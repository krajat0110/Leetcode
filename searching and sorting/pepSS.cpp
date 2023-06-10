#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include <cmath>
using namespace std;

//34
vector<int> searchRange(vector<int> &nums, int target)
{
    int start = 0, end = nums.size(), mid, left, right;

    while (start < end)
    {
        mid = (start + end) / 2;
        if (nums[mid] >= target)
            end = mid;
        else
            start = mid + 1;
    }

    left = end;

    start = 0, end = nums.size();
    while (start < end)
    {
        mid = (start + end) / 2;
        if (nums[mid] > target)
            end = mid;
        else
            start = mid + 1;
    }

    right = start;

    return left == right ? vector<int>{-1, -1} : vector<int>{left, right - 1};
}

// 35. Search Insert Position
int searchInsert(vector<int> &nums, int target)
{
    int n = nums.size(), si = 0, ei = n - 1;

    while (si <= ei)
    {
        int mid = si + (ei - si) / 2;

        if (nums[mid] == target)
            return mid;

        if (nums[mid] > target)
        {
            ei = mid - 1;
        }
        else
        {
            si = mid + 1;
        }
    }
    return si;
}

int nearestElement(vector<int> &arr, int target)
{
   int n = arr.size();
   if(n == 0 ) return -1;

   if(n == 1) return arr[0];

   if(target <= arr[0]  || target >= arr[n-1]){
       return target <= arr[0] ? arr[0] : arr[n-1];
   }

   int si = 0 , ei = n - 1;
   while(si <= ei){
     int mid = (ei + si)/2;

     if(arr[mid] == target) return arr[mid];

     if(arr[mid] > target){
        mid = ei - 1;
     }else{
        si = mid + 1;
     }
   }
   return target - arr[ei] <= target - arr[si] ? arr[ei] : arr[si];
}

// 74. Search a 2D Matrix
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size(), m = matrix[0].size();
    int si = 0, ei = n * m - 1;
    while (si <= ei)
    {
        int mid = (ei + si) / 2;
        int r = mid / m, c = mid % m;
        if (matrix[r][c] == target)
            return true;
        if (matrix[r][c] > target)
        {
            ei = mid - 1;
        }
        else
        {
            si = mid + 1;
        }
    }
    return false;
}

bool searchMatrix_02(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size(), m = matrix[0].size(), si = n - 1, ei = 0;
    while (si >= 0 && ei < m)
    {
        int ele = matrix[si][ei];
        if (ele == target)
            return true;
        ele > target ? si-- : ei++;
    }
    return false;
}

// https://leetcode.com/problems/search-a-2d-matrix-ii/

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size(), m = matrix[0].size(), si = n - 1, ei = 0;
    while (si >= 0 && ei < m)
    {
        int ele = matrix[si][ei];
        if (ele == target)
            return true;
        ele > target ? si-- : ei++;
    }
    return false;
}

// https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1/

long long inversionAcrossArray(vector<long long> &arr, int l, int r, int mid, vector<long long> &sortedArray)
{
    int lsi = l, lei = mid;
    int rsi = mid + 1, rei = r;
    // cout<<lsi<<" "<<lei<<"->"<<rsi<<" "<<rei<<endl;
    int k = 0;
    long cnt = 0;
    while (lsi <= lei && rsi <= rei)
    {
        if (arr[lsi] > arr[rsi])
        {
            cnt += (lei - lsi + 1);
            sortedArray[k++] = arr[rsi++];
        }
        else
            sortedArray[k++] = arr[lsi++];
    }
    while (lsi <= lei)
        sortedArray[k++] = arr[lsi++];

    while (rsi <= rei)
        sortedArray[k++] = arr[rsi++];
    k = 0;
    for (int i = l; i <= r; i++)
        arr[i] = sortedArray[k++];
    return cnt;
}

long long inversionCount01(vector<long long> &arr, int si, int ei, vector<long long> &sortedArray)
{
    if (si >= ei) return 0;

    int mid = (si + ei) / 2;

    long ICL = inversionCount01(arr, si, mid, sortedArray);
    long ICR = inversionCount01(arr, mid + 1, ei, sortedArray);

    return (ICR + ICL + inversionAcrossArray(arr, si, ei, mid, sortedArray));
}

long long inversionCount(long long ar[], long long N)
{
    if (N <= 1) return 0;
    vector<long long> arr;
    for (int i = 0; i < N; i++)
        arr.push_back(ar[i]);

    vector<long long> sortedArray(N, 0);
    return inversionCount01(arr, 0, (int)N - 1, sortedArray);
}

// https://leetcode.com/problems/search-in-rotated-sorted-array/

int search(vector<int> &nums, int target)
{
    int si = 0, n = nums.size(), ei = n - 1;
    while (si <= ei)
    {
        int mid = (si + ei) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[si] <= nums[mid])
        {
            if (nums[si] <= target && target < nums[mid])
                ei = mid - 1;
            else
                si = mid + 1;
        }
        else
        {
            if (target > nums[mid] && target <= nums[ei])
                si = mid + 1;
            else
                ei = mid - 1;
        }
    }
    return -1;
}

// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
bool search1(vector<int> &nums, int target)
{
    int n = nums.size();
    int si = 0, ei = n - 1;
    while (si <= ei)
    {
        int mid = (si + ei) / 2;
        if (nums[mid] == target)
            return true;
        if ((nums[si] == nums[mid]) && (nums[mid] == nums[ei]))
        {
            --ei; ++si;
        }
        else if (nums[si] <= nums[mid]){
            if (nums[si] <= target && nums[mid] > target)
                ei = mid - 1;
            else
                si = mid + 1;
        }else{
            if (nums[ei] >= target && nums[mid] < target)
                si = mid + 1;
            else
                ei = mid - 1;
        }
    }
    return false;
}

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

int findMin(vector<int> &nums)
{
    int n = nums.size();
    int si = 0, ei = n - 1;
    while (si < ei)
    {
        int mid = (si + ei) / 2;

        if (nums[ei] > nums[mid])
        {
            ei = mid;
        }
        else
        {
            si = mid + 1;
        }
    }
    return nums[si];
}

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/

int findMin(vector<int> &nums)
{
    int n = nums.size();
    int si = 0, ei = n - 1;
    while (si < ei)
    {
        int mid = (si + ei) / 2;

        if (nums[ei] > nums[mid])
        {
            ei = mid;
        }
        else if (nums[mid] > nums[ei])
        {
            si = mid + 1;
        }
        else
            ei--;
    }
    return nums[si];
}

// https://leetcode.com/problems/find-k-closest-elements/

int insertPos(vector<int> arr, int val)
{
    int n = arr.size(), si = 0, ei = n - 1;

    while (si <= ei)
    {
        int mid = (si + ei) / 2;

        if (arr[mid] > val)
            ei = mid - 1;
        else
            si = mid + 1;
    }
    return si;
}

vector<int> findClosestElements(vector<int> &arr, int k, int x)
{
    int n = arr.size();

    if (x <= arr[0])
    {
        return {arr.begin(), arr.begin() + k};
    }
    else if (x >= arr[n - 1])
    {
        return {arr.end() - k, arr.end()};
    }
    int idx = insertPos(arr, x);
    int si = max(0, idx - k);
    int ei = min(idx + k, n - 1);

    while ((ei - si + 1) > k)
    {
        if ((x - arr[si]) > (arr[ei] - x))
            si++;
        else
            ei--;
    }
    return {arr.begin() + si, arr.begin() + ei + 1};
}

//if he ask answer with only unique element then we will expand the window size

// https://leetcode.com/problems/longest-increasing-subsequence/

int insertPos1(vector<int> &nums, int val)
{
    int n = nums.size(), si = 0, ei = n - 1;

    while (si <= ei)
    {
        int mid = (ei + si) / 2;

        if (nums[mid] <= val)
            si = mid + 1;
        else
            ei = mid - 1;
    }

    int insertidx = si;
    int lastidx = si - 1;

    return lastidx >= 0 && nums[lastidx] == val ? lastidx : insertidx;
}

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();

    if (n <= 1)
        return n;
    vector<int> list;
    for (int ele : nums)
    {
        int idx = insertPos1(list, ele);
        if (idx == list.size())
            list.push_back(ele);
        else
            list[idx] = ele;
    }
    return list.size();
}

// https://leetcode.com/discuss/interview-question/348510/Google-or-OA-2019-or-Maximum-Area-Serving-Cake

bool ispossibleAreaCake(vector<int> &nums, double Cakearea, int guest)
{
    int g = 0, n = nums.size();
    for (int i = n - 1; i >= 0; i--)
    {
        double area = M_PI * nums[i] * nums[i];

        g += floor(area / Cakearea);
        if (g >= guest)
            return true;
    }
    return false;
}

double ispossibleArea(vector<int> &arr, int guest)
{
   // sort(arr.begin(), arr.end());
    int n = arr.size();
  //  double si = (M_PI * arr[0] * arr[0]) / guest , ei = M_PI * arr[n - 1] * arr[n - 1];
     double si = 0.0, ei = 1e7;
    while ((ei - si) > 1e-5)
    { // 1e^-5 buz given that we what the ans in 1e6 range
        double cakearea = (si + ei) / 2.0;
        if (!ispossibleAreaCake(arr, cakearea, guest))
            ei = cakearea - 1e-5;
        else
            si = cakearea;
    }
    return si ;
}

// 848 · Minimize Max Distance to Gas Station

bool IsCorrectPanelty(vector<int> &stations, double distance, int k)
{
    int d = 0, n = stations.size();
    for (int i = 1; i < n; i++)
    {
        d += (stations[i] - stations[i - 1]) / distance;
        if (d > k)
            return false;
    }
    return true;
}



double minmaxGasDist(vector<int> &stations, int k)
{
    double si = 0.0, ei = 1e9;
    while ((ei - si) > 1e-6)
    {
        double distance = (ei + si) / 2.0;
        if (!IsCorrectPanelty(stations, distance, k))
        {
            si = distance + 1e-6;
        }
        else
            ei = distance;
    }
    return si;
}

void fxn(){
    vector<int> val = {4,3,3};
    double ans = ispossibleArea(val, 3);
    cout << ans << endl;
}

int main(){
    fxn();
    return 0;
}