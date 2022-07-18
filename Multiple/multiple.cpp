uint64_t binary_mult(uint64_t x, uint64_t y, uint64_t mod){
    uint64_t sum = 0;
    while(y > 0){
        if(y & 1) sum = (sum + x) % mod;
        x = (x << 1) % mod; // This part may overflow
        y >>= 1;
    }
    return sum;
}