/*
将非负整数num转换为其对应的英文表示。

示例1：
输入：num = 123
输出："One Hundred Twenty Three"

示例2：
输入：num = 12345
输出："Twelve Thousand Three Hundred Forty Five"

示例3：
输入：num = 1234567
输出："One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

提示：0 <= num <= 2^31 - 1
*/

char *hundred(int num) {
  const char *int_num[20] = {"Zero",    "One",       "Two",      "Three",
                             "Four",    "Five",      "Six",      "Seven",
                             "Eight",   "Nine",      "Ten",      "Eleven",
                             "Twelve",  "Thirteen",  "Fourteen", "Fifteen",
                             "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
  const char *dividedByTen[10] = {"",       "Ten",   "Twenty", "Thirty",
                                  "Forty",  "Fifty", "Sixty",  "Seventy",
                                  "Eighty", "Ninety"};
  char *arr = (char *)malloc(sizeof(char) * 100);
  memset(arr, '\0', sizeof(arr));
  if (num == 1000) {
    strcat(arr, int_num[1]);
    strcat(arr, " ");
    strcat(arr, "Thousand");
    return arr;
  }
  if (num == 0) {
    // strcat(arr,int_num[0]);
    return arr;
  }
  if (num % 100 == 0) {
    strcat(arr, int_num[num / 100]);
    strcat(arr, " Hundred");
    return arr;
  }
  if (num > 100) {
    strcat(arr, int_num[num / 100]);
    strcat(arr, " Hundred ");
  }
  num = num - (num / 100 * 100);
  if (1 <= num && num <= 19) {
    strcat(arr, int_num[num]);
  } else if (num % 10 == 0) {
    strcat(arr, dividedByTen[num / 10]);
  } else {
    strcat(arr, dividedByTen[num / 10]);
    strcat(arr, " ");
    strcat(arr, int_num[num % 10]);
  }
  return arr;
}
char *numberToWords(int num) {
  const char *value[4] = {"Billion", "Million", "Thousand", "Hundred"};
  const char *int_num[10] = {"Zero", "One", "Two",   "Three", "Four",
                             "Five", "Six", "Seven", "Eight", "Nine"};
  const char *dividedByTen[10] = {"Ten",     "Twenty", "Thirty",
                                  "Forty",   "Fifty",  "Sixty",
                                  "Seventy", "Eighty", "Ninety"};
  char *res = (char *)malloc(sizeof(char) * 1000);
  memset(res, '\0', sizeof(res));
  int str[10] = {0}, bit = 0;
  if (num == 0) {
    strcat(res, int_num[0]);
    return res;
  }
  if (num == 1000000000) {
    strcat(res, int_num[1]);
    strcat(res, " ");
    strcat(res, value[0]);
    return res;
  }
  if (num == 1000000) {
    strcat(res, int_num[1]);
    strcat(res, " ");
    strcat(res, value[1]);
    return res;
  }
  while (num > 0) {
    str[bit++] = num % 10;
    num /= 10;
  }
  num = 0;
  for (int i = 0; i < bit; i++) {
    num += pow(10, i) * str[i];
  }
  int k = 0;
  while (num > 1000000000) {
    num -= 1000000000;
    k++;
  }
  if (num == 1000000000) {
    strcat(res, int_num[1]);
    strcat(res, " ");
    strcat(res, value[0]);
    return res;
  }
  if (k) {
    strcat(res, int_num[k]);
    strcat(res, " ");
    strcat(res, value[0]);
    strcat(res, " ");
    k = 0;
  }
  while (num > 1000000) {
    int remainder = num % 1000000;
    k = (num - remainder) / 1000000;
    num = remainder;
  }
  if (num == 1000000) {
    strcat(res, int_num[1]);
    strcat(res, " ");
    strcat(res, value[1]);
    return res;
  }
  if (k) {
    char *arr = hundred(k);
    strcat(res, arr);
    strcat(res, " ");
    strcat(res, value[1]);
    if (num != 0) strcat(res, " ");
    k = 0;
  }
  while (num > 1000) {
    int remainder = num % 1000;
    k = (num - remainder) / 1000;
    num = remainder;
  }
  if (k) {
    char *arr = hundred(k);
    strcat(res, arr);
    strcat(res, " ");
    strcat(res, value[2]);
    if (num != 0) strcat(res, " ");
    k = 0;
  }
  char *arr = NULL;
  arr = hundred(num);
  strcat(res, arr);
  return res;
}

class Solution {
 public:
  vector<string> singles = {"",     "One", "Two",   "Three", "Four",
                            "Five", "Six", "Seven", "Eight", "Nine"};
  vector<string> teens = {"Ten",      "Eleven",  "Twelve",  "Thirteen",
                          "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                          "Eighteen", "Nineteen"};
  vector<string> tens = {"",      "Ten",   "Twenty",  "Thirty", "Forty",
                         "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
  vector<string> thousands = {"", "Thousand", "Million", "Billion"};

  string numberToWords(int num) {
    if (num == 0) {
      return "Zero";
    }
    string sb;
    for (int i = 3, unit = 1000000000; i >= 0; i--, unit /= 1000) {
      int curNum = num / unit;
      if (curNum != 0) {
        num -= curNum * unit;
        sb = sb + toEnglish(curNum) + thousands[i] + " ";
      }
    }
    while (sb.back() == ' ') {
      sb.pop_back();
    }
    return sb;
  }

  string toEnglish(int num) {
    string curr;
    int hundred = num / 100;
    num %= 100;
    if (hundred != 0) {
      curr = curr + singles[hundred] + " Hundred ";
    }
    int ten = num / 10;
    if (ten >= 2) {
      curr = curr + tens[ten] + " ";
      num %= 10;
    }
    if (num > 0 && num < 10) {
      curr = curr + singles[num] + " ";
    } else if (num >= 10) {
      curr = curr + teens[num - 10] + " ";
    }
    return curr;
  }
};