#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <queue>
#include <list>

using namespace std;

void reverse(vector<int> &arr, int i, int j)
{
    while (i < j)
    {
        swap(arr[i++], arr[j--]);
    }
}

void rotateByK(vector<int> &arr, int r)
{
    int n = arr.size();
    // r %= n;
    // if (r < 0)
    // r += n;

    r = (r % n + n) % n;

    reverse(arr, 0, n - 1);
    reverse(arr, n - r, n - 1);
    reverse(arr, 0, n - r - 1);
}

void segregatePositiveAndNegative(vector<int> &arr)
{
    int n = arr.size(), pt = -1, itr = 0;
    while (itr < n)
    {
        if (arr[itr] < 0)
            swap(arr[++pt], arr[itr]);
        itr++;
    }
}

void segregateZeroAndOne(vector<int> &arr)
{
    int n = arr.size(), pt = -1, itr = 0;
    while (itr < n)
    {
        if (arr[itr] == 0)
            swap(arr[++pt], arr[itr]);
        itr++;
    }
}

void segregateZeroAndOneAndTwos(int a[], int n)
{
    int pt1 = -1, idx = 0, pt2 = n - 1;

    while (idx <= pt2)
    {
        if (a[idx] == 0)
        {
            swap(a[++pt1], a[idx++]);
        }
        else if (a[idx] == 2)
        {
            swap(a[pt2--], a[idx]);
        }
        else
        {
            idx++;
        }
    }
}

// https://practice.geeksforgeeks.org/problems/max-sum-in-the-configuration/1/#

int max_sum(int A[], int N)
{
    int sum = 0, idxsum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += A[i];
        idxsum += A[i] * i;
    }

    int ans = idxsum;
    for (int i = 1; i < N; i++)
    {
        idxsum = idxsum - sum + A[i - 1] * N;
        ans = max(ans, idxsum);
    }
    return ans;
}

// 11. Container With Most Water
int maxArea(vector<int> &height)
{
    int n = height.size();
    int si = 0, ei = n - 1;
    int maxarea = 0;
    while (si < ei)
    {
        int h = min(height[ei], height[si]);
        int w = ei - si;

        int area = h * w;
        maxarea = max(maxarea, area);

        if (height[si] < height[ei])
        {
            si++;
        }
        else
        {
            ei--;
        }
    }
    return maxarea;
}

// 3. Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s)
{
    if (s.length() <= 1)
        return s.length();
    int n = s.length(), si = 0, ei = 0, len = 0, count = 0;
    vector<int> freq(128, 0);

    while (ei < n)
    {
        if (freq[s[ei++]]++ > 0)
        { // left left wala increment hoga then left wala
            count++;
            // 1. hgar condintion sahi hogi to cnt++ else not but these 2 will work fine then freq ++ then ei++
        }
        while (count > 0)
            if (freq[s[si++]]-- > 1)
                count--;

        len = max(len, ei - si);
    }
    return len;
}

// https://www.lintcode.com/problem/928/

int lengthOfLongestSubstringTwoDistinct(string &s)
{
    int n = s.size();
    if (n <= 2)
        return n;

    int si = 0, ei = 0, len = 0, cnt = 0;
    vector<int> freq(128, 0);

    while (ei < n)
    {
        if (freq[s[ei++]]++ == 0)
            cnt++;
        while (cnt > 2)
        {
            if (freq[s[si++]]-- == 1)
                cnt--;
        }
        len = max(len, ei - si);
    }
    return len;
}

// 76. Minimum Window Substring

string minWindow(string s, string t)
{
    int n1 = s.size(), n2 = t.size();
    if (n2 > n1)
        return "";
    vector<int> freq(128, 0);
    int si = 0, ei = 0, gsi = 0, len = (int)1e9, cnt = n2;

    for (int i = 0; i < n2; i++)
        freq[t[i]]++;

    while (ei < n1)
    {
        if (freq[s[ei++]]-- > 0)
            cnt--;
        while (cnt == 0)
        {
            if (ei - si < len)
            {
                len = ei - si;
                gsi = si;
            }
            if (freq[s[si++]]++ == 0)
                cnt++;
        }
    }
    return len == (int)1e9 ? "" : s.substr(gsi, len);
}

// 1456. Maximum Number of Vowels in a Substring of Given Length

bool isvovel(char ch)
{
    return ch == 'a' || ch == 'e' || ch == 'o' || ch == 'i' || ch == 'u';
}

