class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        if(nums.empty()) return -1;
        if(target == nums[left]) return left;
        else if(target == nums[right]) return right;
        bool normal = false;
        while(left != right) {
            int mid = (left + right) / 2;
            if(mid == left) return -1;
            if(target == nums[mid]) return mid;
            else if(nums[right] == nums[left] && normal) return -1;
            else if(normal) {
                if(target < nums[mid]) right = mid;
                else if(target > nums[mid]) left = mid;
                
            } else if(nums[mid] >= nums[left]){
                if(target > nums[left] && target > nums[mid]) left = mid;
                else if(target > nums[left] && target < nums[mid]){
                    right = mid;
                    normal = true; 
                } else if(target < nums[left] && target < nums[mid]) left = mid;
                else cout << "why?" << endl; 
            } else if(nums[mid] < nums[left]) {
                if(target > nums[left] && target > nums[mid]) right = mid;
                else if(target < nums[left] && target < nums[mid]) right = mid;
                else if(target < nums[left] && target > nums[mid]) {
                    left = mid;
                    normal = true;
                } else cout << "why?" << endl; 
                
            }
            
        }
        return -1;
        
    }
};