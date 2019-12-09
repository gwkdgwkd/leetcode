uint32_t reverseBits(uint32_t n) {
    uint32_t rst = 0;
    for(int i = 0; i < 32; ++i){
    	rst |= ( ( (n>>i) & 0x00000001 )<<(31-i) );
    }
    return rst;
}
