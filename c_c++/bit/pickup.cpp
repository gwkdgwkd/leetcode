#include <bitset>
#include <iostream>

int x = 124;
int y = 567;

namespace n1 {
// 位运算基本功能

namespace test1 {
// &运算通常用于二进制取位操作

void func1() {
  // 一个数&1的结果就是取二进制的最末位，这可以用来判断一个整数的奇偶，
  // 二进制的最末位为0表示该数为偶数，最末位为1表示该数为奇数。
  std::cout << std::bitset<8>(3 & 1) << std::endl;  // 0001
  std::cout << std::bitset<8>(4 & 1) << std::endl;  // 0000

  if (5 % 2 == 1) {  // 写成n%2的形式，编译器也会自动帮我们优化成位运算
    std::cout << "5 is odd number" << std::endl;
  }
  if (5 & 1 == 1) {
    std::cout << "5 is odd number" << std::endl;
  }
  // 5 is odd number
  // 5 is odd number
}

void func2() {
  // 通常用来将某变量中的某些位清零而保留其他位不变

  // 如果需要将int型变量n的低8位全置成0，而其余位不变，则可以执行：
  int n = 0xffffffff;
  std::cout << std::bitset<32>(n) << std::endl;
  // 11111111111111111111111111111111

  std::cout << std::bitset<32>(n & 0xffffff00) << std::endl;
  // 11111111111111111111111100000000
  // 如果n是short类型的，则用n&0xff00
}

void func3() {
  // ​如果要判断一个int型的变量n的第7位（从右往左，从0开始数）是否为1，
  // 则只需看表达式n&0x80的值是否等于0x80即可：
  std::cout.setf(std::ios_base::boolalpha);
  std::cout << bool(0xff & 0x80) << std::endl;  // true
  std::cout << bool(0x0f & 0x80) << std::endl;  // false
}

void func() {
  func1();
  func2();
  func3();
}
}  // namespace test1

namespace test2 {
// |运算通常用于二进制特定位上的无条件赋值

void func1() {
  std::cout << std::bitset<8>(x) << std::endl;  // 01111100
  std::cout << std::bitset<8>(y) << std::endl;  // 00110111

  // 一个数|1的结果就是把二进制最末位强行变成1：
  std::cout << std::bitset<8>(x | 1) << std::endl;  // 01111101
  std::cout << std::bitset<8>(y | 1) << std::endl;  // 00110111

  // 如果需要把二进制最末位变成0，对这个数|1之后再减一就可以了，
  // 其实际意义就是把这个数强行变成最接近的偶数：
  std::cout << std::bitset<8>((x | 1) - 1) << std::endl;  // 01111100
  std::cout << std::bitset<8>((y | 1) - 1) << std::endl;  // 00110110
}

void func2() {
  // ​通常用来将变量中的某些位置成1，而保留其他位不变

  // 如果需要int型变量n的低8位全置成1，而其余位不变，则可以执行：
  int n = 0x12345678;
  std::cout << std::bitset<32>(n) << std::endl;
  std::cout << std::bitset<32>(n | 0xff) << std::endl;
  // 00010010001101000101011001111000
  // 00010010001101000101011011111111
}

void func() {
  func1();
  func2();
}
}  // namespace test2

namespace test3 {
// ^运算通常用于对二进制的特定一位进行取反操作，因为异或可以这样定义：
// 0和1异或0都不变，异或1则取反，异或运算支持运算的交换律和结合律。

void func() {
  // 两个相同的数异或之后结果会等于0：
  std::cout << (x ^ x) << std::endl;  // 0

  // 并且任何数与0异或等于它本身：
  std::cout << (x ^ 0) << std::endl;  // 124

  // ^运算的逆运算是它本身，也就是说两次异或同一个数最后结果不变：
  std::cout << (x ^ y ^ y) << std::endl;  // 124

  // ​异或运算的特点是：​如果a^b==c，那么c^b==a以及c^a==b都成立，
  // 此规律可以用来做最简单的快速加密和解密：
  int z = x ^ y;
  std::cout << (x ^ y) << " = " << z << std::endl;  // 587 = 587
  std::cout << (x ^ z) << " = " << y << std::endl;  // 567 = 567
  std::cout << (z ^ y) << " = " << x << std::endl;  // 124 = 124
}
}  // namespace test3

namespace test4 {
// 非运算的定义是把内存中的0和1全部取反。
// 使用非运算时要格外小心，需要注意整数类型有没有符号。

void func() {
  int n = 0x12345678;
  std::cout << std::bitset<32>(n) << std::endl;
  std::cout << std::bitset<32>(~n) << std::endl;
  // 00010010001101000101011001111000
  // 11101101110010111010100110000111
}
}  // namespace test4

namespace test5 {
void func() {
  int n = 0x12345678;
  std::cout << std::bitset<32>(n) << std::endl;
  std::cout << std::bitset<32>(n << 1) << std::endl;
  std::cout << std::bitset<32>(n >> 2) << std::endl;
  // 00010010001101000101011001111000
  // 00100100011010001010110011110000
  // 00000100100011010001010110011110

  // 对于有符号数，如long、int、short、char类型变量，在右移时，
  // 符号位(即最高位)将一起移动，并且大多数C/C++编译器规定，
  // 如果原符号位为1，则右移时右边高位就补充1，原符号位为0，则右移时高位就补充0：
  int a = -123;
  std::cout << std::bitset<32>(a) << std::endl;
  std::cout << std::bitset<32>(a >> 1) << std::endl;
  std::cout << std::bitset<32>(a << 1) << std::endl;
  // 11111111111111111111111110000101
  // 11111111111111111111111111000010
  // 11111111111111111111111100001010

  // 左移1位，就等于是乘以2，左移n位，就是乘以2的n次方，比乘法操作快的多：
  std::cout << "8 << 1 = " << (8 << 1) << std::endl;  // 8 << 1 = 16
  // 右移n位，就相当于左操作数除以2的n次方，并且将结果往小里取整：
  std::cout << "8 >> 2 = " << (8 >> 2) << std::endl;  // 8 >> 2 = 2
}
}  // namespace test5

namespace test6 {
/*
| 功能                 | 示例                   | 位运算                  |
| ------------------  | ---------------------  | ---------------------- |
| 去掉最后一位          | (101101->10110)        | x >> 1                 |
| 在最后加一个0         | (101101->1011010)      | x << 1                 |
| 在最后加一个1         | (101101->1011011)      | x << 1+1               |
| 把最后一位变成1       | (101100->101101)       | x | 1                  |
| 把最后一位变成0       | (101101->101100)       | x | 1-1                |
| 最后一位取反          | (101101->101100)       | x ^ 1                  |
| 把右数第k位变成1      | (101001->101101,k=3)   | x | (1 << (k-1))       |
| 把右数第k位变成0      | (101101->101001,k=3)   | x & ~(1 << (k-1))      |
| 右数第k位取反         | (101001->101101,k=3)   | x ^ (1 << (k-1))       |
| 取末三位             | (1101101->101)         | x & 7                  |
| 取末k位              | (1101101->1101,k=5)    | x & (1 << k-1)         |
| 取右数第k位           | (1101101->1,k=4)       | x >> (k-1) & 1         |
| 把末k位变成1          | (101001->101111,k=4)   | x | (1 << k-1)         |
| 末k位取反            | (101001->100110,k=4)    | x ^ (1 << k-1)         |
| 把右边连续的1变成0    | (100101111->100100000)  | x & (x+1)              |
| 把右起第一个0变成1    | (100101111->100111111)  | x | (x+1)              |
| 把右边连续的0变成1    | (11011000->11011111)    | x | (x-1)              |
| 取右边连续的1        | (100101111->1111)       | (x ^ (x+1)) >> 1       |
| 去掉右起第一个1的左边 | (100101000->1000)       | x & (x ^ (x-1))         |
*/
void func() {}
}  // namespace test6
}  // namespace n1

namespace n2 {
// 几个有趣的位操作
}

namespace n3 {
// 算法常用操作
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << argv[0] << " i [0 - 4]" << std::endl;
    return 0;
  }
  int type = atoi(argv[1]);
  switch (type) {
    case 0:
      n1::test1::func();
      break;
    case 1:
      n1::test2::func();
      break;
    case 2:
      n1::test3::func();
      break;
    case 3:
      n1::test4::func();
      break;
    case 4:
      n1::test5::func();
      break;
    case 5:
      n1::test6::func();
      break;
    case 6:
      break;
    case 7:
      break;
    default:
      std::cout << "invalid type" << std::endl;
      break;
  }

  return 0;
}

// 位运算的黑科技
// http://graphics.stanford.edu/~seander/bithacks.html#ReverseParallel