int singleNumber(int* nums, int numsSize){
    // 数字电路的思路
    // int one = 0, two = 0, temp = 0;
    // for (int i = 0; i < numsSize; ++i) {
    //     temp = (two & nums[i]) | (one & ~nums[i]);
    //     two = (~one & ~two & nums[i]) | (two & ~nums[i]);
    //     one = temp;
    // }
    // return two;

    // int one = 0, two = 0, three = 0;
    // for (int i = 0; i < numsSize; ++i) {
    //     two |= one & nums[i]; // 二进制某位出现1次时twos = 0，出现2, 3次时twos = 1；
    //     one ^= nums[i];  // 二进制某位出现2次时ones = 0，出现1, 3次时ones = 1；
    //     three = one & two; // 二进制某位出现3次时（即twos = ones = 1时）three = 1，其余即出现1, 2次时three = 0；
    //     one &= ~three; // 将二进制下出现3次的位置零，实现`三进制下不考虑进位的加法`；
    //     two &= ~three;
    // }
    // return one;

    int one = 0, two = 0;
    for (int i = 0; i < numsSize; ++i) {
        /*
         * 当num=1时，只当 one=two=0时将one置1，代表出现3N+1次；其余置0，根据two值分别代表出现3N次和3N+2次；
         * 当num=0时，one不变。
         */
        one = one ^ nums[i] & ~two;
        /*
         * 当num=1时，只当one=two=0时将two置1，代表出现3N+2次；其余置0，根据one值分别代表出现3N次和3N+1次；
         * 当num=0时，twos不变。
         */
        two = two ^ nums[i] & ~one;
    }
    return one;
}
