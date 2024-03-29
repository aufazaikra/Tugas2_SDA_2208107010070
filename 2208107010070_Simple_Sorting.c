#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// fungsi untuk menghasilkan angka acak dan menyimpannya dalam file
void generateRandomNumbers(int n) {
    FILE *fp;
    fp = fopen("angka_random.txt", "w");
    if (fp == NULL) {
        printf("Error membuka file!\n");
        exit(1);
    }

    srand(time(0));
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", rand());
    }

    fclose(fp);
}

// fungsi bubble sort
void bubbleSort(int arr[], int n)
{
    bool elementSwapped = true;
    for (int i = 0; i < n; i = i + 1)
    {
        elementSwapped = false;
        for (int j = 0; j < n - i - 1; j = j + 1)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                elementSwapped = true;
            }
        }
        if (elementSwapped == false)
            break;
    }
}

// fungsi selection sort
void selectionSort(int arr[], int n) {
    int minIndex, temp;
    for (int i = 0; i < n-1; i++) {
        minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// fungsi insertion sort
void insertionSort(int arr[], int n) {
    clock_t start, end;
    double waktu;
    
    start = clock();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    end = clock();

    waktu = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
    printf("waktu yang dibutuhkan algoritma insertion sort untuk jumlah bilangan %d adalah %.2f ms\n", n, waktu);
}

int main() {
    clock_t start, end;
    double waktu;

    int max_size = 1000000;
    int increment = 100000;

    FILE *fp_sorted, *fp_unsorted;
    fp_sorted = fopen("angka_terurut.txt", "w");
    fp_unsorted = fopen("angka_tak_terurut.txt", "w");
    if (fp_sorted == NULL || fp_unsorted == NULL) {
        printf("Error membuka file!\n");
        exit(1);
    }

    for (int n = increment; n <= max_size; n += increment) {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Alokasi memori gagal!\n");
            exit(1);
        }
 
        generateRandomNumbers(n);

        // membaca nomor acak dari file
        FILE *fp;
        fp = fopen("angka_random.txt", "r");
        if (fp == NULL) {
            printf("Error membuka file!\n");
            exit(1);
        }

        for (int i = 0; i < n; i++) {
            fscanf(fp, "%d", &arr[i]);
        }
        fclose(fp);

        // menulis nomor yang belum diurutkan ke file
        for (int i = 0; i < n; i++) {
            fprintf(fp_unsorted, "%d\n", arr[i]);
        }

        // Bubble Sort
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        waktu = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
        printf("waktu yang dibutuhkan algoritma bubble sort untuk jumlah bilangan %d adalah %.2f ms\n", n, waktu);

        // menulis nomor yang sudah diurutkan ke file
        for (int i = 0; i < n; i++) {
            fprintf(fp_sorted, "%d\n", arr[i]);
        }

        // Selection Sort
        start = clock();
        selectionSort(arr, n);
        end = clock();
        waktu = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
        printf("waktu yang dibutuhkan algoritma selection sort untuk jumlah bilangan %d adalah %.2f ms\n", n, waktu);

        // menulis nomor yang sudah diurutkan ke file
        for (int i = 0; i < n; i++) {
            fprintf(fp_sorted, "%d\n", arr[i]);
        }

        // Insertion Sort
        insertionSort(arr, n);
        
        // menulis nomor yang sudah diurutkan ke file
        for (int i = 0; i < n; i++) {
            fprintf(fp_sorted, "%d\n", arr[i]);
        }

        free(arr);
    }

    fclose(fp_sorted);
    fclose(fp_unsorted);

    return 0;
}

