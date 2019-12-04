int singleNumber(int* nums, int numsSize){
    int i,ret = 0;
    for(i = 0; i < numsSize; ++i) {
        ret ^= nums[i];
    }

	return ret;
}
