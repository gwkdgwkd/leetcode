/*
 * @lc app=leetcode.cn id=416 lang=c
 *
 * [416] 分割等和子集
 */

// @lc code=start

/*
// 官方题解
bool canPartition(int* nums, int numsSize) {
    if (numsSize < 2) {
        return false;
    }
    int sum = 0, maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        maxNum = fmax(maxNum, nums[i]);
    }
    if (sum & 1) {
        return false;
    }
    int target = sum / 2;
    if (maxNum > target) {
        return false;
    }
    int dp[numsSize][target + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < numsSize; i++) {
        dp[i][0] = true;
    }
    dp[0][nums[0]] = true;
    for (int i = 1; i < numsSize; i++) {
        int num = nums[i];
        for (int j = 1; j <= target; j++) {
            if (j >= num) {
                dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
        if(dp[i][target]) {
            return true;
        }
    }
    return dp[numsSize - 1][target];
}
*/

/*
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
        if(dp[i][sum]) {
            return true;
        }
    }
    return dp[numsSize][sum];
}

// 时间复杂度：
// 空间复杂度：O(n*sum)
*/

/*
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

    bool dp[sum + 1];
    dp[0] = true;
    for(int i = 1; i <= sum; ++i) {
        dp[i] = false;
    }
    

    for(int i = 0;i < numsSize;++i) {
        for(int j = sum; j >= 0; --j) {
            if(j >= nums[i]) {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
    }
    return dp[sum];
}
*/

// 官方题解，压缩空间
bool canPartition(int* nums, int numsSize) {
    if (numsSize < 2) {
        return false;
    }
    int sum = 0, maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        maxNum = fmax(maxNum, nums[i]);
    }
    if (sum & 1) {
        return false;
    }
    int target = sum / 2;
    if (maxNum > target) {
        return false;
    }
    int dp[target + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = true;
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        for (int j = target; j >= num; --j) {
            dp[j] |= dp[j - num];
        }
    }
    return dp[target];
}

// 空间复杂度：O(sum)

// @lc code=end

