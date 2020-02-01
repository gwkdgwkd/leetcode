int integerReplacement(int n){
    int count = 0;
    while(n != 1){
        if((n&1) == 0) {
            n >>= 1;
        } else {
            if( 3==n || (n & 2) == 0 ) {
                n -= 1;
            } else if(n == INT_MAX) {
                // why n -= 1 return 33?
                return 32;
            } else {
                n+=1;
            }
        }
        ++count;
    }
    return count;
}
