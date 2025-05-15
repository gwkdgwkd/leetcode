/*
给n个任务和m个工人。
每个任务需要一定的力量值才能完成，需要的力量值保存在下标从0开始的整数数组tasks中，
第i个任务需要tasks[i]的力量才能完成。
每个工人的力量值保存在下标从0开始的整数数组workers中，第j个工人的力量值为workers[j]。
每个工人只能完成一个任务，且力量值需要大于等于该任务的力量要求值，即workers[j]>=tasks[i]。
除此以外，还有pills个神奇药丸，可以给一个工人的力量值增加strength。
可以决定给哪些工人使用药丸，但每个工人最多只能使用一片药丸。
给下标从0开始的整数数组tasks和workers以及两个整数pills和strength，
请你返回最多有多少个任务可以被完成。

示例1：
输入：tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
输出：3
解释：我们可以按照如下方案安排药丸：
     给0号工人药丸。
     0号工人完成任务2（0 + 1 >= 1）
     1号工人完成任务1（3 >= 2）
     2号工人完成任务0（3 >= 3）

示例2：
输入：tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
输出：1
解释：我们可以按照如下方案安排药丸：
     给0号工人药丸。
     0号工人完成任务0（0 + 5 >= 5）

示例3：
输入：tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength = 10
输出：2
解释：我们可以按照如下方案安排药丸：
     给0号和1号工人药丸。
     0号工人完成任务0（0 + 10 >= 10）
     1号工人完成任务1（10 + 10 >= 15）

示例4：
输入：tasks = [5,9,8,5,9], workers = [1,6,4,2,6], pills = 1, strength = 5
输出：3
解释：我们可以按照如下方案安排药丸：
     给2号工人药丸。
     1号工人完成任务0（6 >= 5）
     2号工人完成任务2（4 + 5 >= 8）
     4号工人完成任务3（6 >= 5）


提示：
n == tasks.length
m == workers.length
1 <= n, m <= 5 * 10^4
0 <= pills <= m
0 <= tasks[i], workers[j], strength <= 10^9
*/

/*
提示1：
如果我们已经知道一定可以完成k个任务，那么：
我们可以在tasks中选择k个值最小的任务；
我们可以在workers中选择k个值最大的工人。

提示2：
如果我们可以完成k个任务，并且满足提示1，那么一定可以完成k−1个任务，
并且可以选择k−1个值最小的任务以及k−1个值最大的工人，同样满足提示1。

根据提示2，就可以使用二分查找的方法找到k的上界k′，使得我们可以完成k′个任务，
但不能完成k′+1个任务，我们找到的k′即为答案。
在二分查找的每一步中，当我们得到k个值最小的任务以及k个值最大的工人后，
我们应该如何判断这些任务是否都可以完成呢？

我们可以考虑值最大的那个任务，此时会出现两种情况：
1.如果有工人的值大于等于该任务的值，那么我们一定不需要使用药丸，
  并且一定让值最大的工人完成该任务。
  证明的思路为：由于我们考虑的是值最大的那个任务，
  因此所有能完成该任务的工人都能完成剩余的所有任务。
  因此如果一个值并非最大的工人（无论是否使用药丸）完成该任务，
  而值最大的工人完成了另一个任务，那么我们将这两个工人完成的任务交换，仍然是可行的。
2.如果所有工人的值都小于该任务的值，那么我们必须使用药丸让一名工人完成任务，
  并且一定让值最小的工人完成该任务。
  这里的值最小指的是在使用药丸能完成任务的前提下，值最小的工人。
  证明的思路为：由于我们考虑的是值最大的那个任务，
  因此所有通过使用药丸能完成该任务的工人都能完成剩余的所有任务。
  如果一个值并非最小的工人使用药丸完成该任务，
  而值最小的工人（无论是否使用药丸）完成了另一个任务，
  那么我们将这两个工人完成的任务交换，仍然是可行的。
因此，我们可以从大到小枚举每一个任务，并使用有序集合维护所有的工人。
当枚举到任务的值为t时：
如果有序集合中最大的元素大于等于t，那么我们将最大的元素从有序集合中删除。
如果有序集合中最大的元素小于t，那么在有序集合中找出最小的大于等于t−strength的元素并删除。
对于这种情况，如果我们没有药丸剩余，或者有序集合中不存在大于等于t−strength的元素，
那么我们就无法完成所有任务。
这样一来，我们就解决了二分查找后判断可行性的问题。
*/

