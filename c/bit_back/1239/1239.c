int cmp(const void *a, const void *b)
{
    char *ta = *(char **)a;
    char *tb = *(char **)b;
    if (strlen(ta) == strlen(tb)) {
        return strcmp(ta, tb);
    }
    return strlen(tb) - strlen(ta);
}

int getCharBitmap(char *arr, int size, int bitmap) 
{
    int tmpBitmap = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (bitmap & (1 << (arr[i] - 'a')))  {
            return 0;
        }
        if (tmpBitmap & (1 << (arr[i] - 'a'))) {
            return 0;
        }
        tmpBitmap |= (1 << (arr[i] - 'a'));
    }
    return tmpBitmap;
}

int maxLength(char ** arr, int arrSize){
    int bitmap = 0;
    int tmpBitmap = 0;
    int rltSize = 0;
    int tmpSize = 0;;
    int i, j;
    qsort(arr, arrSize, sizeof(char *), cmp);
    for (i = 0; i < arrSize; i++) {
        bitmap = getCharBitmap(arr[i], strlen(arr[i]), 0);
        if (bitmap == 0) {
            continue;
        }
        tmpSize = strlen(arr[i]);
        for (j = 0; j < arrSize; j++) {
            tmpBitmap = getCharBitmap(arr[j], strlen(arr[j]), bitmap);
            if (tmpBitmap == 0) {
                continue;
            }
            bitmap |= tmpBitmap;
            tmpSize += strlen(arr[j]);
        }
        if (tmpSize > rltSize) {
            rltSize = tmpSize;
        }
    }
    return rltSize;
}
