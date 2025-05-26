/*
给定一个整数数组nums，处理以下类型的多个查询：
计算索引left和right（包含left和right）之间的nums元素的和，其中left<=right

实现NumArray类：
NumArray(int[] nums) 使用数组nums初始化对象
int sumRange(int i, int j)返回数组nums中索引left和right之间的元素的总和，
包含left和right两点（也就是nums[left]+nums[left + 1]+...+nums[right])

示例1：
输入：
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
输出：
[null, 1, -1, -3]
解释：
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1))
numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))

提示：
1 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5
0 <= i <= j < nums.length
最多调用10^4次sumRange方法
*/

#include <stdio.h>
#include <stdlib.h>

// 前缀和主要适用的场景是原始数组不会被修改的情况下，频繁查询某个区间的累加和
typedef struct {
  int* pre;
} NumArray;
NumArray* numArrayCreate(int* nums, int numsSize) {
  NumArray* na = (NumArray*)malloc(sizeof(NumArray));
  na->pre = (int*)calloc(numsSize + 1, sizeof(int));

  // for(int i = 1; i < numsSize + 1; ++i) {
  //     na->pre[i] = na->pre[i - 1] + nums[i - 1];
  // }
  for (int i = 0; i < numsSize; i++) {
    na->pre[i + 1] = na->pre[i] + nums[i];
  }

  return na;
}
int numArraySumRange(NumArray* obj, int left, int right) {
  return obj->pre[right + 1] - obj->pre[left];  // 查询闭区间[left,right]累加和
}
void numArrayFree(NumArray* obj) {
  free(obj->pre);
  free(obj);
}

#include <vector>
using namespace std;

/*
比如nums=[1,2,3,4,5,6]，要想计算子数组[3,4,5]的元素和，
可以用前缀[1,2,3,4,5]的元素和，减去另一个前缀[1,2]的元素和，
就得到了子数组[3,4,5]的元素和，即3+4+5=(1+2+3+4+5)−(1+2)
换句话说，把前缀[1,2,3,4,5]的前缀[1,2]去掉，就得到了子数组[3,4,5]。
一般地，任意子数组都是一个前缀去掉前缀后的结果。
所以任意子数组的和，都可以表示为两个前缀和的差。
nums的子数组有O(n^2)个，但只有O(n)个前缀。
那么，预处理nums的所有前缀和，就可以O(1)计算任意子数组的元素和。

为方便描述，把nums记作a，设其长度为n。
对于数组a，计算它的长为n+1的前缀和数组s，即a的前0个数的和，前1个数的和，
前2个数的和……前n个数的和。
s[0]​=0
s[1]=a[0]
s[2]=a[0]+a[1]
⋮
s[i]=a[0]+a[1]+⋯+a[i−1]
s[i+1]=a[0]+a[1]+⋯+a[i−1]+a[i]
⋮
s[n]=a[0]+a[1]+⋯+a[n−1]​
根据这个定义，前i个数的和，加上a[i]，就是前i+1个数的和，即s[i+1]=s[i]+a[i]

为什么要定义s[0]=0，这样做有什么好处？
如果left=0，要计算的子数组是一个前缀（从a[0]到a[right]）。
按照公式，我们要用s[right+1]减去s[0]。如果不定义s[0]=0，就必须特判left=0的情况了。
通过定义s[0]=0，任意子数组（包括前缀）都可以表示为两个前缀和的差。
此外，如果a是空数组，定义s[0]=0的写法是可以兼容这种情况的。
*/
class NumArray {
  vector<int> pre;

 public:
  NumArray(vector<int>& nums) {
    int n = nums.size();
    pre.resize(n + 1);  // pre[i]表示元素i前面所有元素的和
    pre[0] = 0;         // pre[0]前面没有元素，所有为0
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i] + nums[i];
    }
  }

  int sumRange(int left, int right) {
    // pre[left]表示nums[0]到nums[left-1]所有元素的和，不包括nums[left]，
    // pre[right+1]表示nums[0]到nums[right]所有元素的和，包括nums[right]，
    // (nums[0]...nums[left]...nums[right]) - (nums[0]...nums[left-1])，
    // 所以pre[right + 1] - pre[left] = nums[left]...nums[right]
    return pre[right + 1] - pre[left];
  }
};

int main() {
  int a[] = {-2, 0, 3, -5, 2, -1};
  NumArray* na = numArrayCreate(a, sizeof(a) / sizeof(int));
  for (int i = 0; i < sizeof(a) / sizeof(int) + 1; ++i) {
    printf("%d ", na->pre[i]);
  }
  printf("\n");
  // 0 -2 -2 1 -4 -2 -3

  printf("%d\n", numArraySumRange(na, 0, 2));  // 1
  printf("%d\n", numArraySumRange(na, 2, 5));  // -1
  printf("%d\n", numArraySumRange(na, 0, 5));  // -3
  numArrayFree(na);

  return 0;
}