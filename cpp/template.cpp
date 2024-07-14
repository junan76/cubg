#include <iostream>
#include <cmath>
#include <cstring>
#include <gtest/gtest.h>

/**
 * 实现快速排序算法的函数模板. 要求模板参数"T"支持"<"运算符, 对于字符串类型的比较, 使用"strcmp"标准库函数.
 */

template <typename T>
void swap_two(int i, int j, T *const array)
{
    T tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

template <typename T>
void quick_sort_internal(int start, int end, T *const array)
{
    if (start >= end)
        return;

    const T flag = array[start];
    int i = start + 1;
    int j = end;

    while (i <= j)
    {
        while (!(flag < array[i]) && i <= j)
            i++;

        while (flag < array[j] && i <= j)
            j--;

        if (i < j)
            swap_two(i, j, array);
    }

    swap_two(start, j, array);
    quick_sort_internal(start, j - 1, array);
    quick_sort_internal(j + 1, end, array);
}

template <>
void quick_sort_internal<const char *>(int start, int end, const char *array[])
{
    if (start >= end)
        return;

    const char *flag = array[start];
    int i = start + 1;
    int j = end;

    while (i <= j)
    {
        while (strcmp(array[i], flag) <= 0 && i <= j)
            i++;

        while (strcmp(array[j], flag) > 0 && i <= j)
            j--;

        if (i < j)
            swap_two(i, j, array);
    }

    swap_two(start, j, array);
    quick_sort_internal(start, j - 1, array);
    quick_sort_internal(j + 1, end, array);
}

template <typename T>
void quick_sort(int n, T * const array)
{
    quick_sort_internal(0, n - 1, array);
}

template <typename T, int n>
void run_test_quick_sort(T *const array)
{
    std::cout << ">> [";
    for (int i = 0; i < n; i++)
        std::cout << array[i] << (i == n - 1 ? "]\n" : ", ");
    
    quick_sort(n, array);

    std::cout << ">> [";
    for (int i = 0; i < n; i++)
        std::cout << array[i] << (i == n - 1 ? "]\n\n" : ", ");
}

TEST(func_template, test_quick_sort)
{
    int nums[] = {45, 3, 12, 4, 2, 100};
    const char *words[] = {"talk", "is", "cheap", "show", "me", "the", "code"};

    const int n1 = sizeof(nums) / sizeof(int);
    const int n2 = sizeof(words) / sizeof(const char *);

    run_test_quick_sort<int, n1>(nums);
    run_test_quick_sort<const char *, n2>(words);
}