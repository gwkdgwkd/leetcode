/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int count = 1 << numsSize;
    *returnSize = count;
    int **ret = (int **)malloc(sizeof(int*)*count);
    returnColumnSizes[0] = (int *)malloc(sizeof(int)*count);

    for(int mask = 0;mask < count;++mask) {
        int n = get1nums(mask);
        ret[mask] = (int *)malloc(sizeof(int)*n);
        returnColumnSizes[0][mask] = n;
        int j = 0;
        for(int i=0;i<numsSize;++i){
            if(mask&(1<<i)){
                ret[mask][j++] = nums[i];
            }
         }
    }

    return ret;
}

int get1nums(int num) {
    int count = 0;
    while(num) {
        num &= (num - 1);
        ++count;
    }
    return count;
}

// int count(int num, int k) {
//     int i = 0, count = 0;
//     for(i = 0; i < k; i++) {
//         if(num & 1)
//             count++;
//         num >>= 1;
//     }
//     return count;
// }

// int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
//     int size = 1, i = 0, j = 0, k = 0;
//     int t = (int)pow(2, numsSize);
//     *returnSize = t;
//     int** result = (int**)malloc(t * sizeof(int*));
//     returnColumnSizes[0] = (int*)malloc(t * sizeof(int));  
//     for(i = 0; i < t; i++) {
//         returnColumnSizes[0][i] = count(i, numsSize);
//         result[i] = (int*)malloc(returnColumnSizes[0][i] * sizeof(int));
//         k = i;
//         size = 0;
//         for(j = 0; j < numsSize; j++) {
//             if(k & 1)
//                 result[i][size++] = nums[j];
//             k >>= 1;
//         }
//     }
    
//     return result;
// }
