bool validUtf8(int* data, int dataSize){
    int flag = 0;

    for(int i = 0; i < dataSize; ++i) {
        if(0 == flag) {
            if((data[i] & 0xf8) == 0xf0) {
                flag = 3;
            } else if((data[i] & 0xf0) == 0xe0) {
                flag = 2;
            } else if((data[i] & 0xe0) == 0xc0) {
                flag = 1;
            } else if((data[i] & 0x80) == 0x00) {

            } else {
                return false;
            }
        } else {
            if((data[i] & 0xc0) == 0x80) {
                --flag;
            } else {
                return false;
            }
        }
    }

    return flag > 0 ? false:true;
}
