int totalHammingDistance(int* nums, int numsSize){
    if (numsSize <= 0)
        return 0;

    int ans = 0,k;       
    int cnt[32] = {0};                     // count of elements with a particular bit ON

    for (k = 0; k < numsSize; ++k) {         // loop over every element
        int i = 0;
        while (nums[k] > 0) {           // check every bit
            cnt[i] += (nums[k] & 0x1);
            nums[k] >>= 1;
            i++;
        }
    }

    for (k = 0; k < 32; ++k) {           // loop over every bit count
        ans += cnt[k] * (numsSize - cnt[k]);
    }

    return ans;
}
