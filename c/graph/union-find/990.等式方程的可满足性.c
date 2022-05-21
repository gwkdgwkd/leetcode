/*
给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程equations[i]的长度为4，
并采用两种不同的形式之一："a==b"或"a!=b"。在这里，a和b是小写字母（不一定不同），表示单字母变量名。
只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回true，否则返回false。

示例1：
输入：["a==b","b!=a"]
输出：false
解释：如果我们指定，a = 1且b = 1，那么可以满足第一个方程，但无法满足第二个方程。
没有办法分配变量同时满足这两个方程。

示例2：
输入：["b==a","a==b"]
输出：true
解释：我们可以指定a = 1且b = 1以满足满足这两个方程。

示例3：
输入：["a==b","b==c","a==c"]
输出：true

示例4：
输入：["a==b","b!=c","c==a"]
输出：false

示例5：
输入：["c==c","b==d","x!=z"]
输出：true

提示：
1 <= equations.length <= 500
equations[i].length == 4
equations[i][0]和equations[i][3]是小写字母
equations[i][1]要么是'='，要么是'!'
equations[i][2]是'='
*/

// Union-Find算法
// Union-Find算法，也就是常说的并查集算法，主要是解决图论中动态连通性问题的。
// 很多使用DFS深度优先算法解决的问题，也可以用Union-Find算法解决。
// 这里所说的连通是一种等价关系，也就是说具有如下三个性质：
// 1.自反性：节点p和p是连通的。
// 2.对称性：如果节点p和q连通，那么q和p也连通。
// 3.传递性：如果节点p和q连通，q和r连通，那么p和r也连通。
// Union-Find算法的关键就在于Union和Connected函数的效率。
// 使用数组来模拟出一个森林，如此巧妙的解决这个比较复杂的问题！
// 构造函数初始化数据结构需要O(N)的时间和空间复杂度；
// 连通两个节点Union、判断两个节点的连通性Connected、计算连通分量Count所需的时间复杂度均为O(1)。
int count;    // 连通分量个数
int* parent;  // 存储一棵树
int* size;    // 记录树的重量
void UF(int n) {
  // 怎么用森林来表示连通性呢？
  // 设定树的每个节点有一个指针指向其父节点，如果是根节点的话，这个指针指向自己。
  count = n;
  parent = (int*)malloc(sizeof(int) * n);
  size = (int*)malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    size[i] = 1;
  }
}
int Find(int x) {
  // 主要API
  // Connected和Union中的复杂度都是Find函数造成的，所以说它们的复杂度和Find一样。
  // 能不能进一步压缩每棵树的高度，使树高始终保持为常数？
  // 这样Find就能以O(1)的时间找到某一节点的根节点，相应的，Connected和Union复杂度都下降为O(1)。
  // 调用Find函数每次向树根遍历的同时，顺手将树高缩短了，最终所有树高都不会超过3（Union的时候树高可能达到3）
  while (parent[x] != x) {
    // 进行路径压缩
    parent[x] = parent[parent[x]];
    x = parent[x];
  }
  return x;
}
void Union(int p, int q) {
  // 如果某两个节点被连通，则让其中的（任意）一个节点的根节点接到另一个节点的根节点上：
  int rootP = Find(p);
  int rootQ = Find(q);
  if (rootP == rootQ) return;

  // 小一些的树接到大一些的树下面，这样就能避免头重脚轻，更平衡一些。
  // 解决方法是额外使用一个size数组，记录每棵树包含的节点数，称为重量。
  // 通过比较树的重量，就可以保证树的生长相对平衡，树的高度大致在logN这个数量级，极大提升执行效率。
  // 此时，Find,Union,Connected的时间复杂度都下降为O(logN)，即便数据规模上亿，所需时间也非常少。
  if (size[rootP] > size[rootQ]) {
    parent[rootQ] = rootP;
    size[rootP] += size[rootQ];
  } else {
    parent[rootP] = rootQ;
    size[rootQ] += size[rootP];
  }
  count--;
}
bool Connected(int p, int q) {
  // 如果节点p和q连通的话，它们一定拥有相同的根节点：
  int rootP = Find(p);
  int rootQ = Find(q);
  return rootP == rootQ;
}

// 动态连通性其实就是一种等价关系，具有自反性、传递性和对称性，
// 其实==关系也是一种等价关系，具有这些性质。
// 所以这个问题用Union-Find算法就很自然。
// 将equations中的算式根据==和!=分成两部分，先处理==算式，使得他们通过相等关系各自勾结成门派；
// 然后处理!=算式，检查不等关系是否破坏了相等关系的连通性。
bool equationsPossible(char** equations, int equationsSize) {
  UF(26);  // 26个英文字母
  // 先让相等的字母形成连通分量
  for (int i = 0; i < equationsSize; ++i) {
    if (equations[i][1] == '=') {
      char x = equations[i][0];
      char y = equations[i][3];
      Union(x - 'a', y - 'a');
    }
  }
  // 检查不等关系是否打破相等关系的连通性
  for (int i = 0; i < equationsSize; ++i) {
    if (equations[i][1] == '!') {
      char x = equations[i][0];
      char y = equations[i][3];
      // 如果相等关系成立，就是逻辑冲突
      if (Connected(x - 'a', y - 'a')) return false;
    }
  }
  return true;
}
