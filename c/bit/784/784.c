/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCasePermutation(char * S, int* returnSize){
    int count = 0,i = 0;
    int len = strlen(S);

    while(S[i]) {
        if(isalpha(S[i])) {
            ++count;
        }
        ++i;
    }

    int max = 1 << count;
    *returnSize = max;
    char **ret = (char **)malloc(sizeof(char *) * max);

    for(int mask = 0;mask < max;++mask) {
        ret[mask] = (char *)malloc(len + 1);
        memset(ret[mask],0,len+1);
        modifyString(S, mask,len,ret[mask]);
    }
    return ret;
}
    
void modifyString(char *src, int mask,int len,char *ret){
    for(int i = 0; i < len; i++) {
        if(isalpha(src[i])) {
            if(mask & 1) {
                ret[i] = src[i]^32;
                //ret[i] = src[i]^(1<<5);
            } else {
                ret[i] = src[i];
            }
            mask >>= 1;
        } else {
            ret[i] = src[i];
        }
    }
}
