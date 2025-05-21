/*
产品经理目前正在带领一个团队开发新的产品。
不幸的是，产品的最新版本没有通过质量检测。
由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
假设有n个版本[1, 2, ..., n]，想找出导致之后所有版本出错的第一个错误的版本。
可以通过调用isBadVersion接口来判断版本号version是否在单元测试中出错。
实现一个函数来查找第一个错误的版本。应该尽量减少对调用API的次数。

示例1：
输入：n = 5, bad = 4
输出：4
解释：调用isBadVersion(3) -> false
     调用isBadVersion(5) -> true
     调用isBadVersion(4) -> true
     所以，4是第一个错误的版本。

示例2：
输入：n = 1, bad = 1
输出：1


提示：
1 <= bad <= n <= 2^31 - 1
*/

class Solution {
 public:
  int firstBadVersion(int n) {
    int left = 1;
    int right = n;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (isBadVersion(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};