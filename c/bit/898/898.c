// int subarrayBitwiseORs(int* A, int ASize){
//     int len = ASize*(1+ASize)/2;
//     int temp[len];
//     int count = 0;
//     int dp[ASize][ASize];
//     for(int i=0;i<ASize;i++){
//         dp[0][i]=A[i];
//         for(int k = 0; k < len; ++k) {
//             if(k==count){
//                 temp[count++] = dp[0][i];
//                 break;
//             }
//             if(temp[k] == dp[0][i]){
//                 break;
//             }
//         }
//     }
//     for(int i=1;i<ASize;i++){
//         for(int j=0;j<ASize-i;j++){
//             dp[i][j]=dp[i-1][j]|dp[i-1][j+1];
//             for(int k = 0; k < len; ++k) {
//                 if(k==count){
//                     temp[count++] = dp[i][j];
//                     break;
//                 }
//                 if(temp[k] == dp[i][j]){
//                     break;
//                 }
//             }
//         }
//     }
//     return count;
// }


#define MAXSIZE 399999

int ret=0;
void hash(int* starts,int data)
{
    int start=data%MAXSIZE;
    for(int i=start; i<MAXSIZE; i++)
    {
        if( *(starts+i)==data)
        {

            break;
        }
        if( *(starts+i)==-1)
        {
            *(starts+i)=data;
            ret++;
            break;
        }
        if(i==MAXSIZE-1)
        {
            i=-1;
        }
    }

}

int subarrayBitwiseORs(int* A, int ASize)
{
    ret=0;
    int *data=malloc(sizeof(int)*MAXSIZE);
    memset(data,255,sizeof(int)*MAXSIZE);
    int *dp=malloc(sizeof(int)*ASize);
    int max=0;
    for(int i=0; i<ASize; i++)
    {
        dp[i]=A[i];
        hash(data,A[i]);
        max=max<A[i]?A[i]:max;
    }
    int mask = 1;
    while (max >= mask)
    {
        mask <<= 1;
    }
    mask -= 1;
    int rest=ASize;
    while(rest>0)
    {
        int currentrest=rest-1;
        rest=0;
        for(int i=1; i<=currentrest; i++)
        {
            if(dp[i-1]==mask)
            {
                dp[rest++]=mask;
                if(dp[i]==mask)
                {
                    i++;
                }
                continue;
            }
            if(dp[i]==mask)
            {
                dp[i-1]=mask;
                continue;
            }
            dp[rest++]=dp[i]|dp[i-1];
            hash(data,dp[rest-1]);
        }
    }
    return ret;
}
