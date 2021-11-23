int missingNumber(int* nums, int numsSize){
    int i;
    int sum = 0;

    for(i = 0; i < numsSize; ++i) {
        sum ^= i^nums[i];
    }
    sum ^= i;

    return sum;
}
