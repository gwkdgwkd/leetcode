/*
 * @lc app=leetcode.cn id=416 lang=c
 *
 * [416] 分割等和子集
 */

// @lc code=start



bool canPartition(int* nums, int numsSize){
    int sum = 0;
    for(int i = 0;i < numsSize;++i) {
        sum += nums[i];
    }
    if(sum%2) {
        return false;
    }else {
        sum /= 2;
    }

    bool dp[numsSize+1][sum + 1];
    for(int i = 0;i<numsSize + 1;++i) {
        dp[i][0] = true;
    }
    for(int i = 1;i<sum +1;++i) {
        dp[0][i] = false;
    }

    for(int i = 1;i <= numsSize;++i) {
        for(int j =1;j<=sum;++j ) {
if(nums[i-1] > j) {
    
                dp[i][j] = dp[i-1][j];
            } else{
                dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
            }
        }
    }
    return dp[numsSize][sum];
}
// @lc code=end

