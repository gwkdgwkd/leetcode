/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* singleNumber(int* nums, int numsSize, int* returnSize){
    int x = 0;
    for(int i = 0; i < numsSize; ++i)
        x ^= nums[i]; //结果为两个只有一个的数的异或，即表示两个数不同
    int *arr = (int *)calloc(2,sizeof(int));
    x = x & (-x); //求lowbit，两个数右边第一个不同的位
    for(int i = 0; i < numsSize; ++i){
        if((nums[i] & x) == x) arr[0] ^= nums[i]; // 一个数与所有的异或，结果为一个数
        else arr[1] ^= nums[i]; //另一个数与所有的异或，结果为另一个数
    }
    
    *returnSize = 2;
    return arr;
}
