/*
每年，政府都会公布一万个最常见的婴儿名字和它们出现的频率，
也就是同名婴儿的数量。
有些名字有多种拼法，例如，John和Jon本质上是相同的名字，
但被当成了两个名字公布出来。
给定两个列表，一个是名字及对应的频率，另一个是本质相同的名字对。
设计一个算法打印出每个真实名字的实际频率。
注意，如果John和Jon是相同的，并且Jon和Johnny相同，
则John与Johnny也相同，即它们有传递和对称性。
在结果列表中，选择字典序最小的名字作为真实名字。

示例：
输入：names = ["John(15)","Jon(12)","Chris(13)",
              "Kris(4)","Christopher(19)"],
synonyms = ["(Jon,John)","(John,Johnny)",
            "(Chris,Kris)","(Chris,Christopher)"]
输出：["John(27)","Chris(36)"]

提示：names.length <= 100000
*/

typedef struct {
  int root_index;
  char name[20];
  int frequency;
} name_fre;
int Cmp_names(const void* a, const void* b) {
  name_fre* c = (name_fre*)a;
  name_fre* d = (name_fre*)b;
  return strcmp(c->name, d->name);
}
int FindRoot(name_fre* NAMES, int index) {
  int son = index;
  int temp;
  int index_temp = index;

  if (NAMES[index_temp].root_index == index_temp) {  // 根是自身
    return index_temp;
  }

  while (NAMES[index_temp].root_index != index_temp) {  // 找到root
    index_temp = NAMES[index_temp].root_index;
  }

  while (son !=
         index_temp) {  // 路径压缩，每个节点都连接到根节点上，节省查找时间
    temp = NAMES[son].root_index;  // 当前名字的根节点
    NAMES[son].root_index = index_temp;
    son = temp;
  }

  return index_temp;
}
void UnionRoot(name_fre* NAMES, int index1, int index2) {
  int a = FindRoot(NAMES, index1);
  int b = FindRoot(NAMES, index2);

  if (a != b) {
    if (strcmp(NAMES[a].name, NAMES[b].name) <
        0) {  // 选择字典序最小的字符串作为根节点
      NAMES[b].root_index = a;
      NAMES[a].frequency += NAMES[b].frequency;
      NAMES[b].frequency = 0;
    } else {
      NAMES[a].root_index = b;
      NAMES[b].frequency += NAMES[a].frequency;
      NAMES[a].frequency = 0;
    }
  }
}
int FindName(name_fre* NAMES, int name_number, char* name) {
  int low = 0;
  int high = name_number - 1;
  while (low < high) {
    int mid = (low + high) / 2;
    if (strcmp(NAMES[mid].name, name) < 0) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}
void UnionName(name_fre* NAMES, int name_number, char* name1, char* name2) {
  int name1_index = FindName(NAMES, name_number, name1);
  int name2_index = FindName(NAMES, name_number, name2);

  if (name1_index == name2_index) {
    return;
  }
  // union根节点
  UnionRoot(NAMES, name1_index, name2_index);
}
char** trulyMostPopular(char** names, int namesSize, char** synonyms,
                        int synonymsSize, int* returnSize) {
  name_fre NAMES[namesSize];
  int ret_index = 0;
  char** ret = (char**)malloc(namesSize * sizeof(char*));

  for (int i = 0; i < namesSize; i++) {
    memset(NAMES[i].name, '\0', 20);
    NAMES[i].frequency = 0;
    NAMES[i].root_index = -1;
  }
  // 将名字和频率写成结构体
  for (int i = 0; i < namesSize; i++) {
    int s_len = strlen(names[i]);
    for (int j = 0; j < s_len; j++) {
      if ((names[i][j] >= 'a' && names[i][j] <= 'z') ||
          (names[i][j] >= 'A' && names[i][j] <= 'Z')) {
        NAMES[i].name[j] = names[i][j];
      } else if (names[i][j] >= '0' && names[i][j] <= '9') {
        NAMES[i].frequency = 10 * NAMES[i].frequency + (names[i][j] - '0');
      }
    }
  }

  qsort(NAMES, namesSize, sizeof(name_fre), Cmp_names);

  for (int i = 0; i < namesSize; i++) {
    NAMES[i].root_index = i;  // 初始化时根节点是自己
  }

  // 读取名字对
  for (int i = 0; i < synonymsSize; i++) {
    char name1[20], name2[20];
    memset(name1, '\0', 20);
    memset(name2, '\0', 20);
    int s_len = strlen(synonyms[i]);
    int flag = 0, index1 = 0, index2 = 0;
    for (int j = 0; j < s_len; j++) {
      if ((synonyms[i][j] >= 'a' && synonyms[i][j] <= 'z') ||
          (synonyms[i][j] >= 'A' && synonyms[i][j] <= 'Z')) {
        if (!flag) {
          name1[index1++] = synonyms[i][j];
        } else {
          name2[index2++] = synonyms[i][j];
        }
      }
      if (synonyms[i][j] == ',') {
        flag = 1;
      }
    }
    // 查找名字的根节点
    UnionName(NAMES, namesSize, name1, name2);
  }

  // 将频率不为0的名字输出
  for (int i = 0; i < namesSize; i++) {
    if (NAMES[i].frequency == 0) {
      continue;
    }
    ret[ret_index] = (char*)malloc(30 * sizeof(char));
    int s_len = strlen(NAMES[i].name);
    int fre = NAMES[i].frequency;
    char fre_str[10] = {'\0'};
    memcpy(ret[ret_index], NAMES[i].name, s_len);
    ret[ret_index][s_len] = '(';
    sprintf(fre_str, "%d", fre);  // 将整数转为字符串
    int fre_len = strlen(fre_str);
    memcpy(&ret[ret_index][s_len + 1], fre_str, fre_len);
    ret[ret_index][s_len + fre_len + 1] = ')';
    ret[ret_index][s_len + fre_len + 2] = '\0';
    ret_index++;
  }
  *returnSize = ret_index;
  return ret;
}

class UnionSet {
 private:
  unordered_map<string, string> parents;
  unordered_map<string, int> sizes;

 public:
  void Put(string&& str, int size) {
    parents[str] = str;
    sizes[str] = size;
  }

  void Put(string& str, int size) {
    parents[str] = str;
    sizes[str] = size;
  }

  void Merge(string str1, string str2) {
    str1 = Find(str1);
    str2 = Find(str2);
    if (str1 < str2) {
      parents[str2] = str1;
      sizes[str1] = sizes[str2] + sizes[str1];
    } else if (str2 < str1) {
      parents[str1] = str2;
      sizes[str2] = sizes[str2] + sizes[str1];
    }
  }

  string Find(string& a) {
    if (parents[a] == a) {
      return a;
    }
    return Find(parents[a]);
  }

  int Size(string& str) { return sizes[str]; }

  bool IsExist(string& str) { return parents.find(str) != parents.end(); }
};

class Solution {
 public:
  vector<string> trulyMostPopular(vector<string>& names,
                                  vector<string>& synonyms) {
    UnionSet us;
    // 存储目前的名字
    vector<string> allNames;
    // 首次遍历names把数量插入到UnionSet里
    for (string& name : names) {
      auto start = name.find("(");
      auto end = name.find(")");
      us.Put(name.substr(0, start),
             stoi(name.substr(start + 1, end - start - 1)));
      allNames.push_back(name.substr(0, start));
    }

    // 遍历synnoyms来生成并查集
    for (string synonym : synonyms) {
      // 考虑在names里不存在name，也插入默认的size=0
      auto index1 = synonym.find(",");
      string name1 = synonym.substr(1, index1 - 1);
      string name2 = synonym.substr(index1 + 1, synonym.find(")") - index1 - 1);
      if (!us.IsExist(name1)) {
        us.Put(name1, 0);
      }
      if (!us.IsExist(name2)) {
        us.Put(name2, 0);
      }
      us.Merge(name1, name2);
    }

    // 再次遍历只找自己的父节点是自己的name（即就是输出真实的字典序最小）
    vector<string> res;
    for (string& name : allNames) {
      // 只输出根节点是自己的
      if (us.Find(name) == name) {
        res.push_back(name + "(" + to_string(us.Size(name)) + ")");
      }
    }
    return res;
  }
};
