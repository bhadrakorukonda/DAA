#include <bits/stdc++.h>
using namespace std;

long long merge_and_count(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left == right) return 0;
    int mid = (left + right) / 2;
    long long inv_count = merge_and_count(arr, temp, left, mid);
    inv_count += merge_and_count(arr, temp, mid + 1, right);
    inv_count += merge(arr, temp, left, mid, right);
    return inv_count;
}

long long merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    long long inv_count = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);  // All the elements left in the left subarray are greater than arr[j]
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (i = left; i <= right; ++i) arr[i] = temp[i];
    
    return inv_count;
}

int main() {
    vector<int> arr = {5, 4, 3, 2, 1};
    vector<int> temp(arr.size());
    long long result = merge_and_count(arr, temp, 0, arr.size() - 1);
    cout << "Number of inversions: " << result << "\n";  // Output: 10
}
