int hammingDistance(int x, int y){
    int count = 0;
    int diff = x ^ y;

    while(diff) {
        diff &= diff - 1;
        count ++;
    }
    
    return count;
}
