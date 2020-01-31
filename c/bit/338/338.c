/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* countBits(int num, int* returnSize){
    int *ret = (int *)malloc((num + 1)*sizeof(int));
    *returnSize = num +1;
    ret[0] = 0;
    for(int i = 1;i<=num;++i) {
        if(i%2 == 0) {
            ret[i] = ret[i/2];
        } else {
            ret[i] = ret[i/2] + 1;
        }
    }


    return ret;
}

// int* countBits(int num, int* returnSize){
//     int *ret = (int *)malloc((num + 1)*sizeof(int));
//     *returnSize = num +1;
//     for(int i = 0;i<=num;++i) {
//         ret[i] = get_count(i);
//     }
//     return ret;
// }
// int get_count(int num) {
//     int count = 0;
//     while(num) {
//         num = num & (num - 1);
//         ++count;
//     }

//     return count;
// }
