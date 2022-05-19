/*
给你一个包含n个整数的数组nums，判断nums中是否存在三个元素a，b，c，使得a+b+c=0？
请你找出所有和为0且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例1：
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]

示例2：
输入：nums = []
输出：[]

示例3：
输入：nums = [0]
输出：[]

提示：
0 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
*/

// 剑指OfferII007数组中和为0的三个数

// 排序+双指针（左右包夹）
int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }
int** threeSum(int* nums, int numsSize, int* returnSize,
               int** returnColumnSizes) {
  int n = numsSize;
  // 用qsort函数给nums排序
  qsort(nums, n, sizeof(int), cmp);

  // 声明答案数组指针ans，给ans和**returnColumnSizes申请空间
  int** ans;
  int rstSize = 0, basicSize = 8;  // 用来扩容（如果需要的话）的两个参数
  ans = (int**)malloc(sizeof(int*) * basicSize);
  *returnColumnSizes = (int**)malloc(sizeof(int*) * basicSize);

  for (int target = 0; target < n - 1; target++) {
    // 发现同值，直接右挪，移动到相同值的最后一个
    if (target > 0 && nums[target] == nums[target - 1]) continue;
    // 在排除target后的数组上进行左右包夹扫描
    int left = target + 1, right = n - 1;

    // 保证是左右指针往中间走，不然会乱套，上面的qsort也没意义
    while (left < right) {
      // sum要在开始左右扫描才开始算
      int sum = nums[target] + nums[left] + nums[right];
      // 目标：三数之和=0
      if (sum == 0) {
        // 给单组答案空间申请空间，三数，就是3
        ans[rstSize] = (int*)malloc(sizeof(int) * 3);
        // 给单组答案显示空间申请空间，三数，就是3
        (*returnColumnSizes)[rstSize] = 3;
        ans[rstSize][0] = nums[target];
        ans[rstSize][1] = nums[left];
        ans[rstSize][2] = nums[right];
        rstSize++;  // 答案的组数，开始计数
        while (left < right && nums[left] == nums[left + 1])
          left++;  // 发现同值，直接右移
        // 在target的情况下，继续找还有没有新的left和right，两边同时移动
        left++, right--;
        if (rstSize == basicSize) {  // 答案空间满了，开始扩容
          basicSize *= 2;            // 以原先的两倍大小扩容
          // 答案数组ans扩容
          ans = (int**)realloc(ans, sizeof(int*) * basicSize);
          // 答案显示*returnColumnSizes扩容
          (*returnColumnSizes) =
              (int**)realloc((*returnColumnSizes), sizeof(int*) * basicSize);
        }
      } else if (sum > 0) {
        right--;  // sum>0，单左移right
      } else {
        left++;  // sum<0，单右移left
      }
    }
  }
  // 答案显示大小已经在上面算好了，现在再把算好的rstSize赋值给*returnSize，答案就是正常显示了
  *returnSize = rstSize;
  return ans;  // 得出答案ans
}

int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }
int** threeSum(int* nums, int numsSize, int* returnSize,
               int** returnColumnSizes) {
  *returnSize = 0;
  if (numsSize < 3) {
    return NULL;
  }

  int k, i, j;
  int** ans = (int**)malloc(sizeof(int*) * numsSize * numsSize);
  *returnColumnSizes = (int*)malloc(sizeof(int) * numsSize * numsSize);

  qsort(nums, numsSize, sizeof(int), cmp);

  for (k = 0; k < numsSize - 2; k++) {
    if (nums[k] > 0) return ans;
    if (k > 0 && nums[k] == nums[k - 1]) continue;
    i = k + 1;
    j = numsSize - 1;

    while (i < j) {
      int sum = nums[i] + nums[j] + nums[k];
      if (sum == 0) {
        ans[*returnSize] = (int*)malloc(sizeof(int) * 3);
        (*returnColumnSizes)[*returnSize] = 3;
        ans[*returnSize][0] = nums[k];
        ans[*returnSize][1] = nums[i];
        ans[*returnSize][2] = nums[j];
        *returnSize += 1;
        while (i < j && nums[i] == nums[++i])
          ;
        while (i < j && nums[j] == nums[--j])
          ;
      } else if (sum > 0) {
        j--;
      } else {
        i++;
      }
    }
  }
  return ans;
}