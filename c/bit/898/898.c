int subarrayBitwiseORs(int* A, int ASize){
    int len = ASize*(1+ASize)/2;
    int temp[len];
    int count = 0;
    int dp[ASize][ASize];
    for(int i=0;i<ASize;i++){
        dp[0][i]=A[i];
        for(int k = 0; k < len; ++k) {
            if(k==count){
                temp[count++] = dp[0][i];
                break;
            }
            if(temp[k] == dp[0][i]){
                break;
            }
        }
    }
    for(int i=1;i<ASize;i++){
        for(int j=0;j<ASize-i;j++){
            dp[i][j]=dp[i-1][j]|dp[i-1][j+1];
            for(int k = 0; k < len; ++k) {
                if(k==count){
                    temp[count++] = dp[i][j];
                    break;
                }
                if(temp[k] == dp[i][j]){
                    break;
                }
            }
        }
    }
    return count;
}
