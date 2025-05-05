/*
给两个二维整数数组nums1和nums2。
nums1[i] = [idi, vali]表示编号为idi的数字对应的值等于vali。
nums2[i] = [idi, vali]表示编号为idi的数字对应的值等于vali。
每个数组都包含互不相同的id，并按id以递增顺序排列。
请将两个数组合并为一个按id以递增顺序排列的数组，并符合下述条件：
只有在两个数组中至少出现过一次的id才能包含在结果数组内。
每个id在结果数组中只能出现一次，并且其对应的值等于两个数组中该id所对应的值求和。
如果某个数组中不存在该id，则假定其对应的值等于0。
返回结果数组。返回的数组需要按id以递增顺序排列。

示例1：
输入：nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
输出：[[1,6],[2,3],[3,2],[4,6]]
解释：结果数组中包含以下元素：
     id = 1，对应的值等于2 + 4 = 6。
     id = 2，对应的值等于3。
     id = 3，对应的值等于2。
     id = 4，对应的值等于5 + 1 = 6。

示例2：
输入：nums1 = [[2,4],[3,6],[5,5]], nums2 = [[1,3],[4,3]]
输出：[[1,3],[2,4],[3,6],[4,3],[5,5]]
解释：不存在共同id，在结果数组中只需要包含每个id和其对应的值。


提示：
1 <= nums1.length, nums2.length <= 200
nums1[i].length == nums2[j].length == 2
1 <= idi, vali <= 1000
数组中的id互不相同
数据均按id以严格递增顺序排列
*/

class Solution {
 public:
  vector<vector<int>> mergeArrays(vector<vector<int>>& nums1,
                                  vector<vector<int>>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    int i1 = 0;
    int i2 = 0;
    vector<vector<int>> ans;
    while (i1 < n1 && i2 < n2) {
      if (nums1[i1][0] < nums2[i2][0]) {
        ans.emplace_back(nums1[i1++]);
      } else if (nums1[i1][0] > nums2[i2][0]) {
        ans.emplace_back(nums2[i2++]);
      } else {
        ans.push_back({nums1[i1][0], nums1[i1][1] + nums2[i2][1]});
        ++i1;
        ++i2;
      }
    }
    while (i1 < n1) {
      ans.emplace_back(nums1[i1++]);
    }
    while (i2 < n2) {
      ans.emplace_back(nums2[i2++]);
    }
    return ans;
  }
};