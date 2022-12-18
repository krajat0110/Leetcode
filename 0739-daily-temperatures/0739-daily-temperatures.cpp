class Solution {
public:
      
    vector<int> dailyTemperatures(vector<int>& arr) {
     int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        while (s.size() != 0 && arr[s.top()] < arr[i])
        {
            ans[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
        
         for(int i = 0 ; i < n ; i++){
             if(ans[i] == -1){
                 ans[i] = 0;
             }
             else{
            ans[i] = ans[i] - i;
             }
        }
    return ans;
    }
};