int maxVowels(string s, int k)
{

    int si = 0, ei = 0, vovelcnt = 0, n = s.size(), maxvovelcnt = 0;

    while (ei < n)
    {
        if (isvovel(s[ei++]))
            vovelcnt++;

        if (ei - si == k)
        {
            maxvovelcnt = max(maxvovelcnt, vovelcnt);
            if (isvovel(s[si++]))
                vovelcnt--;
        }
    }
    return maxvovelcnt;
}

// 992. Subarrays with K Different Integers

int atMostKDistinct(vector<int> &arr, int k)
{
    vector<int> freq(20000 + 1);
    int n = arr.size(), si = 0, ei = 0, count = 0, ans = 0;

    while (ei < n)
    {
        if (freq[arr[ei++]]++ == 0)
            count++;

        while (count > k)
        {
            if (freq[arr[si++]]-- == 1)
                count--;
        }
        ans += ei - si;
    }

    return ans;
}

// second method
int atMostKDistinct(vector<int> &arr, int k)
{
    unordered_map<int, int> freq;
    int n = arr.size(), si = 0, ei = 0, ans = 0;

    while (ei < n)
    {
        freq[arr[ei++]]++;
        while (freq.size() > k)
        {
            if (freq[arr[si++]]-- == 1)
                freq.erase(arr[si - 1]);
        }

        ans += ei - si;
    }

    return ans;
}

int subarraysWithKDistinct(vector<int> &arr, int k)
{
    return atMostKDistinct(arr, k) - atMostKDistinct(arr, k - 1);
}

// practice.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1#

int longestKSubstr(string arr, int k)
{
    vector<int> freq(20000 + 1);
    int n = arr.size(), si = 0, ei = 0, len = 0, cnt = -1;

    while (ei < n)
    {
        if (freq[arr[ei++]]++ == 0)
            len++;

        if (len == k)
        {
            cnt = max(cnt, ei - si);
        }

        while (len > k)
        {
            if (freq[arr[si++]]-- == 1)
                len--;
        }
    }
    return cnt;
}

// 1248. Count Number of Nice Subarrays
int fxn(vector<int> &nums, int k)
{
    int si = 0, ei = 0, cnt = 0, ans = 0;
    int n = nums.size();
    while (ei < n)
    {

        if (nums[ei++] & 1 != 0)
            cnt++;

        while (cnt > k)
        {
            if (nums[si++] & 1 != 0)
                cnt--;
        }
        ans += ei - si;
    }
    return ans;
}

int numberOfSubarrays(vector<int> &nums, int k)
{
    return fxn(nums, k) - fxn(nums, k - 1);
}

// 904. Fruit Into Baskets
int totalFruit(vector<int> &fruits)
{
    int si = 0, ei = 0, cnt = 0, ans = 0, n = fruits.size();
    vector<int> freq(1000001, 0);

    while (ei < n)
    {
        if (freq[fruits[ei++]]++ == 0)
            cnt++;

        while (cnt > 2)
        {
            if (freq[fruits[si++]]-- == 1)
                cnt--;
        }
        ans = max(ans, ei - si);
    }
    return ans;
}

// 930. Binary Subarrays With Sum
int subarrycnt(vector<int> &nums, int goal)
{
    int si = 0, ei = 0, sum = 0, res = 0, n = nums.size();

    while (ei < n)
    {
        if (nums[ei++] == 1)
            sum += 1;

        while (sum > goal)
        {
            sum -= nums[si++];
        }
        res += ei - si;
    }
    return res;
}

int numSubarraysWithSum(vector<int> &nums, int goal)
{
    return subarrycnt(nums, goal) - (goal != 0 ? subarrycnt(nums, goal - 1) : 0);
}

// 485. Max Consecutive Ones
int findMaxConsecutiveOnes(vector<int> &arr)
{
    int n = arr.size(), ei = 0, si = 0, len = 0;
    while (ei < n)
    {
        if (arr[ei++] == 0)
        {
            si = ei;
        }

        len = max(len, ei - si);
    }
    return len;
}

// 883 · Max Consecutive Ones II
int findMaxConsecutiveOnes(vector<int> &nums)
{
    int si = 0, ei = 0, cnt = 0, len = 0;
    int n = nums.size();
    while (ei < n)
    {
        if (nums[ei++] == 0)
            cnt++;

        while (cnt > 1)
            if (nums[si++] == 0)
                cnt--;

        len = max(len, ei - si);
    }
    return len;
}

// 974. Subarray Sums Divisible by K
int subarraysDivByK(vector<int>& arr, int k) {
      unordered_map<int, int> rem;
        int long long  n=arr.size(),ei=0,sum=0,ans=0;
        rem[0]=1;
        while(ei<n){
            sum+=arr[ei++];
            
           int r = (sum % k + k ) % k;
            
            ans+= rem[r];
            rem[r]++;
        }
        return ans;
}

