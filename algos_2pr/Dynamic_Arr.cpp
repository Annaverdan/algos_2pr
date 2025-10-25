#include "Dynamic_Arr.h"
using namespace std;

Dynamic_Arr::Dynamic_Arr() {
    arr = new int[capacity]();
}

Dynamic_Arr::Dynamic_Arr(int initial_capacity) {
    if (initial_capacity <= 0) {
        cout << "Размерность должна быть положительной";
    }
    this->capacity = initial_capacity;
    arr = new int[capacity]();
}

Dynamic_Arr::~Dynamic_Arr() {
    delete[] arr;
    arr = nullptr;
}

void Dynamic_Arr::resize() {
    int new_capacity = capacity * 2;
    int* new_data = new int[new_capacity]();

    for (int i = 0; i < size; i++) {
        new_data[i] = arr[i];
    }
    delete[] arr;
    arr = new_data;
    capacity = new_capacity;
}

void Dynamic_Arr::add(int value) {
    if (size >= capacity) {
        resize();
    }
    arr[size] = value;
    ++size;
}

void Dynamic_Arr::add_index(int index, int value) {
    if (index < 0 || index > size) {
        cout << "Некорректный индекс";
    }
    if (size >= capacity) {
        resize();
    }
    for (int i = size; i > index; --i) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    ++size;
}

void Dynamic_Arr::remove(int index) {
    if (index < 0 || index >= size) {
        cout << "Некорректный индекс";
    }
    for (int i = index; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --size;
}

int Dynamic_Arr::get(int index) const {
    if (index < 0 || index >= size) {
        cout << "Некорректный индекс";
    }
    return arr[index];
}

void Dynamic_Arr::set(int index, int value) {
    if (index < 0 || index >= size) {
        cout << "Некорректный индекс";
    }
    arr[index] = value;
}

int Dynamic_Arr::get_size() const {
    return size;
}

int Dynamic_Arr::get_capacity() const {
    return capacity;
}

bool Dynamic_Arr::empty() const {
    return size == 0;
}

void Dynamic_Arr::copy_of_range(Dynamic_Arr src, int startSrc, int startDest, int copyLength) {
    if (copyLength <= 0) return;
    if (startSrc < 0 || startSrc + copyLength > src.get_size()) {
        cout << "Диапазон источника за пределами допустимого";
    }
    if (startDest < 0 || startDest + copyLength > size) {
        cout << "Диапазон источника за пределами допустимого";
    }
    for (int i = 0; i < copyLength; ++i) {
        arr[startDest + i] = src.get(startSrc + i);
    }
}

void Dynamic_Arr::reverse(int left, int right) {
    while (left < right) {
        swap(left, right);
        ++left;
        --right;
    }
}

void Dynamic_Arr::print() {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}