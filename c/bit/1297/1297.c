int cmp (const void* a, const void* b) {
    return strcmp(*((char**)a), *((char**)b));
}
bool checkMaxLetters(char * s, int maxLetters, int start, int end) {
    int chr[26] = {0};
    int i;
    int n = 0;
    for (i = start; i < end; i++) {
        if (chr[s[i] - 'a'] != 0) {
            continue;
        }
        n++;
        chr[s[i] - 'a'] = 1;
        if (n > maxLetters) {
            return false;
        }
    }
    return true;
}

int maxFreq(char * s, int maxLetters, int minSize, int maxSize){
    int i;
    int L = strlen(s);
    char ** letterInfo = malloc(sizeof(char*) * (L - minSize + 1));
    int lInfoLen = 0;
    int ret = 1;
    int k = 1;

    for (i = 0; i <= L - minSize; i++) {
        if (checkMaxLetters(s, maxLetters, i, i + minSize)) {
            letterInfo[lInfoLen++] = &s[i];
        }
    }
    if (lInfoLen <= 1) {
        free(letterInfo);
        return lInfoLen;
    }

    qsort(&letterInfo[0], lInfoLen, sizeof(char *), cmp);

    for (i = 1; i < lInfoLen; i++) {
        if (strncmp(letterInfo[i], letterInfo[i - 1], minSize) == 0) {
            k++;
        } else {
            k = 1;
        }
        ret = ret > k ? ret : k;
    }
    free(letterInfo);
    return ret;
}
