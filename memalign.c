// cache line
#define ALIGN 64

void *aligned_malloc(int size) {
    void *mem = malloc(size+ALIGN+sizeof(void*));
    void **ptr = (void**)((uintptr_t)(mem+ALIGN+sizeof(void*)) & ~(ALIGN-1));
    ptr[-1] = mem;
    return ptr;
}

void aligned_free(void *ptr) {
    free(((void**)ptr)[-1]);
}
