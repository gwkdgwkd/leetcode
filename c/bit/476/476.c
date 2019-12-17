int findComplement(int num){
    unsigned int n = 1;	/*防止数据溢出*/	
    while (n <=num)  n*=2; /*找到第一位 二进制1*/
    return (n-1)^ num; /*   (n/2*2-1)^num    */
}
