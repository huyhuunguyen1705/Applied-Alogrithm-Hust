/*
Description
Given a sequence of integers a1, a2, ..., an. A pair (i, j) is call an inversion if i < j and ai > aj. Compute the number Q of inversions
Input
Line 1: contains a positive integer n (1 <= n <= 10^6)
Line 2: contains a1, a2, ..., an (0 <= ai<= 10^6)
Output
Write the value Q modulo 10^9 +7
Example
Input
6
3 2 4 5 6 1
Output
6
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7, MAX = 1e6 + 5;
int n, a[MAX];
// the left and right array are allready sorted ascedingly
long long mergeAndCount(int arr[] ,int left, int mid, int right){
    int n1 = mid -left +1; //a[left] -> a[mid]
    int n2 = right - mid; //a[mid+1] -> a[right]

    int leftArr[n1], rightArr[n2];
    for(int i=0; i<n1; i++) leftArr[i] = arr[left + i];
    for(int i=0; i<n2; i++) rightArr[i] = arr[mid + 1 + i];

    int i=0, j=0, k=left;

    long long inversions = 0;
    while(i<n1 && j<n2){
        if(leftArr[i]<=rightArr[j]){
            arr[k++] = leftArr[i++];
        }else{
            arr[k++] = rightArr[j++];
            // All remaining elements in leftArr[i...n1-1] are greater than rightArr[j-1] since they are sorted ascedingly
            inversions = (inversions + n1 - i) % MOD;
        }
    }
    // Copy remaining elements of leftArr[] if any
    while(i<n1) arr[k++] = leftArr[i++];
    while(j<n2) arr[k++] = rightArr[j++];
    return inversions;
}

long long mergeSortAndCount(int arr[],int left, int right){
    long long inversions = 0;
    if(left<right){
        int mid = left + (right - left)/2;
        inversions += mergeSortAndCount(arr, left, mid);
        inversions %= MOD;
        inversions += mergeSortAndCount(arr, mid+1, right);
        inversions %= MOD;
        inversions += mergeAndCount(arr, left, mid, right);
        inversions %= MOD;
    }
    return inversions;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0; i<n; i++) cin >>a[i];
    long long res = mergeSortAndCount(a, 0, n-1);
    cout<<res<<'\n';
}