/*
给两个整数数组nums1和nums2。
从nums1中移除两个元素，并且所有其他元素都与变量x所表示的整数相加。
如果x为负数，则表现为元素值的减少。
执行上述操作后，nums1和nums2相等。
当两个数组中包含相同的整数，并且这些整数出现的频次相同时，两个数组相等。
返回能够实现数组相等的最小整数x。

示例1:
输入：nums1 = [4,20,16,12,8], nums2 = [14,18,10]
输出：-2
解释：移除nums1中下标为[0,4]的两个元素，并且每个元素与-2相加后，
     nums1变为[18,14,10]，与nums2相等。

示例2:
输入：nums1 = [3,5,5,3], nums2 = [7,7]
输出：2
解释：移除nums1中下标为[0,3]的两个元素，并且每个元素与2相加后，
     nums1变为[7,7]，与nums2相等。


提示：
3 <= nums1.length <= 200
nums2.length == nums1.length - 2
0 <= nums1[i], nums2[i] <= 1000
测试用例以这样的方式生成：
存在一个整数x，nums1中的每个元素都与x相加后，再移除两个元素，nums1可以与nums2相等。
*/

class Solution {
 public:
  int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
    // 把两个数组都从小到大排序：
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    int n = nums1.size();
    int m = nums2.size();

    // 由于只能移除两个元素，所以nums1​的前三小元素必定有一个是保留下来的，
    // 可以枚举保留下来的最小元素是nums1​[0]还是nums1​[1]还是nums1​[2]，
    // 先判断保留下来的最小元素是nums1​[2]，再判断是nums1​[1]，最后判断是nums1​[0]。
    // 这是因为nums1​[i]越大，答案x越小，第一个满足的就是答案。
    for (int i = 2; i >= 0; --i) {
      int x = nums2[0] - nums1[i];
      int j = 0;
      for (int k = i; k < n; ++k) {
        if (j < m && nums2[j] == nums1[k] + x) {
          ++j;
        }
      }
      if (j == m) {
        return x;
      }
    }

    // 由于题目保证答案一定存在，所以当nums1​[2]和nums1​[1]都不满足时，
    // 直接返回nums2​[0]−nums1​[0]，无需判断：
    // return nums2[0] - nums1[0];  // 如果把i>=0改成i>0，那么返回这个

    return 0;  // 走不到
  }
};