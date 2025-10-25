#ifndef DYNAMIC_ARR_H
#define DYNAMIC_ARR_H

#include <iostream>
using namespace std;

class Dynamic_Arr {
private:

    int size = 0;
    int capacity = 2;
    int* arr = nullptr;

public:

    Dynamic_Arr();
    Dynamic_Arr(int initial_capacity);
    ~Dynamic_Arr();

    void clear() {
        size = 0;
    }
    void add(int value);
    void add_index(int index, int value);
    void remove(int index);
    int get(int index) const;
    void set(int index, int value);
    int get_size() const;
    void resize();
    int get_capacity() const;
    bool empty() const;
    void copy_of_range(Dynamic_Arr src, int startSrc, int startDest, int copyLength);
    void reverse(int left, int right);
    void print();
};


#endif // DYNAMIC_ARR_H