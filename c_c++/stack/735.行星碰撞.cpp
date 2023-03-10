/*
给定一个整数数组asteroids，表示在同一行的行星，对于数组中的每一个元素，
其绝对值表示行星的大小，正负表示行星的移动方向（正表示向右移动，负表示向左移动）。
每一颗行星以相同的速度移动，找出碰撞后剩下的所有行星。
碰撞规则：两个行星相互碰撞，较小的行星会爆炸，如果两颗行星大小相同，
则两颗行星都会爆炸，两颗移动方向相同的行星，永远不会发生碰撞。

示例1：
输入：asteroids = [5,10,-5]
输出：[5,10]
解释：10和-5碰撞后只剩下10，5和10永远不会发生碰撞。

示例2：
输入：asteroids = [8,-8]
输出：[]
解释：8和-8碰撞后，两者都发生爆炸。

示例3：
输入：asteroids = [10,2,-5]
输出：[10]
解释：2和-5发生碰撞后剩下-5，10和-5发生碰撞后剩下10。

提示：
2 <= asteroids.length <= 10^4
-1000 <= asteroids[i] <= 1000
asteroids[i] != 0
*/

// 剑指OfferII037小行星碰撞

int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize) {
  int stack[asteroidsSize];
  int top = 0;

  for (int i = 0; i < asteroidsSize; ++i) {
    stack[top++] = asteroids[i];

    while (top >= 2 && stack[top - 2] > 0 && stack[top - 1] < 0) {
      int tmp = stack[top - 1] + stack[top - 2];
      if (tmp == 0) {
        top -= 2;
      } else if (tmp > 0) {
        --top;
      } else {
        stack[top - 2] = stack[top - 1];
        --top;
      }
    }
  }

  int* res = (int*)malloc(sizeof(int) * top);
  for (int i = 0; i < top; ++i) {
    res[i] = stack[i];
  }
  *returnSize = top;

  return res;
}

class Solution {
 public:
  vector<int> asteroidCollision(vector<int>& asteroids) {
    vector<int> st;
    for (auto aster : asteroids) {
      bool alive = true;
      while (alive && aster < 0 && !st.empty() && st.back() > 0) {
        alive = st.back() < -aster;  // aster是否存在
        if (st.back() <= -aster) {   // 栈顶行星爆炸
          st.pop_back();
        }
      }
      if (alive) {
        st.push_back(aster);
      }
    }
    return st;
  }
};