// 二分查找 + 贪心选择工人
class Solution {
  // 时间复杂度：O(nlogn+mlogm+min(m,n)log2min(m,n))。
  //           对数组tasks排序需要O(nlogn)的时间；
  //           对数组workers排序需要O(mlogm)的时间；
  //           二分查找的下界为1，上界为m和n中的较小值，因此二分查找的次数为logmin(m,n)。
  //           每一次查找需要枚举min(m,n)个任务，
  //           并且枚举的过程中需要对工人的有序集合进行删除操作，
  //           单次操作时间复杂度为logmin(m,n)。
  //           因此二分查找的总时间复杂度为O(min(m,n)log2min(m,n))。
  // 空间复杂度：O(logn+logm+min(m,n))。
  //           对数组tasks排序需要O(logn)的栈空间；
  //           对数组workers排序需要O(logm)的栈空间；
  //           二分查找中使用的有序集合需要O(min(m,n))的空间。
 public:
  int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills,
                    int strength) {
    int n = tasks.size(), m = workers.size();
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());

    auto check = [&](int mid) -> bool {
      int p = pills;
      // 工人的有序集合
      multiset<int> ws;
      for (int i = m - mid; i < m; ++i) {
        ws.insert(workers[i]);
      }
      // 从大到小枚举每一个任务
      for (int i = mid - 1; i >= 0; --i) {
        // 如果有序集合中最大的元素大于等于 tasks[i]
        if (auto it = prev(ws.end()); *it >= tasks[i]) {
          ws.erase(it);
        } else {
          if (!p) {
            return false;
          }
          auto rep = ws.lower_bound(tasks[i] - strength);
          if (rep == ws.end()) {
            return false;
          }
          --p;
          ws.erase(rep);
        }
      }
      return true;
    };

    int left = 1, right = min(m, n), ans = 0;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (check(mid)) {
        ans = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return ans;
  }
};

// 二分答案+贪心匹配+双端队列
class Solution {
  /*
  可以发现，当我们从大到小枚举每一个任务时，
  如果我们维护了（在使用药丸的情况下）所有可以完成任务的工人，那么：
  如果有工人可以不使用药丸完成该任务，那么我们选择（删除）值最大的工人；
  如果所有工人都需要使用药丸才能完成该任务，那么我们选择（删除）值最小的工人。
  而随着任务值的减少，可以完成任务的工人只增不减，
  因此可以使用一个双端队列来维护所有可以（在使用药丸的情况下）所有可以完成任务的工人，
  此时要么队首的工人被选择（删除），要么队尾的工人被选择（删除），
  那么单次删除操作的时间复杂度由O(logmin(m,n))降低为 O(1)，总时间复杂度降低为：
  O(nlogn+mlogm+min(m,n)logmin(m,n))=O(nlogn+mlogm)
  */
 public:
  int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills,
                    int strength) {
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());
    int n = tasks.size();
    int m = workers.size();

    auto check = [&](int mid) -> bool {
      int p = pills;
      deque<int> ws;
      int ptr = m - 1;
      for (int i = mid - 1; i >= 0; --i) {  // 从大到小枚举每一个任务
        while (ptr >= m - mid && workers[ptr] + strength >= tasks[i]) {
          ws.push_front(workers[ptr]);
          --ptr;
        }
        if (ws.empty()) {
          return false;
        } else if (ws.back() >= tasks[i]) {
          ws.pop_back();  // 如果双端队列中最大的元素大于等于tasks[i]
        } else {
          if (p == 0) {
            return false;
          }
          --p;
          ws.pop_front();
        }
      }
      return true;
    };

    int ans = 0;
    int left = 1;
    int right = min(n, m);
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        ans = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return ans;
  }
};