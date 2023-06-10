#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

// int higest(int *arr, int n)
// {
//     unordered_map<int, int> hf;

//     for (int i = 0; i < n; i++)
//     {
//        if(hf.count(arr[i])>0)
//        hf[arr[i]] +=1;
//        else hf[arr[i]] = 1;
//    }
//     unordered_map<int,int> :: iterator it;
//     it=hf.begin();
//    int max= it->second;
//    int key= it->first;
//    it++;
//    while(it!=hf.end())
//    {
//        if(max<it->second)
//        {
//            max=it->second;
//            key=it->first;   
//        }
//        it++;
//    }
//     if(max==1)
//     return arr[0];
//     else
//     return key;
// }
int main(){

    int n;
    cin >> n;

    int *arr = new int[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    cout<< "hello world";

    delete[] arr;
}