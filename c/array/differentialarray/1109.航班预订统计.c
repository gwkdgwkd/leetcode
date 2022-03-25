/*
这里有n个航班，它们分别从1到n进行编号。
有一份航班预订表bookings，表中第i条预订记录bookings[i]=[firsti,lasti,seatsi]意味着
在从firsti到lasti（包含firsti和lasti）的每个航班上预订了seatsi个座位。
请你返回一个长度为n的数组answer，里面的元素是每个航班预定的座位总数。

示例1：
输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
输出：[10,55,45,25,25]
解释：
航班编号        1   2   3   4   5
预订记录 1 ：   10  10
预订记录 2 ：       20  20
预订记录 3 ：       25  25  25  25
总座位数：      10  55  45  25  25
因此，answer = [10,55,45,25,25]

示例 2：
输入：bookings = [[1,2,10],[2,2,15]], n = 2
输出：[10,25]
解释：
航班编号        1   2
预订记录 1 ：   10  10
预订记录 2 ：       15
总座位数：      10  25
因此，answer = [10,25]

提示：
1 <= n <= 2 * 104
1 <= bookings.length <= 2 * 104
bookings[i].length == 3
1 <= firsti <= lasti <= n
1 <= seatsi <= 104
*/

// 差分数组
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize,
                        int n, int* returnSize) {
  int* nums = malloc(sizeof(int) * n);
  memset(nums, 0, sizeof(int) * n);
  *returnSize = n;

  for (int i = 0; i < bookingsSize; i++) {
    nums[bookings[i][0] - 1] += bookings[i][2];
    if (bookings[i][1] < n) {
      nums[bookings[i][1]] -= bookings[i][2];
    }
  }

  for (int i = 1; i < n; i++) {
    nums[i] += nums[i - 1];
  }

  return nums;
}