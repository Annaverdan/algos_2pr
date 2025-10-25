#ifndef TIMSORT_H
#define TIMSORT_H
#include "Dynamic_Arr.h"

class Timsort {
public:

    Timsort(Dynamic_Arr& array);
    ~Timsort();
    void sort();

private:

    struct Run {
        int base;
        int len;
        Run() = default;
        Run(int b, int l) : base(b), len(l) {}
    };

    Dynamic_Arr& array;
    const int MIN_RUN = 32;
    const int MIN_GALLOP = 7;
    int min_gallop = MIN_GALLOP;
    static const int INITIAL_STACK_SIZE = 40;
    Run run_stack[INITIAL_STACK_SIZE];
    int stack_size = 0;
    int min_run;
    int count_min_run(int arraySize);
    void insertion_sort(int left, int right);
    void merge_runs(int start, int mid, int end);
    void tim_sorting();
    int gallop(int key, Dynamic_Arr& array, int base, int len);
    void push_run(int base, int len);
    void merge_collapse();
    void mergeAt(int i);
    int find_run_end(int start, int n);

};

#endif // TIMSORT_H