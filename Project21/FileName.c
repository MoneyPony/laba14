#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 100

double func(int size, int i);
double* full_elements(double* ptr_array, int size);
int put_elements(double* ptr_array, int n);
double* calc_elements(double* ptr_array, int n);
double sum_elements(double* ptr_array, int begin, int end);
int find_element(double* ptr_array, int n, double findelem);
double find_max(double* ptr_array, int n, double A);
int weight(double* ptr_array, int n);

int main() {
    double array[N];
    int size;
    setlocale(LC_ALL, "RUS");
    printf("������� ������ ������� > ");
    scanf("%d", &size);
    if (size <= 0 || size > N) {
        printf("������������ ������ �������. ����� �� ���������.\n");
        return 1;
    }
    full_elements(array, size);
    put_elements(array, size);
    calc_elements(array, size);
    printf("������������ �������� �������:\n");
    put_elements(array, size);
    int begin, end;
    printf("������� ��������� � �������� ������� ��� ���������� ����� (�� 0 �� %d) > ", size - 1);
    scanf("%d %d", &begin, &end);
    if (begin >= 0 && begin <= size - 1 && end >= 0 && end <= size - 1 && begin <= end) {
        double sum = sum_elements(array, begin, end);
        printf("����� ��������� �� ������� %d �� %d: %g\n", begin, end, sum);
    }
    else {
        printf("������������ �������. ���������� ����� ����������.\n");
    }
    double findelem;
    printf("������� ������� ��� ������ 1> ");
    scanf("%lf", &findelem);
    int index = find_element(array, size, findelem);
    if (index != -1) {
        printf("������� %lg ������ �� ������� %d.\n", findelem, index);
    }
    else {
        printf("������� %lg �� ������ � �������.\n", findelem);
    }
    double A;
    printf("������� �������� A ��� ������ ������������� �� ������ ��������, �� ������� A > ");
    scanf("%lf", &A);

    double maxabs = find_max(array, size, A);

    if (maxabs >= 0) {
        printf("������������ �� ������ ��������, �� ������ %g: %g\n", A, maxabs);
    }
    else {
        printf("��� ����������� �������� � �������.\n");
    }
    int elem = weight(array, size);
    printf("���������� ��������� �������, ������� ��� ������ ����������� ��������: %d\n", elem);
}

double func(int size, int i)
{
    float end = 4;
    float start = 2;
    float step = (end - start) / size;
    float x;
    double y;
    x = 1 + i * step;
    y = pow(x, 3) + 3 * pow(x, 2) - 3;
    return y;
}

double* full_elements(double* ptr_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        ptr_array[i] = func(size, i);
    }
    return ptr_array;
}

int put_elements(double* ptr_array, int n) {
    printf("�������� �������:\n");
    for (int i = 0; i < n; ++i) {
        printf("%g ", ptr_array[i]);
    }
    printf("\n");
}

int find_min_index(double* ptr_array, int n) {
    int min_index = 0;
    for (int i = 1; i < n; ++i) {
        if (ptr_array[i] < ptr_array[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

int find_max_index(double* ptr_array, int n) {
    int max_index = 0;
    for (int i = 1; i < n; ++i) {
        if (ptr_array[i] > ptr_array[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

double* calc_elements(double* ptr_array, int n) {
    int min = find_min_index(ptr_array, n);
    int max = find_max_index(ptr_array, n);
    double sum = 0;
    int count = 0;
    int start, end;
    if (min < max) {
        start = min;
        end = max;
    }
    else {
        start = max;
        end = min;
    }
    for (int i = start + 1; i < end; ++i) {
        sum += ptr_array[i];
        ++count;
    }
    if (count > 0) {
        double average = sum / count;
        for (int i = start + 1; i < end; ++i) {
            ptr_array[i] = average;
        }
        printf("������� �������������� ��������� ����� ����������� � ������������: %g\n", average);
    }
    return ptr_array;
}

double sum_elements(double* ptr_array, int begin, int end) {
    double sum = 0;
    for (int i = begin; i <= end; ++i) {
        sum += ptr_array[i];
    }
    return sum;
}

int find_element(double* ptr_array, int n, double findelem) {
    for (int i = 0; i < n; i++)
    {
        if (fabs(ptr_array[i] - findelem) <= 0.00001)
        {
            return i;
        }
    }
    return -1;
}

double find_max(double* ptr_array, int n, double A) {
    double maxabs = 0;
    int found = 0;
    for (int i = 0; i < n; ++i) {
        if (ptr_array[i] != A) {
            double abs = fabs(ptr_array[i]);
            if (!found || abs > maxabs) {
                maxabs = abs;
                found = 1;
            }
        }
    }
    if (found) {
        return maxabs;
    }
    else {
        return -1;
    }
}

int weight(double* ptr_array, int n) {
    if (n <= 2) {
        return 0;
    }
    double min = ptr_array[0];
    double max = ptr_array[0];
    for (int i = 1; i < n; ++i) {
        if (ptr_array[i] < min) {
            min = ptr_array[i];
        }
        if (ptr_array[i] > max) {
            max = ptr_array[i];
        }
    }
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        if (ptr_array[i] != min && ptr_array[i] != max) {
            sum += ptr_array[i];
        }
    }
    double weight = sum / (n - 2);
    printf("���������� ������� ��������������: %g\n", weight);
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (ptr_array[i] <= weight) {
            ++count;
        }
    }
    return count;
}