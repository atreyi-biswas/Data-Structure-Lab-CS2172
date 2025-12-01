#include <stdio.h>
#include <stdlib.h>

long long exchanges = 0;   // counts swaps or shift-like operations

// swap two numbers
void swap(int *a, int *b) {
    int t = *a;  //where "t" is temp, and "a" and "b" are elements to swap
    *a = *b;
    *b = t;
    exchanges++;
}

//--------------------------------------------------------------------------------------

// insertion sort (default, uses swap)
void insertionSort_default(int arr[], int n) {
    exchanges = 0;
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(&arr[j], &arr[j - 1]);
            j--;
        }
    }
}

//--------------------------------------------------------------------------------------

// insertion sort (shift method, no swap)
void insertionSort_noSwap(int arr[], int n) {
    exchanges = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  // shift
            j--;
            exchanges++;
        }
        arr[j + 1] = key;
    }
}

//--------------------------------------------------------------------------------------

// bubble sort (default)
void bubbleSort_default(int arr[], int n) {
    exchanges = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

//--------------------------------------------------------------------------------------

// bubble sort (shift method)
void bubbleSort_noSwap(int arr[], int n) {
    exchanges = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = t;
                exchanges++;
            }
}

//--------------------------------------------------------------------------------------

// bubble sort with flag (stops early)
void bubbleSort_flagged(int arr[], int n) {
    exchanges = 0;
    for (int i = 0; i < n - 1; i++) {
        int flag = 0;
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                flag = 1;
            }
        if (!flag) break;
    }
}

//--------------------------------------------------------------------------------------

// range-limited bubble sort
void bubbleSort_rangeLimit(int arr[], int n) {
    exchanges = 0;
    int newn;
    do {
        newn = 0;
        for (int i = 1; i < n; i++)
            if (arr[i - 1] > arr[i]) {
                swap(&arr[i - 1], &arr[i]);
                newn = i;   // last swapped index
            }
        n = newn;
    } while (newn);
}

//--------------------------------------------------------------------------------------

// alternating bubble sort (cocktail sort)
void bubbleSort_alternating(int arr[], int n) {
    exchanges = 0;
    int start = 0, end = n - 1;
    while (start < end) {
        for (int i = start; i < end; i++)
            if (arr[i] > arr[i + 1])
                swap(&arr[i], &arr[i + 1]);
        end--;

        for (int i = end; i > start; i--)
            if (arr[i] < arr[i - 1])
                swap(&arr[i], &arr[i - 1]);
        start++;
    }
}

//--------------------------------------------------------------------------------------

// merge operation
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    // compare and merge
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : (exchanges++, R[j++]);

    // copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

//--------------------------------------------------------------------------------------

// merge sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

//--------------------------------------------------------------------------------------

// choose median of three values
int medianOfThree(int arr[], int a, int b, int c) {
    if ((arr[a] < arr[b] && arr[b] < arr[c]) || (arr[c] < arr[b] && arr[b] < arr[a])) return b;
    if ((arr[b] < arr[a] && arr[a] < arr[c]) || (arr[c] < arr[a] && arr[a] < arr[b])) return a;
    return c;
}

//--------------------------------------------------------------------------------------

// partition for quick sort
int partition(int arr[], int low, int high) {
    int mid = (low + high) / 2;
    int p = medianOfThree(arr, low, mid, high);
    swap(&arr[p], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (arr[j] <= pivot)
            swap(&arr[++i], &arr[j]);

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

//--------------------------------------------------------------------------------------

// quick sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

//--------------------------------------------------------------------------------------

// copy arrays
void copyArray(int d[], int s[], int n) {
    for (int i = 0; i < n; i++) d[i] = s[i];
}

///////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int L1[20] = {1,16,12,26,25,35,33,58,45,42,56,67,83,75,74,86,81,88,99,95};
    int L2[20] = {1,17,21,42,24,27,32,35,45,47,57,23,66,69,70,76,87,85,95,99};
    int L3[20] = {22,20,81,38,95,84,99,12,79,44,26,87,96,10,48,80,1,31,16,92};

    int A[20], ch;

    while (1) {
        printf("\n--- Sorting Menu ---\n");
        printf("1. Insertion Sort (Default)\n");
        printf("2. Insertion Sort (No Swap)\n");
        printf("3. Bubble Sort (Default)\n");
        printf("4. Bubble Sort (No Swap)\n");
        printf("5. Bubble Sort (Flagged)\n");
        printf("6. Bubble Sort (Range Limit)\n");
        printf("7. Bubble Sort (Alternating)\n");
        printf("8. Merge Sort\n");
        printf("9. Quick Sort (Median of Three)\n");
        printf("10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                copyArray(A, L1, 20);
                insertionSort_default(A, 20);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 2:
                copyArray(A, L1, 20);
                insertionSort_noSwap(A, 20);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 3:
                copyArray(A, L2, 20);
                bubbleSort_default(A, 20);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 4:
                copyArray(A, L2, 20);
                bubbleSort_noSwap(A, 20);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 5:
                copyArray(A, L2, 20);
                bubbleSort_flagged(A, 20);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 6:
                copyArray(A, L2, 20);
                bubbleSort_rangeLimit(A, 20);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 7:
                copyArray(A, L2, 20);
                bubbleSort_alternating(A, 20);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 8:
                copyArray(A, L3, 20);
                exchanges = 0;
                mergeSort(A, 0, 19);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 9:
                copyArray(A, L3, 20);
                exchanges = 0;
                quickSort(A, 0, 19);
                printf("Exchanges: %lld\n", exchanges);
                break;

            case 10:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
