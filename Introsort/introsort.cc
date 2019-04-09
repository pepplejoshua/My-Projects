#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <time.h>

using namespace std;

// makes a heap to help get largest value from array
template <typename T>
void makeHeap(T items[], int n, int i);

// sorts an array using heapsort algorithm, calls makeHeap()
template <typename T>
void heapsort(T items[], int n);

// this partitions around an index value where its lhs is smaller and the rhs is only values larger
template <typename T>
int partition(T items[], int low, int high);

// this is the actual introsort which performs quicksort until the max recursion depth has been reached and then hands it over to the heapsort.
template <typename T>
void qsort2(T items, int low, int high, int actualSize, int recurseDepth);

// this is the high level function the user can call.
template <typename T>
void introsort(T items[], int n);


int main() {
    
    int n = 0;
    cout << "Enter an array size or 0 to quit -- ";
    cin >> n;
    
    while(n > 0)
    {
        // dynamic array
        int *items = new int[n];
        
        // seed random function using time
        srand((int) time(NULL));
        
        // this loads array with random elements while also printing these values
        cout << "Initial array => \n";
        for (int i = 0; i < n; ++i)
        {
            items[i] = rand() % 10000;
            if (i != 0 && i % 10 == 0)
                cout << endl;
            cout << items[i] << " ";
        }
        
        cout << endl;
        // this calls the sort function
        introsort(items, n);
        cout << endl;
        
        // this prints the sorted array
        cout << "Sorted array => \n";
        for(int i = 0; i < n; i++)
        {
            if (i != 0 && i % 10 == 0)
                cout << endl;
            cout << items[i] << " ";
        }
        cout << "\n\nEnter an array size -- ";
        cin >> n;
    }
    
    return 0;
}



template <typename T>
void makeHeap(T items[], int n, int i)
{
    // set max to i
    int max = i;

    // this maps the heap index for left and right to a 1D array index
    int leftNode = 2 * i + 1;
    int rightNode = 2 * i + 2;
    
    // if leftNode is larger than max, max is leftNode
    if (leftNode < n && items[leftNode] > items[max])
        max = leftNode;
    
    // if rightNode is larger than max, max is rightNode
    if (rightNode < n && items[rightNode] > items[max])
        max = rightNode;
    
    if (max != i)
    {
        // if the initial max (i) isn't the true max (leftNode or rightNode), swap the max with i
        swap(items[i], items[max]);
        
        // recursively turn the rest of the array into a heap
        makeHeap(items, n, max);
    }
    
}

template <typename T>
void heapsort(T items[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        makeHeap(items, n, i);
    }
    
    for (int i = n - 1; i >= 0; i--)
    {
        swap(items[0], items[i]);
        
        makeHeap(items, i, 0);
    }
}

template <typename T>
int partition(T items[], int low, int high)
{
    T pivot = items[high]; // pivot
    
    int i = low - 1; //the index of a smaller element
    
    for (int j = low; j <= high - 1; j++)
    {
        if(items[j] <= pivot)
        {
            i++;
            swap(items[i], items[j]);
        }
    }
    
    swap(items[i+1], items[high]);
    return i + 1;
}

template <typename T>
void qsort2(T items, int low, int high, int actualSize, int recurseDepth)
{
    if (low < high)
    {
        if (recurseDepth == 0)
        {
            heapsort(items, high);
            return;
        }
        
        recurseDepth--;
        int partIndex = partition(items, low, high);
        
        // sort both sides of partition
        qsort2(items, low, partIndex-1, actualSize, recurseDepth);
        qsort2(items, partIndex+1, high, actualSize, recurseDepth);
    }
}

template <typename T>
void introsort(T items[], int n)
{
    int recurseDepth  = 2 * log2(n);
    qsort2(items, 0, n - 1, n, recurseDepth);
}
