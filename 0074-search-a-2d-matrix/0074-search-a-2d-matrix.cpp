class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) { //2d matric ko 1d matrix me assure kiya he 
        int n = matrix.size() , m = matrix[0].size();
        int si = 0 , ei = n * m - 1; // si = 0 , ei = last ele of matrix 
        while(si <= ei){
            int mid = (ei + si)/2;
            int r = mid/m , c = mid%m;
            if(matrix[r][c] == target) return true;
            if(matrix[r][c]>target){
                ei = mid - 1;
            }else{
                si = mid + 1;
            }
        }
        return false;
    }
};