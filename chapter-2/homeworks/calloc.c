#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Solution to 2.76
// ----------------

void *ccalloc(size_t nmemb, size_t size);

int main() 
{
    void *ptr;

    ptr = ccalloc(5, sizeof(int));
    printf("5 ints = %p\n", ptr);
    free(ptr);
    
    ptr = ccalloc(SIZE_MAX, 3);
    printf("5 SIZE_MAX = %p\n", ptr);

    return 0;
}

void *ccalloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return NULL;

    size_t space = nmemb * size;

    if (nmemb != space / size)
        return NULL;

    void *ptr = malloc(space);

    for (size_t n = 0; n < nmemb; n++) {
        if (ptr == NULL) continue;
        memset(ptr, 0, n);
    }

    return ptr;
}

