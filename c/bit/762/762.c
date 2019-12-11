int isPrime(int num) {
    if(num<2) return 0;
    for(int i=2;i*i<=num;i++)//这里注意使用sqrt的效率较低，可使用i*i提高效率；
    {
        if(num%i==0) return 0;
    }
    return 1;
}
int countPrimeSetBits(int L, int R){
    int i;
    int num = 0;

    for(i = L; i <=R; ++i) {
        int a = i;
        int count = 0;
        while(a > 0) {
            ++count;
            a &= (a - 1);
        }

        if(isPrime(count)) {
            ++num;
        }
    }
    return num;
}
