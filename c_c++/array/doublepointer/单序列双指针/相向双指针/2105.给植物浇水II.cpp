/*
Alice和Bob打算给花园里的n株植物浇水。
植物排成一行，从左到右进行标记，编号从0到n - 1。
其中，第i株植物的位置是x = i。
每一株植物都需要浇特定量的水。
Alice和Bob每人有一个水罐，最初是满的。他们按下面描述的方式完成浇水：
Alice按从左到右的顺序给植物浇水，从植物0开始。
Bob按从右到左的顺序给植物浇水，从植物n - 1开始。他们同时给植物浇水。
无论需要多少水，为每株植物浇水所需的时间都是相同的。
如果Alice/Bob水罐中的水足以完全灌溉植物，他们必须给植物浇水。
否则，他们首先（立即）重新装满罐子，然后给植物浇水。
如果Alice和Bob到达同一株植物，那么当前水罐中水更多的人会给这株植物浇水。
如果他俩水量相同，那么Alice会给这株植物浇水。
给你一个下标从0开始的整数数组plants，数组由n个整数组成。
其中，plants[i]为第i株植物需要的水量。
另有两个整数capacityA和capacityB分别表示Alice和Bob水罐的容量。
返回两人浇灌所有植物过程中重新灌满水罐的次数 。

示例1：
输入：plants = [2,2,3,3], capacityA = 5, capacityB = 5
输出：1
解释：最初，Alice和Bob的水罐中各有5单元水。
     Alice给植物0浇水，Bob给植物3浇水。
     Alice和Bob现在分别剩下3单元和2单元水。
     Alice有足够的水给植物1，所以她直接浇水。
     Bob的水不够给植物2，所以他先重新装满水，再浇水。
     所以，两人浇灌所有植物过程中重新灌满水罐的次数= 0 + 0 + 1 + 0 = 1。

示例2：
输入：plants = [2,2,3,3], capacityA = 3, capacityB = 4
输出：2
解释：最初，Alice的水罐中有3单元水，Bob的水罐中有4单元水。
     Alice给植物0浇水，Bob给植物3浇水。
     Alice和Bob现在都只有1单元水，并分别需要给植物1和植物2浇水。
     由于他们的水量均不足以浇水，所以他们重新灌满水罐再进行浇水。
     所以，两人浇灌所有植物过程中重新灌满水罐的次数= 0 + 1 + 1 + 0 = 2。

示例3：
输入：plants = [5], capacityA = 10, capacityB = 8
输出：0
解释：只有一株植物
     Alice的水罐有10单元水，Bob的水罐有8单元水。
     因此Alice的水罐中水更多，她会给这株植物浇水。
     所以，两人浇灌所有植物过程中重新灌满水罐的次数 = 0。


提示：
n == plants.length
1 <= n <= 10^5
1 <= plants[i] <= 10^6
max(plants[i]) <= capacityA, capacityB <= 10^9
*/

class Solution {
 public:
  int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
    int ans = 0;
    int ca = capacityA;
    int cb = capacityB;
    int left = 0;
    int right = plants.size() - 1;
    for (; left < right; ++left, --right) {
      if (ca < plants[left]) {
        ++ans;
        ca = capacityA;
      }
      ca -= plants[left];
      if (cb < plants[right]) {
        ++ans;
        cb = capacityB;
      }
      cb -= plants[right];
    }
    if (left == right && max(ca, cb) < plants[left]) {
      ++ans;
    }
    return ans;
  }
};