//974 modified tell the length of the max subarray

int longestSubarraysDivByK(vector<int> &arr, int k)
{
    vector<int> rem(k,-2);
    int n = arr.size(), ei = 0, sum = 0, len = 0;
    rem[0] = -1;
    while (ei < n)
    {
        sum += arr[ei];
        int r = (sum % k + k) % k;

        if (rem[r] == -2)
            rem[r] = ei;
        else
            len = max(len, ei - rem[r]);
        ei++;
    }
    return len;
}

// Subarrays with equal 1s and 0s

long long int countSubarrWithEqualZeroAndOne(int arr[], int n)
{
    unordered_map<int, int> mp;
    long long int pre_sum = 0, res = 0;

    mp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        arr[i] = arr[i] == 0 ? -1 : 1;
        pre_sum += arr[i];
        res += mp[pre_sum];
        //       cout<<pre_sum<<" " <<res<<" "<<mp[pre_sum]<<" -> ";
        mp[pre_sum]++;
        //       cout<<mp[pre_sum]<<endl;
    }
    return res;
}

// 239. Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    priority_queue<vector<int>> pq;
    vector<int> res;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {

        while (pq.size() != 0 && pq.top()[1] <= i - k)
            pq.pop();

        pq.push({nums[i], i}); // pq index ke basis pe he
                               //  cout<<nums[i]<<" "<< pq.top()[0]<<"->"<<pq.top()[1]<<endl;
        if (i >= k - 1)
            res.push_back(pq.top()[0]);
    }
    return res;
}

vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    list<int> dequeue;
    vector<int> res;
    int n = nums.size(), idx = 0;
    for (int i = 0; i < n; i++)
    {
        while (dequeue.size() != 0 && dequeue.front() <= i - k) // front ele exceed the window size
            dequeue.pop_front();

        while (dequeue.size() != 0 && nums[dequeue.back()] <= nums[i]) // if last ele small or equal to next ele
            dequeue.pop_back();

        dequeue.push_back(i);

        if (i >= k - 1)
        {
            cout << i << " " << dequeue.front() << endl;
            res.push_back(nums[dequeue.front()]);
        }
    }
    return res;
}

int kadanesAlgo(vector<int>nums){
    int gsum = -1e9 , csum = 0;
    for(auto ele : nums){
        csum+=ele;
        if(csum > gsum){
            gsum = csum;
        }
        if(csum <= 0){
            csum = 0;
        }
    }
   return gsum;
}

// [-1,-7,-8,-9] -> max sum Subarray if -1 (0,0);
 int kadanesAlgoGeneric(vector<int> arr)
{
    int gSum = -(int)1e9, cSum = 0;
    for (int ele : arr)
    {
        cSum = max(ele, cSum + ele);
        gSum = max(gSum, cSum);
    }

    return gSum;
}

int kadanesAlgo_SubArray(vector<int>arr){
    int res = 0 , csum = 0 ,gsum = -1e9 , n = arr.size() , gsi = 0 , gei = 0 , csi = 0;
    for(int i = 0 ; i < n ;i++){ 
       csum += arr[1];
    if(gsum < csum){
       gsum = csum;

       gsi = csi;
       gei = i;
      }
    if(csum <= 0){
        csum = 0;
        csi = i+1;
     }    
    }
   return gsum;
}

// 1191. K-Concatenation Maximum Sum

int mod = (int)1e9 + 7;

int kadansalgo(vector<int> &arr, int k)
{
    long csum = 0, gsum = 0;
    int n = arr.size();
    for (int i = 0; i < k * n; i++)
    {
        int ele = arr[i % n];
        csum += ele;

        if (csum > gsum)
            gsum = csum;
        if (csum <= 0)
            csum = 0;
    }
    return (int)gsum % mod;
}

int kConcatenationMaxSum(vector<int> &arr, int k)
{
    long sum = 0, prevsum = 0;
    for (int i = 1; i <= 3; i++)
    { // to know tha AP series pattern
        prevsum = sum;
        sum = kadansalgo(arr, i);
        if (i == k) // means k agar 3 se chota ho to
            return (int)sum;
    }
    return (int)((prevsum + (k - 2) * (sum - prevsum)) % mod);
}

// https://practice.geeksforgeeks.org/problems/maximum-sum-rectangle2948/1#

