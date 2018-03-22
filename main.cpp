//
//  main.cpp
//  d-ary
//
//  Created by Jared Heddinger on 12/19/17.
//  Copyright © 2017 Jared Heddinger. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <queue>
#include "d-ary.cpp"

int main(int argc, const char * argv[]) {

    std::vector<int> v;
    for (int i = 0; i < 50; ++i) {
        int tmp = rand() % 100;
        v.push_back(tmp);
    }
    d_ary<int, 4> d(v);
    std::cout << d << std::endl;
    d.updatePriorities();
    std::cout << d;

    
    auto d1Start = std::chrono::high_resolution_clock::now();
    d_ary<int> d1;
    for (int i = 0; i < 50000000; ++i) {
        int tmp = rand() % 1000000;
        d1.push(tmp);
    }
    auto d1End = std::chrono::high_resolution_clock::now();
    std::cout << "Time Binary: " << std::chrono::duration_cast<std::chrono::milliseconds>(d1End - d1Start).count() << "\n";
    

    auto d2Start = std::chrono::high_resolution_clock::now();
    d_ary<int, 2> d2;
    for (int i = 0; i < 10000000; ++i) {
        int tmp = rand() % 1000000;
        d2.push(tmp);
    }
    auto d2End = std::chrono::high_resolution_clock::now();
    std::cout << "Time 4-ary: " << std::chrono::duration_cast<std::chrono::milliseconds>(d2End - d2Start).count() << "\n";

    auto d3Start = std::chrono::high_resolution_clock::now();
    std::priority_queue<int, std::vector<int>, std::less<int>> d3;
    for (int i = 0; i < 50000000; ++i) {
        int tmp = rand() % 1000000;
        d3.push(tmp);
    }
    auto d3End = std::chrono::high_resolution_clock::now();
    std::cout << "Time Vector: " << std::chrono::duration_cast<std::chrono::milliseconds>(d3End - d3Start).count() << "\n";
    
    while (!d.empty()) {
        std::cout << d.top() << " ";
        d.pop();
    }
    
    return 0;
}
