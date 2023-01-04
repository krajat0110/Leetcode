class Solution {
public:
    int minimumRounds(vector<int>& A) {
         unordered_map<int, int> count;
        int res = 0;
        for (int a: A)
            ++count[a];
        for (auto& it: count) {
            if (it.second == 1) return -1;
             if(it.second%3==0){
                res += it.second/3;
            }
            else{
                res += it.second/3 + 1;
            }
        }
        return res;
    }
};