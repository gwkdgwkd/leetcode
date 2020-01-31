#define MAX_ALPHA_NUM 26

int str2int(char *str){
	int res = 0;
	int size = strlen(str);
	for (int i = 0; i < size; i++){
		res |= 1 << (str[i] - 'a');
	}
	return res;
}

int maxProduct(char ** words, int wordsSize){
	if (words == NULL || wordsSize < 1)
	{
		return 0;
	}
	int *ptr = (int*)malloc(sizeof(int)*wordsSize);
	for (int i = 0; i < wordsSize; i++){
		ptr[i] = str2int(words[i]);
	}
	int res = 0;
	for (int i = 0; i < wordsSize; i++){
		for (int j = 0; j < i; j++){
			if ((ptr[i] & ptr[j]) == 0 && (strlen(words[i])*strlen(words[j])) > res){
				res = strlen(words[i])*strlen(words[j]);
			}
		}
	}
	return res;
}
