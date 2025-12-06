#define CORE_IMPLEMENTATION
#include "core.h"

int main(void) {
    /*hashmap*/
    core_Hashmap(int) hm = {0};
    int result = 0;
    char sym[7];
    int i;

    CORE_DEFER(hashmap_cleanup) {
        core_hashmap_free(&hm);
    }
    core_hashmap_set(&hm, "foo", 1);
    core_hashmap_set(&hm, "bapp", 1);
    core_hashmap_set(&hm, "bop", 1);
    core_hashmap_set(&hm, "boop", 4);
        
    assert(core_hashmap_get(&hm, "foo", &result));
    assert(result == 1);
    assert(!core_hashmap_get(&hm, "bar", &result));
    assert(core_hashmap_get(&hm, "boop", &result));
    assert(result == 4);

    /* Iterate through all values */
    core_hashmap_reset_next(&hm);
    {
        const char * key;
        while(core_hashmap_next(&hm, &result, &key, NULL)) {
            printf("start: \"%s\" = %d,\n", key, result);
        }
    }
    printf("\n");


    for(i = 0; i < 20; ++i) {
        core_gensym(sym, sizeof(sym));
        core_hashmap_set(&hm, sym, rand());
    }

    /* Iterate through all values */
    core_hashmap_reset_next(&hm);
    {
        const char * key;
        while(core_hashmap_next(&hm, &result, &key, NULL)) {
            printf("\"%s\" = %d,\n", key, result);
        }
    }
    printf("\n");


    CORE_DEFERRED(hashmap_cleanup);

    /*file_read_all*/
    {
        core_Arena arena = {0};
        char * contents = core_file_read_all_arena(&arena, "example.c");
        /* assert(contents); */
        (void)contents;
        /*printf("%s", contents);*/
        core_arena_free(&arena);
    }


    {
        core_Arena a = {0};
        core_HashmapV2(int) h = {0};
        
        core_hashmapv2_set(&h, &a, "urmom", 69);
        assert(core_hashmapv2_get(&h, "urmom") != NULL);
        assert(*core_hashmapv2_get(&h, "urmom") == 69);
        
        core_arena_free(&a);
    }

    return 0;
}
