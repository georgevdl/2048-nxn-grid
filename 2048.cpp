#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <stdio.h>

bool proc_num(std::vector<int>& v, int bi, int ei){
    std::vector<int> out;
    
    for(int i = 0; i < bi; ++i){
        out.push_back(v[i]);
    }
    int counter = 0, end0counter = 0;
    for(int i = bi; i < ei; ++i){
        if(v[i] != 0) {
            out.push_back(v[i]);
            end0counter = 0;
        }
        else {
            ++counter;
            ++end0counter;
        }
    }
    for(int i = 0; i < counter; ++i){
        out.push_back(0);
    }
    for(int i = ei; i < v.size(); ++i){
        out.push_back(v[i]);
    }
    int end = ei-counter-1;
    for(int i = bi; i < end; ++i){
        if(out[i] == out[i+1]){
            out[i] *= 2;
            for(int j = i+1; j < ei-1; ++j){
                out[j] = out[j+1];
            }
            out[end] = 0;
            ++counter;
        }
    }
    counter = counter - end0counter;
    v=out;
    if(counter > 0) return 1;
    else return 0;
}

void rotate_anti_clock(std::vector<int>& v){
    std::vector<int> result;
    int side = std::sqrt(v.size());
    for(int i = 0; i < side; ++i){
        for(int j = 0; j < side; ++j){
            result.push_back(v[j*4+3-i]);
        }
    }
    v = result;
}

void print_grid(const std::vector<int>& v){
    int side = std::sqrt(v.size());
    for(int i = 0; i < v.size(); ++i){
        
        std::cout << v[i];
        if((i+1) % side == 0){
            std::cout << std::endl;
        }
        else std::cout << "\t";
    }
    
    
}

void insert2(std::vector<int>& v){
    std::vector<int> zeroPositions;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == 0){
            zeroPositions.push_back(i);
        }
    }
    if(zeroPositions.size() > 0){
        int randomPosition = zeroPositions[rand() % zeroPositions.size()];
        v[randomPosition] = 2;
    }
}

void swipe(std::vector<int>& v){
    int side = std::sqrt(v.size());
    for(int i = 0; i < side; ++i){
        proc_num(v, side*i, side*(i+1));
    }
}

bool game_over(const std::vector<int>& v){
    std::vector<int> tempv = v;
    int side = std::sqrt(v.size());
    for(int i=0; i < side; ++i){
        if(proc_num(tempv, side*i, side*(i+1))) return 0;
    }
    tempv = v;
    rotate_anti_clock(tempv);
    for(int i=0; i < side; ++i){
        if(proc_num(tempv, side*i, side*(i+1))) return 0;
    }
    tempv = v;
    rotate_anti_clock(tempv);
    rotate_anti_clock(tempv);
    for(int i=0; i < side; ++i){
        if(proc_num(tempv, side*i, side*(i+1))) return 0;
    }
    tempv = v;
    rotate_anti_clock(tempv);
    rotate_anti_clock(tempv);
    rotate_anti_clock(tempv);
    for(int i=0; i < side; ++i){
        if(proc_num(tempv, side*i, side*(i+1))) return 0;
    }
    return 1;
}

int main () {
    std::string fileName;
    std::cout << "enter initial configuration file name:\n";
    std::cin >> fileName;
    std::ifstream in;
    std::vector<int> v;
    int input;
    in.open(fileName);
    if(!in.is_open()){
        std::cout << "file not found, using default start configuration" << std::endl;
        for(int i = 0; i < 15; ++i){
            v.push_back(0);
        }
        v.push_back(2);
    }
    else {
        while(in >> input){
            v.push_back(input);
        }
    }
    srand(time(NULL));
    while(in >> input){
            v.push_back(input);
    }
    print_grid(v);
    std::string userInput;
    int side = std::sqrt(v.size());
    while(!game_over(v)){
        std::cin >> userInput;
        if(userInput == "w" || userInput == "a" || userInput == "s" || userInput == "d"){
            std::cout << std::endl;
            if(userInput == "a"){
                swipe(v);
            }
            else if(userInput == "w"){
                rotate_anti_clock(v);
                swipe(v);
                rotate_anti_clock(v);
                rotate_anti_clock(v);
                rotate_anti_clock(v);
            }
            else if(userInput == "d"){
                rotate_anti_clock(v);
                rotate_anti_clock(v);
                swipe(v);
                rotate_anti_clock(v);
                rotate_anti_clock(v);
            }
            else if(userInput == "s"){
                rotate_anti_clock(v);
                rotate_anti_clock(v);
                rotate_anti_clock(v);
                swipe(v);
                rotate_anti_clock(v);
            }
            insert2(v);
            print_grid(v);
            std::cout << "\n\n";
        }
    }
    std::cout << "game over\n";
    return 0;
}
