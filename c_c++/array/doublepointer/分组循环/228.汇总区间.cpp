/*
给定一个无重复元素的有序整数数组nums。
返回恰好覆盖数组中所有数字的最小有序区间范围列表。
也就是说，nums的每个元素都恰好被某个区间范围所覆盖，
并且不存在属于某个范围但不属于nums的数字x。
列表中的每个区间范围[a,b]应该按如下格式输出：
"a->b"，如果a != b
"a"，如果a == b

示例1：
输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
     [0,2] --> "0->2"
     [4,5] --> "4->5"
     [7,7] --> "7"

示例2：
输入：nums = [0,2,3,4,6,8,9]
输出：["0","2->4","6","8->9"]
解释：区间范围是：
     [0,0] --> "0"
     [2,4] --> "2->4"
     [6,6] --> "6"
     [8,9] --> "8->9"


提示：
0 <= nums.length <= 20
-2^31 <= nums[i] <= 2^31 - 1
nums中的所有值都互不相同
nums按升序排列
*/

class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    int n = nums.size();
    int left = 0;
    int right = 1;
    vector<string> ans;
    if (n == 0) {
      return ans;
    }
    while (right < n) {
      if (nums[right] != 1 + nums[right - 1]) {
        if (right == left + 1) {
          ans.push_back(to_string(nums[left]));
        } else {
          ans.push_back(to_string(nums[left]) + "->" +
                        to_string(nums[right - 1]));
        }
        left = right;
      }
      ++right;
    }

    if (right == left + 1) {
      ans.push_back(to_string(nums[left]));
    } else {
      ans.push_back(to_string(nums[left]) + "->" + to_string(nums[right - 1]));
    }
    return ans;
  }
};

// 分组循环
class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    vector<string> ret;
    int i = 0;
    int n = nums.size();
    while (i < n) {
      int low = i;
      i++;
      while (i < n && nums[i] == nums[i - 1] + 1) {
        i++;
      }
      int high = i - 1;
      string temp = to_string(nums[low]);
      if (low < high) {
        temp.append("->");
        temp.append(to_string(nums[high]));
      }
      ret.push_back(move(temp));
    }
    return ret;
  }
};
