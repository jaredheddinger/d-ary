//
//  d-ary.cpp
//  
//
//  Created by Jared Heddinger on 3/13/18.
//

#include <vector>
#include <cmath>
#include <iterator>
#include "d-ary.h"

template<typename T, int D, typename COMP>
d_ary<T, D, COMP>::d_ary() : compare{COMP()} {
    heap.push_back(T());
}

template<typename T, int D, typename COMP>
d_ary<T, D, COMP>::d_ary(d_ary& d) : compare{COMP()} {
    heap.push_back(T());
    for (auto &t : d.heap) {
        heap.push_back(t);
    }
}

template<typename T, int D, typename COMP>
d_ary<T, D, COMP>::d_ary(std::vector<T>& in) {
    heap = in;
}

template<typename T, int D, typename COMP>
bool d_ary<T, D, COMP>::empty() {
    return heap.size() < 2;
}

template<typename T, int D, typename COMP>
const size_t d_ary<T, D, COMP>::size() const {
    return heap.size() - 1;
}

template<typename T, int D, typename COMP>
void d_ary<T, D, COMP>::clear() {
    heap.clear();
}

template<typename T, int D, typename COMP>
T& d_ary<T, D, COMP>::top() {
    return heap[1];
}

template<typename T, int D, typename COMP>
void d_ary<T, D, COMP>::push(T& i) {
    heap.push_back(std::move(i));
    fixUp();
}

template<typename T, int D, typename COMP>
void d_ary<T, D, COMP>::pop() {
    std::swap(heap[1], heap.back());
    heap.pop_back();
    fixDown(1);
}

template<typename T, int D, typename COMP>
void d_ary<T, D, COMP>::updatePriorities() {
    int leaf = (int(size()) / D);
    while (leaf >= 1) {
        fixDown(leaf);
        --leaf;
    }
}

template<typename T, int D, typename COMP>
int d_ary<T, D, COMP>::child(int i, int j) {
    int o = ((D * (i - 1)) + 1) + j;
    if (o <= size()) {
        return o;
    }
    return -1;
}

template<typename T, int D, typename COMP>
int d_ary<T, D, COMP>::smallestChild(int i) {
    int min = child(i, 1);
    for (int pos = 2; pos <= D; ++pos) {
        int tmp = child(i, pos);
        if (tmp == -1) {break;}
        else if (compare(heap[tmp], heap[min])) {
            min = tmp;
        }
    }
    return min;
}

template<typename T, int D, typename COMP>
int d_ary<T, D, COMP>::parent(int i) {
    return ((i - 1) / D) + 1;
}

template<typename T, int D, typename COMP>
void d_ary<T, D, COMP>::fixUp() {
    auto start = ++heap.begin();
    auto end = heap.end();
    auto len = (end - start); //num actual els
    if (len > 1) {
        len = ((len - 1) / D) + 1; // len becomes distance needed to move forward from start (1) to be mother of
        auto ptr = start + len; // ptr becomes mother of last element
        if (!compare(*ptr, *--end)) { //if mother of last element less than element
            T tmp(std::move(*end)); //tmp == last element
            do {
                *end = std::move(*ptr); //val at last is mother of last
                end = ptr; //last ptr = mother of last ptr
                if (len == 1) {
                    break;
                }
                len = ((len - 1) / D) + 1;
                ptr = start + len;
            } while (!compare(*ptr, tmp));
            *end = std::move(tmp);
        }
    }
}

template<typename T, int D, typename COMP>
void d_ary<T, D, COMP>::fixDown(int place) {
    while (smallestChild(place) != -1) {
        int tmp = smallestChild(place);
        if (tmp == -1) {break;}
        if (compare(heap[tmp], heap[place])) {
            std::swap(heap[tmp], heap[place]);
        }
        else {
            break;
        }
        place = tmp;
    }
}

