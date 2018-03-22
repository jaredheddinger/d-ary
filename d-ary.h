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
#include <iostream>

template<typename T, int D = 2, typename COMP = std::less<T>>
class d_ary {
public:
    d_ary();
    
    d_ary(d_ary& d);
    
    d_ary(std::vector<T>& in);
    
    bool empty();
    
    const size_t size() const;
    
    void clear();
    
    T& top();
    
    void push(T& i);
    
    void pop();
    
    void updatePriorities();
    
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
    
    int child(int i, int j);
    
    int smallestChild(int i);
    
    int parent(int i);
    
    void fixUp();
    
    void fixDown(int place);
};



#endif /* d_ary_h */
