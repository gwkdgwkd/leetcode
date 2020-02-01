#define RETURN_IF(expr, errCode) \
    {                            \
        if (expr) {              \
            return (errCode);    \
        }                        \
    }
#define CONTINUE_IF(expr)          \
    {                              \
        if (expr) {                \
            continue;              \
        }                          \
    }

#define MAXLEN 200
#define MAXBOTTOM 8
typedef struct {
    char numStore[MAXLEN];
    int num;
} NodeInfo;
NodeInfo nodeInfo[MAXBOTTOM][MAXBOTTOM] = {0};
bool BuildStr(char* bottom, int bottomLen, char* nextBottom, int begin)
{
    int index, indexj;
    bool res;
    char nestr[MAXBOTTOM] = {0};
    // printf("bottomLen = %d, begin = %d\n", bottomLen, begin);
    RETURN_IF(bottomLen == 1, true);
    if (begin == bottomLen - 1) {
        return BuildStr(nextBottom, bottomLen - 1, nestr, 0);
    }
    // printf("%c, %c, %d\n", bottom[begin], bottom[begin + 1], nodeInfo[0][0].num);
    RETURN_IF(nodeInfo[bottom[begin] - 'A'][bottom[begin + 1] - 'A'].num == 0, false);
    // printf("num = %d\n", nodeInfo[bottom[begin] - 'A'][bottom[begin + 1] - 'A'].num);
    for (index = 0; index < nodeInfo[bottom[begin] - 'A'][bottom[begin + 1] - 'A'].num; index++) {
        nextBottom[begin] = nodeInfo[bottom[begin] - 'A'][bottom[begin + 1] - 'A'].numStore[index];
        res = BuildStr(bottom, bottomLen, nextBottom, begin + 1);
        RETURN_IF(res == true, true);
    }
    return false;
}

bool pyramidTransition(char * bottom, char ** allowed, int allowedSize)
{
    int index = 0;
    int bottomLen = 0;
    int num, indexj;
    char nextBottom[MAXBOTTOM] = {0};
    RETURN_IF(bottom == NULL, true);
    RETURN_IF(allowed == NULL || allowedSize == 0, false);
    while (bottom[index] != '\0') {
        bottomLen++;
        index++;
    }
    RETURN_IF(bottomLen == 1, true);
    for (index = 0; index < MAXBOTTOM; index++) {
        for (indexj = 0; indexj < MAXBOTTOM; indexj++) {
            nodeInfo[index][indexj].num = 0;
        }
    }
    for (index = 0; index < allowedSize; index++) {
        num = nodeInfo[allowed[index][0] - 'A'][allowed[index][1] - 'A'].num;
        nodeInfo[allowed[index][0] - 'A'][allowed[index][1] - 'A'].numStore[num] = allowed[index][2];
        (nodeInfo[allowed[index][0] - 'A'][allowed[index][1] - 'A'].num)++;
        // printf("num = %d\n", nodeInfo[allowed[index][0] - 'A'][allowed[index][1] - 'A'].num);
    }
    return BuildStr(bottom, bottomLen,  nextBottom, 0);
}

