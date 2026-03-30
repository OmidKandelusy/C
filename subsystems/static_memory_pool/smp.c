int buffer_init(uint8_t *pool_name, int s_size, int s_count){
    int ret = SMP_SUCCESS;
    if (!pool_name) return SMP_NULL_POINTER;

    printf("slot size: %d, slot count:%d \n\r", s_size, s_count);

    return ret;
}