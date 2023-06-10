#include <iostream>
using namespace std;

void mergesort(int arr1[], int size1, int arr2[], int size2, int ans[]){

    int i = 0, j = 0, k = 0;
    while (i<size1 && j<size2){
        if(arr1[i] < arr2[j]){
            ans[k] = arr1[i];
            i++;
        }
        else{
            ans[k] = arr2[j];
            j++;
        }
        k++;
    }
    while(i < size1){
        ans[k] = arr1[i];
        k++;
        i++;
    }
    while(j < size2){
        ans[k] = arr2[j];
        k++;
        j++;
    }
}
int main()
{
	int t;
	cin >> t;

	while (t--)
	{
		int size1;
		cout<<" input the size of arr1 ";
		cin >> size1;

		int *arr1 = new int[size1];

       cout<<"enter the element of 1 array"<<endl;
		for (int i = 0; i < size1; i++)
		{
			cin >> arr1[i];
		}

		int size2;
        cout<<" input the size of arr2 ";
		cin >> size2;

		int *arr2 = new int[size2];
       cout<<"enter the element of 2 array"<<endl;
		for (int i = 0; i < size2; i++)
		{
			cin >> arr2[i];
		}

		int *ans = new int[size1 + size2];

		mergesort(arr1, size1, arr2, size2, ans);

        cout<<"mergerd sorted array"<<endl;

		for (int i = 0; i < size1 + size2; i++)
		{
			cout << ans[i] << " ";
		}

		cout << endl;
		delete[] arr1;
		delete[] arr2;
		delete[] ans;
	}
}
