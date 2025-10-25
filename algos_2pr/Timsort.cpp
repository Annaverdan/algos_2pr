#include "Timsort.h"

Timsort::Timsort(Dynamic_Arr& arr) : array(arr), run_stack{}, stack_size(0) {}

Timsort::~Timsort() = default;
int Timsort::count_min_run(int arr_size) {
    int a = 0;
    while (arr_size >= MIN_RUN) {
        a |= arr_size & 1;
        arr_size >>= 1;
    }
    return arr_size + a;

}

void Timsort::insertion_sort(int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = array.get(i);
        int j = i - 1;
        while (j >= left && array.get(j) > key) {
            array.set(j + 1, array.get(j));
            j--;
        }
        array.set(j + 1, key);
    }
}

void Timsort::merge_runs(int start, int mid, int end) {
    int left_len = mid - start + 1;
    int right_len = end - mid;

    Dynamic_Arr left(left_len);
    Dynamic_Arr right(right_len);

    left.copy_of_range(array, start, 0, left_len);
    right.copy_of_range(array, mid + 1, 0, right_len);

    int i = 0, j = 0;
    int k = start;

    const int MIN_GALLOP = 7;
    int left_win = 0;
    int right_win = 0;

    while (i < left_len && j < right_len) {
        if (left.get(i) <= right.get(j)) {
            array.set(k++, left.get(i++));
            left_win++;
            right_win = 0;
        }
        else {
            array.set(k++, right.get(j++));
            right_win++;
            left_win = 0;
        }
        if (left_win >= MIN_GALLOP || right_win >= MIN_GALLOP) {
            if (k > start) {
                i--;
                j--;
                k--;
            }
            if (j < right_len) {
                int n1 = gallop(right.get(j), left, i, left_len - i);
                for (int m = 0; m < n1 && i < left_len; ++m) {
                    array.set(k++, left.get(i++));
                }
            }
            if (i < left_len) {
                int n2 = gallop(left.get(i), right, j, right_len - j);
                for (int m = 0; m < n2 && j < right_len; ++m) {
                    array.set(k++, right.get(j++));
                }
            }
            left_win = 0;
            right_win = 0;
        }
    }
    while (i < left_len) {
        array.set(k++, left.get(i++));
    }
    while (j < right_len) {
        array.set(k++, right.get(j++));
    }
}

void Timsort::sort() {
    if (array.empty() || array.get_size() <= 1) {
        return;
    }
    int n = array.get_size();
    if (n <= MIN_RUN) {
        insertion_sort(0, n - 1);
        return;
    }
    tim_sorting();
}

void Timsort::tim_sorting() {
    int n = array.get_size();
    min_run = count_min_run(n);
    int run_start = 0;
    while (run_start < n) {
        int run_end = find_run_end(run_start, n);
        int run_len = run_end - run_start;
        if (run_len < min_run) {
            int force = min(min_run, n - run_start);
            insertion_sort(run_start, run_start + force - 1);
            run_len = force;
        }
        push_run(run_start, run_len);
        merge_collapse();
        run_start += run_len;
    }
    while (stack_size > 1) {
        mergeAt(stack_size - 2);
    }

}

int Timsort::gallop(int key, Dynamic_Arr& arr, int base, int len) {
    int low = 0;
    int high = len;
    while (low < high) {
        int mid = (low + high) / 2;
        if (arr.get(base + mid) < key) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }
    return low;
}

void Timsort::push_run(int base, int len) {
    if (stack_size >= INITIAL_STACK_SIZE) {
        cout << "Стек пуст";
    }
    run_stack[stack_size] = Run(base, len);
}

void Timsort::merge_collapse() {
    while (stack_size > 1) {
        int n = stack_size - 2;
        if (n > 0 && run_stack[n - 1].len <= run_stack[n].len + run_stack[n + 1].len) {
            if (run_stack[n - 1].len < run_stack[n + 1].len) {
                n--;
            }
            mergeAt(n);
        }
        else if (run_stack[n].len <= run_stack[n + 1].len) {
            mergeAt(n);
        }
        else {
            break;
        }
    }
}

void Timsort::mergeAt(int i) {
    Run& run1 = run_stack[i];
    Run& run2 = run_stack[i + 1];
    run1.len += run2.len;
    stack_size--;
    for (int j = i + 1; j < stack_size; j++) {
        run_stack[j] = run_stack[j + 1];
    }
    merge_runs(run1.base, run1.base + run1.len - run2.len - 1, run1.base + run1.len - 1);
}

int Timsort::find_run_end(int start, int n) {
    if (start >= n - 1) return n;
    int end = start + 2;
    if (array.get(start) > array.get(start + 1)) {
        while (end < n && array.get(end - 1) >= array.get(end)) {
            end++;
        }
        array.reverse(start, end - 1);
    }
    else {
        while (end < n && array.get(end - 1) <= array.get(end)) {
            end++;
        }
    }
    return end;
}