int getSum(int a, int b){
    while (b) {
        auto carry = ((unsigned int ) (a & b))<<1 ; // 记录a+b的进位，直到进位为0是退出
        a = a^b;   //结果相
        b = carry;  //循环
    }
    return a;
}
