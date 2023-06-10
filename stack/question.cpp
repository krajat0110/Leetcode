#include <iostream>
#include <stack>
#include <vector>
#include<unordered_map>
using namespace std;

void display(vector<int> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << endl;
    }
}

// next , greater  on right
vector<int>NGOR(vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        while (s.size() != 0 && arr[s.top()] < arr[i])
        {
            ans[s.top()] = arr[i];
            s.pop();
        }
        s.push(i);
    }
    return ans;
}

//nextgreater on left
vector<int> NGOL(vector<int> &arr)
{
    int n = arr.size();
    vector<int>ans(n, -1);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--)
    {
        while (s.size() != 0 && arr[s.top()] < arr[i])
        {
            ans[s.top()] = arr[i];
            s.pop();
        }
        s.push(i);
    }
    return ans;
}

//nextsmaller on right
vector<int> NSOR(vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        while (s.size() != 0 && arr[s.top()] > arr[i])
        {
            ans[s.top()] = arr[i];
            s.pop();
        }
        s.push(i);
    }
    return ans;
}

// next smaller on left
vector<int> NSOL( vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--)
    {
        while (s.size() != 0 && arr[s.top()] > arr[i])
        {
            ans[s.top()] = arr[i];
            s.pop();
        }
        s.push(i);
    }
    return ans;
}

//leetcode 496
class Solution
{
public:
    vector<int> NGOR(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> ans(n, -1);
        stack<int> s;
        for (int i = 0; i < n; i++)
        {
            while (s.size() != 0 && arr[s.top()] < arr[i])
            {
                ans[s.top()] = arr[i];
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }

    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> ngr = NGOR(nums2);

        unordered_map<int, int> hm;

        // nums -> key  ngr -> value
        for (int i = 0; i < nums2.size(); i++)
        {
            hm.emplace(nums2[i], ngr[i]);
        }

        vector<int> ans(nums1.size());

        for (int i = 0; i < nums1.size(); i++)
        {
            ans[i] = hm[nums1[i]];
        }

        return ans;
    }
};

//leetcode 503
vector<int> nextGreaterElements(vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans(n, -1);

    stack<int> s;

    for (int i = 0; i < 2 * n; i++)
    {
        while (s.size() != 0 && arr[s.top()] < arr[i % n])
        {
            ans[s.top()] = arr[i % n];
            s.pop();
        }
        if (i < n)
            s.push(i);
    }
    return ans;
}

//leetcode 20

bool isValid(string str)
{
    if ((str.size() & 1))
    {
        return false;
    }
    stack<char> s;
    for (auto ele : str)
    {
        if (ele == '(' || ele == '{' || ele == '[')
        {
            s.push(ele);
        }
        else
        {
            if (s.empty() || (ele == ')' && s.top() != '(') || (ele == '}' && s.top() != '{') || (ele == ']' && s.top() != '['))
                return false;
            s.pop();
        }
    }
    return s.empty();
}

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<int> nge(n, 0);
    nge = NGOR(arr);
    display(nge);
    return 0;
}