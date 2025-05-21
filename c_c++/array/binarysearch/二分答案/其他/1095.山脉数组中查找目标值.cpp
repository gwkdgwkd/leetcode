/*
可以将一个数组arr称为山脉数组当且仅当：
arr.length >= 3
存在一些0 < i < arr.length - 1的i使得：
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
给定一个山脉数组mountainArr，返回最小的index使得mountainArr.get(index)==target。
如果不存在这样的index，返回-1。
无法直接访问山脉数组。只能使用MountainArray接口来访问数组：
MountainArray.get(k)返回数组中下标为k的元素（从0开始）。
MountainArray.length()返回数组的长度。
调用MountainArray.get超过100次的提交会被判定为错误答案。
此外，任何试图绕过在线评测的解决方案都将导致取消资格。

示例 1：
输入：mountainArr = [1,2,3,4,5,3,1], target = 3
输出：2
解释：3 在数组中出现了两次，下标分别为2和5，我们返回最小的下标2。

示例2：
输入：mountainArr = [0,1,2,4,2,1], target = 3
输出：-1
解释：3在数组中没有出现，返回-1。


提示：
3 <= mountainArr.length() <= 10^4
0 <= target <= 10^9
0 <= mountainArr.get(index) <= 10^9
*/

class Solution {
  int binary_search(MountainArray &mountain, int target, int l, int r,
                    int key(int)) {
    target = key(target);
    while (l <= r) {
      int mid = (l + r) / 2;
      int cur = key(mountain.get(mid));
      if (cur == target) {
        return mid;
      } else if (cur < target) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return -1;
  }

 public:
  int findInMountainArray(int target, MountainArray &mountainArr) {
    // 有一个单调递增序列（峰值左边）和一个单调递减序列（峰值右边），
    // 只是不知道两个序列的分割点，即峰值在哪里，所以第一步应该首先找到峰值：
    int l = 0, r = mountainArr.length() - 1;
    while (l < r) {
      int mid = (l + r) / 2;
      // 对于一个范围[l,r]，可以先找到范围[l,r]中间连续的两个点mid与mid+1。
      // 如果mountainArr.get(mid + 1)>mountainArr.get(mid)，
      // 那么可以知道峰值在范围[mid + 1, r]内；
      // 如果mountainArr.get(mid + 1)<mountainArr.get(mid)，
      // 那么可以知道峰值在范围[l, mid]内。
      if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }

    int peak = l;
    // 在峰值左边使用二分法寻找目标值：
    int index = binary_search(mountainArr, target, 0, peak,
                              [](int x) -> int { return x; });
    if (index != -1) {
      return index;
    }

    // 如果峰值左边没有目标值，那么使用二分法在峰值右边寻找目标值：
    return binary_search(mountainArr, target, peak + 1,
                         mountainArr.length() - 1,
                         [](int x) -> int { return -x; });
  }
};