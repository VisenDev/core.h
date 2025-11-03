#define CORE_IMPLEMENTATION
#include "core.h"

int main(void) {
    /*hashmap*/
    core_Hashmap(int) hm = {0};
    int result = 0;  

    CORE_DEFER(hashmap_cleanup) {
        core_hashmap_free(&hm);
    }
    core_hashmap_set(&hm, "foo", strlen("foo"), 1);
        
    assert(core_hashmap_get(&hm, "foo", strlen("foo"), &result));
    assert(result == 1);
    assert(!core_hashmap_get(&hm, "bar", strlen("bar"), &result));

    CORE_DEFERRED(hashmap_cleanup);

    /*file_read_all*/
    {
        FILE * fp = fopen("example.c", "r");
        char buf[6000];
        if(fp == NULL) CORE_FATAL_ERROR("failed to open example.c");
        if(!core_file_read_all(fp, buf, sizeof(buf))) CORE_FATAL_ERROR("failed to read file");
        fclose(fp);
    }

    return 0;
}
