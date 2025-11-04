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
        core_Arena arena = {0};
        char * contents = core_file_read_all_arena(&arena, fp);
        assert(contents);
        printf("%s", contents);
        fclose(fp);
        core_arena_free(&arena);
    }

    return 0;
}
