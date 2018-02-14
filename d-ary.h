//
//  d-ary.h
//  d-ary
//
//  Created by Jared Heddinger on 12/19/17.
//  Copyright © 2017 Jared Heddinger. All rights reserved.
//

#ifndef d_ary_h
#define d_ary_h

#include <vector>
#include <cmath>
#include <iterator>

template<typename T, int D = 2, typename COMP = std::less<T>>
class d_ary {
public:
    d_ary() : compare{COMP()} {
        heap.push_back(T());
    }
    
    d_ary(d_ary& d) : compare{COMP()} {
        heap.push_back(T());
        for (auto &t : d.heap) {
            heap.push_back(t);
        }
    }
    
    d_ary(std::vector<T>& in) {
        heap = in;
    }
    
    bool empty() {
        return heap.size() < 2;
    }
    
    const size_t size() const {
        return heap.size() - 1;
    }
    
    void clear() {
        heap.clear();
    }
    
    T& top() {
        return heap[1];
    }
    
    void push(T& i) {
        heap.push_back(std::move(i));
        fixUp();
    }
    
    void pop() {
        std::swap(heap[1], heap.back());
        heap.pop_back();
        fixDown(1);
    }
    
    void updatePriorities() {
        int leaf = (int(size()) / D);
        while (leaf >= 1) {
            fixDown(leaf);
            --leaf;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const d_ary& dOut) {
        int max = 1;
        int level = 1;
        for (int i = 1; i < dOut.size(); ++i) {
            if (i > max) {
                os << "\n";
                max += std::pow(D, level);
                ++level;
            }
            os << dOut.heap[i] << " ";
        }
        return os;
    }
    
private:
    std::vector<T> heap;
    COMP compare;
    
    int child(int i, int j) {
        int o = ((D * (i - 1)) + 1) + j;
        if (o <= size()) {
            return o;
        }
        return -1;
    }
    
    int smallestChild(int i) {
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
    
    int parent(int i) {
        return ((i - 1) / D) + 1;
    }
    
    void fixUp() {
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
    
    void fixDown(int place) {
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
};



#endif /* d_ary_h */
