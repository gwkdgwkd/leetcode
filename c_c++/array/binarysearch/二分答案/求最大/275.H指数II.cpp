/*
给一个整数数组citations，其中citations[i]表示研究者的第i篇论文被引用的次数，
citations已经按照非降序排列。计算并返回该研究者的h指数。
h指数的定义：h代表高引用次数（high citations），
一名科研人员的h指数是指他（她）的（n篇论文中）至少有h篇论文分别被引用了至少h次。
请设计并实现对数时间复杂度的算法解决此问题。

示例1：
输入：citations = [0,1,3,5,6]
输出：3
解释：给定数组表示研究者总共有5篇论文，每篇论文相应的被引用了0,1,3,5,6次。
     由于研究者有3篇论文每篇至少被引用了3次，其余两篇论文每篇被引用不多于3次，
     所以她的h指数是3。

示例2：
输入：citations = [1,2,100]
输出：2


提示：
n == citations.length
1 <= n <= 10^5
0 <= citations[i] <= 1000
citations按升序排列
*/

/*
求最小和二分查找求排序数组中某元素的第一个位置是类似的，
按照红蓝染色法，左边是不满足要求的（红色），右边则是满足要求的（蓝色）。
求最大的题目则相反，左边是满足要求的（蓝色），右边是不满足要求的（红色）。
这会导致二分写法和上面的求最小有一些区别。

以开区间二分为例：
求最小：check(mid)==true时更新right=mid，反之更新left=mid，最后返回right。
求最大：check(mid)==true时更新left=mid，反之更新right=mid，最后返回left。
对于开区间写法，简单来说check(mid)==true时更新的是谁，最后就返回谁。
相比其他二分写法，开区间写法不需要思考加一减一等细节，个人推荐使用开区间写二分。
*/

// 闭区间写法
class Solution {
  // 单调性：二分答案的前提：
  // 如果至少有2篇的引用次数>=2，那么也必然有至少1篇引用次数>=1；
  // 如果没有4篇的引用次数>=4，那么也必然没有5篇的引用次数>=5。
 public:
  int hIndex(vector<int>& citations) {
    // 在区间[left, right]内询问
    int n = citations.size();
    int left = 1;
    int right = n;
    while (left <= right) {  // 区间不为空
      // 循环不变量：
      // left-1的回答一定为是
      // right+1的回答一定为否
      int mid = (left + right) / 2;  // left+(right-left)/2
      // 引用次数最多的mid篇论文，引用次数均>=mid
      if (citations[n - mid] >= mid) {
        left = mid + 1;  // 询问范围缩小到[mid+1, right]
      } else {
        right = mid - 1;  // 询问范围缩小到[left, mid-1]
      }
    }

    // 循环结束后right等于left-1，回答一定为是
    // 根据循环不变量，right现在是最大的回答为是的数
    return right;
  }
};

// 左闭右开区间写法
class Solution {
 public:
  int hIndex(vector<int>& citations) {
    // 在区间[left, right)内询问
    int n = citations.size();
    int left = 1;
    int right = n + 1;
    while (left < right) {  // 区间不为空
      // 循环不变量：
      // left-1的回答一定为是
      // right的回答一定为否
      int mid = (left + right) / 2;
      // 引用次数最多的mid篇论文，引用次数均>=mid
      if (citations[n - mid] >= mid) {
        left = mid + 1;  // 询问范围缩小到[mid+1, right)
      } else {
        right = mid;  // 询问范围缩小到[left, mid)
      }
    }
    // 根据循环不变量，left-1现在是最大的回答为是的数
    return left - 1;
  }
};

// 左开右闭区间写法
class Solution {
 public:
  int hIndex(vector<int>& citations) {
    // 在区间(left, right]内询问
    int n = citations.size();
    int left = 0;
    int right = n;
    while (left < right) {  // 区间不为空
      // 循环不变量：
      // left的回答一定为是
      // right+1的回答一定为否
      int mid = (left + right + 1) / 2;  // 保证mid在二分区间内
      // 引用次数最多的mid篇论文，引用次数均>=mid
      if (citations[n - mid] >= mid) {
        left = mid;  // 询问范围缩小到(mid, right]
      } else {
        right = mid - 1;  // 询问范围缩小到(left, mid-1]
      }
    }
    // 根据循环不变量，left现在是最大的回答为是的数
    return left;
  }
};

// 开区间写法
class Solution {
 public:
  int hIndex(vector<int>& citations) {
    // 在区间(left, right)内询问
    int n = citations.size();
    int left = 0;
    int right = n + 1;
    while (left + 1 < right) {  // 区间不为空
      // 循环不变量：
      // left的回答一定为是
      // right的回答一定为否
      int mid = (left + right) / 2;
      // 引用次数最多的mid篇论文，引用次数均>=mid
      if (citations[n - mid] >= mid) {
        left = mid;  // 询问范围缩小到(mid, right)
      } else {
        right = mid;  // 询问范围缩小到(left, mid)
      }
    }
    // 根据循环不变量，left现在是最大的回答为是的数
    return left;
  }
};

class Solution {
 public:
  int hIndex(vector<int>& citations) {
    auto check = [&citations](int h) {
      int sum = 0;
      for (int c : citations) {
        if (c >= h) {
          ++sum;
        }
      }
      return sum >= h;
    };

    int left = 1;
    int right = citations.size();
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};

class Solution {
 public
  int hIndex(int[] citations) {
    int n = citations.length;
    int left = 0, right = n - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (citations[mid] >= n - mid) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return n - left;
  }
}
