#include <iostream>
#include <vector>

using namespace std;

int permutationinfinitecoin(vector<int> arr, int tar, string ans)
{
    if (tar == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (auto ele : arr)
    {
        if (tar - ele >= 0) //agar target se small he to continue
            count += permutationinfinitecoin(arr, tar - ele, ans + to_string(ele));
    }
    return count;
}

int combinationinfinitecoins(vector<int> arr, int tar, int idx, string ans)
{
    if (tar == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = idx; i < arr.size(); i++)
    {
        if (tar - arr[i] >= 0)
            count += combinationinfinitecoins(arr, tar - arr[i], i, ans + to_string(arr[i]));
    }
    return count;
}

int combinationsinglecoins(vector<int> arr, int tar, int idx, string ans)
{
    if (tar == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < arr.size(); i++)
    { // idx hoga to value fix rahegi or for loop 0 se nahi chalega 0 se chalega to infini coin ka sol de dega
        if (tar - arr[i] >= 0)
            count += combinationsinglecoins(arr, tar - arr[i], i + 1, ans + to_string(arr[i]));
    }
    return count;
}

int permutationsinglecoins(vector<int> arr, int tar, string ans)
{
    if (tar == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > 0 && tar - arr[i] >= 0)
        {
            int val = arr[i];
            arr[i] = -val;
            count += permutationsinglecoins(arr, tar - val, ans + to_string(val));
            arr[i] = val;
        }
    }
    return count;
}

//================================================================================================//
// using subsequence method

int permutationinfinitecoin_sub(vector<int> arr, int tar, int idx, string ans)
{
    if (tar == 0 || idx == arr.size())
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if (tar - arr[idx] >= 0)
    {
        count += permutationinfinitecoin_sub(arr, tar - arr[idx], 0, ans + to_string(arr[idx]));
        count += permutationinfinitecoin_sub(arr, tar, idx + 1, ans);
    }
    return count;
}

int combinationinfinitecoins_sub(vector<int> arr, int tar, int idx, string ans)
{
    if (tar == 0 || idx == arr.size())
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if (tar - arr[idx] >= 0)
    {
        count += combinationinfinitecoins_sub(arr, tar - arr[idx], idx, ans + to_string(arr[idx]));
        count += combinationinfinitecoins_sub(arr, tar, idx + 1, ans);
    }
    return count;
}

int combinationsinglecoins_sub(vector<int> arr, int tar, int idx, string ans)
{
    if (tar == 0 || idx == arr.size())
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    if (tar - arr[idx] >= 0)
    {
        count += combinationsinglecoins_sub(arr, tar - arr[idx], idx + 1, ans + to_string(arr[idx]));
        count += combinationsinglecoins_sub(arr, tar, idx + 1, ans);
    }
    return count;
}

int permutationsinglecoins_sub(vector<int> arr, int tar, int idx, string ans)
{
    if (tar == 0 || idx == arr.size())
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if (arr[idx] > 0 && tar - arr[idx] >= 0)
    {
        int val = arr[idx];
        arr[idx] = -val;
        count += permutationsinglecoins_sub(arr, tar - val, idx + 1, ans + to_string(val));
        arr[idx] = val;
    }
    count += permutationsinglecoins_sub(arr, tar, idx + 1, ans);

    return count;
}

void rtree()
{
    vector<int> arr = {2, 3, 5, 7};
    int tar = 10;
    string ans = "";
      cout << permutationinfinitecoin(arr, tar, ans);
    // cout<<endl<<"@"<<endl;
    //  cout << combinationinfinitecoins(arr, tar, 0, ans);
    // cout << combinationsinglecoins(arr, tar, 0, ans);
    // cout << permutationsinglecoins(arr, tar, ans);
}

void subtree()
{
    vector<int> arr = {2, 3, 5, 7};
    int tar = 10;
    string ans = "";
    // cout << permutationinfinitecoin_sub(arr, tar, 0, ans);
    // cout << combinationinfinitecoins_sub(arr, tar, 0, ans);
    // cout << combinationsinglecoins_sub(arr, tar, 0, ans);
    // cout << permutationsinglecoins_sub(arr, tar,0,ans);
}

//================================================================//

int main()
{
    rtree();
   // subtree();
    return 0;
}
