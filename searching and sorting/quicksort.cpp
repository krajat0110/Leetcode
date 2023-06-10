#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
using namespace std;


int segregateData(vector<int> &arr, int si, int ei, int pivot)
{
   swap(arr[pivot] , arr[ei]);
   int p = si - 1 , idx = si; 
   while(idx <= ei){
       if(arr[idx] <= arr[ei])
        swap(arr[++p] , arr[idx]); 
       idx++;
   }
   return p;
}

void quickSort(vector<int> &arr, int si, int ei)
{
    if(si > ei) return;
    int pivot = ei; //it can be si , ei , random

    int pidx = segregateData(arr , si , ei , pivot);
    quickSort(arr, si, pidx - 1);
    quickSort(arr,pidx + 1, ei);
}

int main()
{
    vector<int> arr = {-12, 2, 7, 4, 34, 23, 0, 1, -1, -50, 16, 23, 7, 4, 2, 3};
    quickSort(arr, 0, arr.size() - 1);

    for (int ele : arr)
        cout << ele << " ";
}
