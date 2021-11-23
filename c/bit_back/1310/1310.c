/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize){

    /**
     *   利用位运算的性质  a ⊕ a = 0;可以利用这个性质加上前缀和抵消区间前段。
     *   定义前缀和如下。
     *   preSum[i] = arr[0] ⊕ arr[1] ⊕ ... ⊕ arr[i];
     *   preSum[j] = arr[0] ⊕ arr[1] ⊕ ... ⊕ arr[i] ⊕ arr[i+1] ... ⊕ arr[j]; (i <= j)
     *   则 query[i, j] = (preSum[j] ⊕ preSum[i]) ⊕ arr[i] = arr[i] ⊕ arr[i+1] ⊕ ... ⊕ arr[j]
     */
    int preSum[arrSize];
    preSum[0] = arr[0];

    for(int idx = 1; idx < arrSize; ++idx){
        preSum[idx] = preSum[idx-1] ^ arr[idx];
    }

    int *ret = (int *)malloc(queriesSize*sizeof(int));
    memset(ret,0,queriesSize*sizeof(int));
    *returnSize = queriesSize;

    for(int idx = 0; idx < queriesSize; ++idx){
        int left = queries[idx][0],right = queries[idx][1];
        ret[idx] = preSum[right] ^ preSum[left] ^ arr[left];
    }

    return ret;
}
