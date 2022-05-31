char ** findRepeatedDnaSequences(char * s, int* returnSize){ 
    unsigned int map[1024 * 1024] = {0}; 
    char **ret = (char **)malloc(sizeof(char *) * 1000); 
    char buf[256] = {0}; 
    int len = strlen(s); 
    int i, n = 0; 
    unsigned int val = 0;

    buf['A'] = 0;
    buf['C'] = 1;
    buf['G'] = 2;
    buf['T'] = 3;

    for (i = 0; i < 10 && i < len; i++) {
        val = (val << 2) | buf[s[i]];
    }
    map[val] = 1;

    for (i = 10; i < len; i++) {
        val = ((val << 2) & 0xfffff) | buf[s[i]];
        map[val]++;

        if (map[val] == 2) {
            char *s1 = malloc(12);
            memset(s1, 0, 12);
            memcpy(s1, s + i - 9, 10);
            ret[n] = s1;
            n++;
        }
    }

    *returnSize = n;
    return ret;
}

// /**
//  * Note: The returned array must be malloced, assume caller calls free().
//  */
// size_t get_hash(char *str)
// {//ensure strlen(str)>=10
//     register size_t hash=0;
//     for(int i=0;i<10;i++)
//     {
//         hash=hash*131+str[i];
//     }
//     return hash;
// }
// struct Hash{
//     size_t val;//保存hash,相同的hash视为同一字符串
//     bool save;//是否已经保存，用于去重
//     struct Hash *next_hash;//链表处理hash冲突
// };

// char ** findRepeatedDnaSequences(char * s, int* returnSize){
//     int hash_size=strlen(s)-9;
//     char **ret=NULL;
//     *returnSize=0;
//     if(hash_size<2)return ret;
//     struct Hash **hash_map=calloc(hash_size,sizeof(struct Hash *));
//     for(int i=0;i<hash_size;i++)
//     {
//         size_t hash_key=get_hash(s+i);
//         struct Hash *hash_node=hash_map[hash_key%hash_size];
//         struct Hash * new_node=NULL;
//         if(!hash_node)
//         {
//             new_node=(struct Hash *)malloc(sizeof(struct Hash));
//             new_node->next_hash=NULL;
//             new_node->val=hash_key;
//             new_node->save=false;
//             hash_map[hash_key%hash_size]=new_node;
//         }
//         else
//         {
//             while(hash_node)
//             {
//                 if(hash_node->val==hash_key)
//                 {
//                     if(!hash_node->save)
//                     {
//                         hash_node->save=true;
//                         (*returnSize)++;
//                         ret=(char **)realloc(ret,sizeof(char *)*(*returnSize));
//                         ret[(*returnSize)-1]=(char *)calloc(11,sizeof(char));
//                         strncpy(ret[(*returnSize)-1],s+i,sizeof(char)*10);
//                         printf("%s\n",ret[(*returnSize)-1]);
//                     }
//                     break;
//                 }
//                 else
//                 {
//                     if(!hash_node->next_hash)
//                     {
//                         new_node=(struct Hash *)malloc(sizeof(struct Hash));
//                         new_node->next_hash=NULL;
//                         new_node->val=hash_key;
//                         new_node->save=false;
//                         hash_node->next_hash=new_node;
//                         break;
//                     }
//                     hash_node=hash_node->next_hash;
//                 }
//             }
//         }
//     }
//     for(int i=0;i<hash_size;i++)
//     {
//         struct Hash *hash=hash_map[i];
//         while(hash)
//         {
//             struct Hash *tmp=hash;
//             hash=hash->next_hash;
//             free(tmp);
//         }
//     }
//     free(hash_map);
//     return ret;
// }