int maximumSumRectangle(int R, int C, vector<vector<int>> M)
{
    int ans1 = -1e9;
    for (int k = 0; k < R; k++)
    {
        vector<int> ans(C, 0);
        for (int i = k; i < R; i++)
        {
            for (int j = 0; j < C; j++)
                ans[j] += M[i][j];
            int res = kadanesAlgoGeneric(ans);
            ans1 = max(ans1, res);
        }
    }
    return ans1;
}

//if we want to print matrix 

vector<int> kadanesAlgoGenericSubarray(vector<int> &arr)
{
    int gSum = -(int)1e9, cSum = 0, gsi = 0, gei = 0, csi = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        int ele = arr[i];
        cSum += ele;
        if (ele >= cSum)
        {
            cSum = ele;
            csi = i;
        }

        if (cSum > gSum)
        {
            gSum = cSum;
            gsi = csi;
            gei = i;
        }
    }

    return vector<int> {gSum, gsi, gei};
}

int maximumSumRectangle_02(int R, int C, vector<vector<int>> M)
{
    int maxSum = -(int)1e9;
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    for (int fixRow = 0; fixRow < R; fixRow++)
    {
        vector<int> colPrefixSum(C, 0);
        for (int row = fixRow; row < R; row++)
        {
            for (int col = 0; col < C; col++)
                colPrefixSum[col] += M[row][col];

            vector<int> res = kadanesAlgoGenericSubarray(colPrefixSum);
            if (res[0] >= maxSum)
            {
                maxSum = res[0];
                r1 = fixRow;
                c1 = res[1];
                r2 = row;
                c2 = res[2];
            }
        }
    }
    for (int i = r1; i <= r2; i++)
    {
        for (int j = c1; j <= c2; j++)
        {
           cout<<M[i][j] <<" ";
        }
        cout<<endl;
    }

    return maxSum;
}

// https://leetcode.com/problems/rabbits-in-forest/
int numRabbits(vector<int> &answers)
{
    vector<int> map(999 - 0 + 1, 0); //range  = [999 , 0];
    int ans = 0;
    for (auto ele : answers)
    {
        if (map[ele] == 0)
            ans += ele + 1;

        map[ele]++;

        if (map[ele] == ele + 1)
            map[ele] = 0;
    }
    return ans;
}

// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
int countsubarray(vector<int> &colPrefixSum, int tar)
{
    unordered_map<int, int> map;
    map[0] = 1;
    int count = 0, sum = 0;
    for (auto ele : colPrefixSum)
    {
        sum += ele;
        count += map.find(sum - tar) != map.end() ? map[sum - tar] : 0;
        map[sum]++;
    }
    return count;
}

int numSubmatrixSumTarget(vector<vector<int>> &mat, int tar)
{
    int R = mat.size(), C = mat[0].size();
    int count = 0;
    for (int fixRow = 0; fixRow < R; fixRow++)
    {
        vector<int> colPrefixSum(C, 0);
        for (int row = fixRow; row < R; row++)
        {
            for (int col = 0; col < C; col++)
                colPrefixSum[col] += mat[row][col];
            count += countsubarray(colPrefixSum, tar);
        }
    }
    return count;
}

// https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/

class Solution {
public:  
    int kadanesAlgoWithSumUnderK(vector<int> arr, int k) {
        int gsum = -(int) 1e9, csum = 0;
        for (int ele : arr) {
            csum += ele;
            csum = max(csum, ele);
            gsum = max(gsum, csum);

            if (gsum >= k)
                return gsum;
        }

        return gsum;
}
    
    int maxSumSubmatrix(vector<vector<int>>& arr, int k) {
        int n = arr.size(), m = arr[0].size();
        int maxRes = -1e9;

        for (int fixedRow = 0; fixedRow < n; fixedRow++) {
            vector<int> prefixColArray (m,0);
            for (int row = fixedRow; row < n; row++) {
                for (int col = 0; col < m; col++)
                    prefixColArray[col] += arr[row][col];
                int sum = kadanesAlgoWithSumUnderK(prefixColArray, k);
                if (sum == k)
                    return sum;
                else if (sum < k) {
                    maxRes = max(maxRes, sum);
                    continue;
                }
             // Otherwise, try binary search of running sums
               int cur_sum = 0;
                set<int> s{0};
                for (auto& sum: prefixColArray)
                {
                    cur_sum += sum;
                    auto it = s.lower_bound(cur_sum - k);
                    if (it != s.end())
                        maxRes = max(maxRes, cur_sum - *it);
                    if (maxRes == k)
                        return k;
                    s.insert(cur_sum);
                }
            }
        }
        return maxRes;
    }
};
        