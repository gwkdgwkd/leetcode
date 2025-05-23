/*
给一个长度为n的整数数组nums和一个二维数组queries，其中queries[i]=[li,ri]。
每一个queries[i]表示对于nums的以下操作：
将nums中下标在范围[li,ri]之间的每一个元素最多减少1。
坐标范围内每一个元素减少的值相互独立。
零数组指的是一个数组里所有元素都等于0。
请返回最多可以从queries中删除多少个元素，
使得queries中剩下的元素仍然能将nums变为一个零数组。
如果无法将nums变为一个零数组，返回-1。

示例1：
输入：nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
输出：1
解释：删除queries[2]后，nums仍然可以变为零数组。
     对于queries[0]，将nums[0]和nums[2]减少1，将nums[1]减少0。
     对于queries[1]，将nums[0]和nums[2]减少1，将nums[1]减少0。

示例2：
输入：nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
输出：2
解释：可以删除queries[2]和queries[3]。

示例3：
输入：nums = [1,2,3,4], queries = [[0,3]]
输出：-1
解释：nums无法通过queries变成零数组。


提示：
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
1 <= queries.length <= 10^5
queries[i].length == 2
0 <= li <= ri < nums.length
*/

class Solution {
 public:
  int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
    ranges::sort(queries, {},
                 [](auto& q) { return q[0]; });  // 按照左端点从小到大排序
    int n = nums.size(), j = 0, sum_d = 0;
    vector<int> diff(n + 1, 0);
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
      sum_d += diff[i];
      // 维护左端点<=i的区间
      while (j < queries.size() && queries[j][0] <= i) {
        pq.push(queries[j][1]);
        j++;
      }
      // 选择右端点最大的区间
      while (sum_d < nums[i] && !pq.empty() && pq.top() >= i) {
        sum_d++;
        diff[pq.top() + 1]--;
        pq.pop();
      }
      if (sum_d < nums[i]) {
        return -1;
      }
    }
    return pq.size();
  }
};

class Solution {
 public:
  int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
    sort(
        queries.begin(), queries.end(),
        [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

    priority_queue<int> heap;
    vector<int> deltaArray(nums.size() + 1, 0);
    int operations = 0;
    for (int i = 0, j = 0; i < nums.size(); ++i) {
      operations += deltaArray[i];
      while (j < queries.size() && queries[j][0] == i) {
        heap.push(queries[j][1]);
        ++j;
      }
      while (operations < nums[i] && !heap.empty() && heap.top() >= i) {
        operations += 1;
        deltaArray[heap.top() + 1] -= 1;
        heap.pop();
      }
      if (operations < nums[i]) {
        return -1;
      }
    }
    return heap.size();
  }
};