bool hasAlternatingBits(int n){
    n = (n ^ (n>>1)); //如果n位1111，那么返回true
    return (n & ((long)n+1)) == 0; //判断n是否位1111，这样的数
}
