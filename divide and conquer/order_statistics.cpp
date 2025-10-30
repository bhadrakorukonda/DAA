#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right], i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

int quickselect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];
    
    int pivotIndex = partition(arr, left, right);
    
    if (k == pivotIndex) return arr[k];
    else if (k < pivotIndex) return quickselect(arr, left, pivotIndex - 1, k);
    else return quickselect(arr, pivotIndex + 1, right, k);
}

int main() {
    vector<int> arr = {12, 3, 5, 7, 19, 10};
    int k = 3;
    int result = quickselect(arr, 0, arr.size() - 1, k - 1);  // k-th smallest
    cout << k << "th smallest element is " << result << "\n";  // Output: 7
}
