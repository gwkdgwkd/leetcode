char findTheDifference(char * s, char * t){
    char sum = 0;

    while(*s != 0 || *t != 0) {
        if(*s != 0) {
            sum ^= *s++;
        }
        if(*t != 0) {
            sum ^= *t++;
        }
    }

    return sum;
}
