#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void SelectionSort(int[], int);
void bubbleSort(int[], int);
void insertionSort(int[], int);
void maxHeapify(int[], int, int);
void buildMaxHeap(int[], int);
void heapSort(int[], int);
void merge(int[], int, int, int);
void mergeSort(int[], int, int);
int partition(int*, int, int);
void quickSort(int[], int, int);
void swap(int*, int*);
void copyArray(int[], int, int[]);
void printArray(int[], int, char[]);
int* generateRandom(int);
void checkPrint(int[], int, char[]);
void testSorting(int*, int);

int main()
{
    int *arr, *result;
    arr = generateRandom(10);   //(size = 10) only to show that the array is sorted correctly
    result = malloc(10*sizeof(int));
    copyArray(arr, 10, result);
    testSorting(result, 10);

    clock_t t;
    for(int size = 10000; size <= 235000; size += 45000)
    {
        printf("Array of size: %d\n\n", size);
        arr = generateRandom(size);
        checkPrint(arr,size,"Original Array");  //To check if the user wants to print the array
        printf("\n");
        result = realloc(result, size*sizeof(int));  //allocate with the new size

        for(int j=1; j<=6; j++)
        {
            copyArray(arr, size, result);   //preserve the original array by copying it to result
            t = clock();    //start time
            if(j == 1)
            {
                SelectionSort(result, size);
                t = clock() - t;   //time taken = end time - start time
                checkPrint(result,size,"Selection Sort");
                printf("Selection Sort ");
            }
            else if(j == 2)
            {
                bubbleSort(result, size);
                t = clock() - t;
                checkPrint(result,size,"Bubble Sort");
                printf("Bubble Sort ");
            }
            else if(j == 3)
            {
                insertionSort(result, size);
                t = clock() - t;
                checkPrint(result,size,"Insertion Sort");
                printf("Insertion Sort ");
            }
            else if(j == 4)
            {
                heapSort(result, size);
                t = clock() - t;
                checkPrint(result,size,"Heap Sort");
                printf("Heap Sort ");
            }
            else if(j == 5)
            {
                mergeSort(result, 0, size - 1);
                t = clock() - t;
                checkPrint(result,size,"Merge Sort");
                printf("Merge Sort ");
            }
            else if(j == 6)
            {
                quickSort(result, 0, size - 1);
                t = clock() - t;
                checkPrint(result,size,"Quick Sort");
                printf("Quick Sort ");
            }
            printf("took %lf seconds to execute\n\n", ((double)t)/CLOCKS_PER_SEC);
        }
        printf("---------------------------------------------------------------------------------------------------------------\n\n");
    }
    free(arr);
    free(result);
    return 0;
}


void SelectionSort(int arr[],int n)
{
    for(int i=0; i<n-1; i++)
    {
        int iMin=i;
        for(int j=i+1; j<n; j++)
        {
            if(arr[j]<arr[iMin])
            {
                iMin=j;
            }
        }
        if(i!=iMin)
            swap(&arr[i],&arr[iMin]);
    }
}


void bubbleSort(int A[], int n)
{
    int i,j,flag=0;
    for(i=0; i<n-1; i++)
    {
        flag=0;
        for(j=0; j<n-i-1; j++)
        {
            if(A[j]>A[j+1])
            {
                swap(&A[j], &A[j+1]);
                flag = 1;
            }
        }
        if(flag == 0)
            return;
    }
}


void insertionSort(int arr[],int n)
{
    for(int i=0; i<n; i++)
    {
        int key=arr[i];
        int hole=i;
        while(hole>0 && arr[hole-1]>key)
        {
            arr[hole]=arr[hole-1];
            hole=hole-1;
        }
        arr[hole]=key;
    }
}


void maxHeapify(int A[], int heapSize, int i)
{
    int left = 2*i+1;
    int right = 2*i+2;
    int largest;

    if((left<heapSize) && (A[left]>A[i]))
        largest = left;
    else
        largest = i;

    if((right<heapSize) && (A[right]>A[largest]))
        largest = right;

    if(largest != i)
    {
        swap(&A[i], &A[largest]);
        maxHeapify(A, heapSize, largest);
    }
}


void buildMaxHeap(int A[], int n)
{
    int i;
    for(i=n/2 - 1; i>=0; i--)
        maxHeapify(A, n, i);
}


void heapSort(int A[], int n)
{
    buildMaxHeap(A,n);
    int heapSize = n;
    int i;
    for(i=n-1 ; i>0; i--)
    {
        swap(&A[i], &A[0]);
        heapSize--;
        maxHeapify(A, heapSize, 0);
    }
}


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int nL = m - l + 1;
    int nR = r - m;

    int L[nL], R[nR];
    for (i = 0; i < nL; i++)
        L[i] = arr[l + i];
    for (j = 0; j < nR; j++)
        R[j] = arr[m + 1 + j];

    i=0;
    j=0;
    k=l;
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < nL) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < nR) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


int partition(int *arr,int first,int last)
{
    int lastS1 = first;
    int firstUnknown = first + 1;
    while (firstUnknown <= last)
    {
        if (arr[firstUnknown] < arr[first])
        {
            lastS1 = lastS1 + 1;
            swap(&arr[firstUnknown],&arr[lastS1]);
        }
        firstUnknown = firstUnknown + 1;
    }
    swap(&arr[first], &arr[lastS1]);
    return lastS1;
}


void quickSort(int arr[],int first,int last)
{
    if(first<last)
    {
        int q = partition(arr,first,last);
        quickSort(arr,first,q-1);
        quickSort(arr,q+1,last);
    }
}


void swap(int* num1, int* num2)
{
    int temp;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}


void copyArray(int arr[],int n,int x[])
{
    for(int i=0; i<n; i++)
    {
        x[i]=arr[i];
    }
}

void printArray(int arr[],int n, char str[])
{
    puts(str);
    for(int i=0; i<n; i++)
        printf("%d ",arr[i]);
    printf("\n\n");
}

int* generateRandom(int size)
{
    srand(time(0));
    int* A = malloc(size*sizeof(int));
    for(int i = 0; i<size; i++)
        A[i] = rand()%10000;  //Generates random numbers between 0 and 9999
    return A;
}

void checkPrint(int result[],int size, char str[])
{
    int choice;
    printf("Do you want to print %s ?\nPress 1 to print sorted. Press any other number to skip printing: ", str);
    scanf("%d",&choice);
    if(choice == 1)
        printArray(result, size, str);
}

void testSorting(int result[], int size)
{
    printf("Array of size: %d\n\n", size);
    printArray(result, size, "Original Array:");
    for(int i = 1; i <= 6; i++)
    {
        if(i == 1)
        {
            SelectionSort(result, size);
            printArray(result, size, "Selection Sort:");
        } else if(i == 2)
        {
            bubbleSort(result, size);
            printArray(result, size, "Bubble Sort:");
        } else if(i == 3)
        {
            insertionSort(result, size);
            printArray(result, size, "Insertion Sort:");
        } else if(i == 4)
        {
            heapSort(result, size);
            printArray(result, size, "Heap Sort:");
        } else if(i == 5)
        {
            mergeSort(result, 0, size - 1);
            printArray(result, size, "Merge Sort:");
        } else if(i == 6)
        {
            quickSort(result, 0, size - 1);
            printArray(result, size, "Quick Sort:");
        }
    }
    printf("---------------------------------------------------------------------------------------------------------------\n\n");
}
