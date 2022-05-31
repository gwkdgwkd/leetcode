#define  Max(x,y)    ((x) > (y) ? (x) : (y))

int maxAbsValExpr(int* arr1, int arr1Size, int* arr2, int arr2Size){
    // 八种情况，用1表示正号，-1表示负号
    int d[8][3] = {{1, 1, 1}, {1, 1, -1}, {1, -1, 1}, {-1, 1, 1}, {1, -1, -1}, {-1, -1, 1}, {-1, 1, -1}, {-1, -1, -1}};
    int maxv[8];

    //int n = arr1.size();
    memset(maxv, 0x80, sizeof maxv);

    // 求出点i的8种组合的最大值
    for (int k = 0; k < 8; k ++)
        for (int i = 0; i < arr1Size; i ++)
            maxv[k] = Max(maxv[k], i * d[k][0] + arr1[i] * d[k][1] + arr2[i] * d[k][2]);

    int res = 0;
    for (int k = 0; k < 8; k ++)
        for (int j = 0; j < arr2Size; j ++)
            res = Max(res, maxv[k] - j * d[k][0] - arr1[j] * d[k][1] - arr2[j] * d[k][2]);

    return res;
}
