class Solution {
public:
    int search(vector<int>& nums, int tar) {
        int si = 0 , ei = nums.size()-1;
        while(si <= ei){
            int mid = (si + ei)/2;
            
            if(nums[mid] == tar) return mid;
            if(nums[mid] < tar){
                si = mid + 1; 
            }else{
                ei = mid - 1;
            }
        }
        return -1;
    }
};