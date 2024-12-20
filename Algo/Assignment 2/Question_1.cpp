#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

// Sorting algorithms
void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        size_t j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; ++i, ++k) {
        arr[i] = temp[k];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                swap(arr[++i], arr[j]);
            }
        }
        swap(arr[++i], arr[right]);
        quickSort(arr, left, i - 1);
        quickSort(arr, i + 1, right);
    }
}

// Function to measure execution time
long long measureTime(void (*sortFunc)(vector<int>&), vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

int main() {
    // Array sizes to test
    vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000, 100000};
    
    // Open CSV file to write results
    ofstream outFile("sorting_times.csv");
    outFile << "Array Size,Bubble Sort,Insertion Sort,Selection Sort,Merge Sort,Quick Sort\n";

    // Measure time for each size
    for (int size : sizes) {
        // Generate random data
        vector<int> arr(size);
        generate(arr.begin(), arr.end(), rand);
        
        // Time each sorting algorithm
        long long bubbleTime = measureTime(bubbleSort, arr);
        long long insertionTime = measureTime(insertionSort, arr);
        long long selectionTime = measureTime(selectionSort, arr);
        
        // Merge Sort and Quick Sort need the array to be reset
        vector<int> tempArr = arr; // create a copy
        long long mergeTime = measureTime([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, tempArr);

        tempArr = arr; // create a copy
        long long quickTime = measureTime([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, tempArr);

        // Write to CSV
        outFile << size << "," << bubbleTime << "," << insertionTime << "," 
                << selectionTime << "," << mergeTime << "," << quickTime << "\n";
    }

    outFile.close();
    cout << "Timing results saved to sorting_times.csv" << endl;

    return 0;
}
