int majorityElement(int* nums, int numsSize){
    if (numsSize < 3) return nums[0];
    
    int m = nums[0];
    for (int i = 1, c = 1; i != numsSize; i++) {
        if (c == 0) {
            m = nums[i];
        }
        nums[i] == m ? c++ : c--;
    }
    return m;
}
