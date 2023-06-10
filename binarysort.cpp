#include<iostream>
using namespace std;

int find_key(int a[], int n , int key){
    int s=0;
    int e=n-1;
    while(s<=e){
    int mid = (s + e)/2;
    if(a[mid]==key){
        return mid;
    }
   else if(a[s]<=a[mid]){
       if(a[s]<=key and   key<=a[mid]){
         e= mid - 1;
       }
        else {
          s = mid +1;
         }
       }
    else {
        if(a[mid]<=key and key <= a[e]){
            s=mid+1;
        }
        else {
            e=mid-1;
        }
    }
 }
}

int main( ){
    int n;
    int key;
    int a[100000];
    cin>>n;
  for(int i=0;i<=n;i++){
      cin>>a[i];
  }
  cout<<"the the element you want to find"<<endl;
   cin>>key;
    cout<<find_key(a,n,key);
}
