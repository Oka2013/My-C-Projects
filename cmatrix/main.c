// Çıktı panelinin boyutunu ayarlamanızı öneririm!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>

void print_memory_usage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    printf("%ld byte\n", memInfo.WorkingSetSize);
}

void delay(int tms) {
    clock_t st = clock();
    while(clock() < st + tms);
}

char* new_random_line(size_t ls) {
    char* line = (char*)calloc(ls + 1, 1);

    for (int i = 0; i < ls; i++) {
        line[i] = rand() % 3 < 2 ? 32 : rand() % 128;
    }

    return line;
}

char** new_matrix(size_t ls) {
    char** matrix = (char**)calloc(ls, sizeof(char*));

    for (int i = 0; i < ls; i++) {
        matrix[i] = new_random_line(ls);
    }

    return matrix;
}

char** cmatrix(char** matrix, size_t ls) {
    free(matrix[ls - 1]);

    for (int i = ls - 1; i > 0; i--) {
        matrix[i] = matrix[i - 1];
    }

    matrix[0] = new_random_line(ls);
}

void print_matrix(char** matrix, size_t ls) {
    for (int i = 0; i < ls; i++) {
        printf("%s\n", matrix[i]);
    }
}

int main() {
    srand(time(NULL));

    size_t ls = 100000;
    char** matrix = new_matrix(ls);

    for (int i = 0; i < 100; i++) {
        //print_matrix(matrix, ls);
        cmatrix(matrix, ls);
        delay(250);
        print_memory_usage();
    }

    return 0;
}