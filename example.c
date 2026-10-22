#define CORE_IMPLEMENTATION
#include "core.h"

int main(void) {
    /*hashmap*/
    core_Hashmap(int) hm = {0};
    core_Arena a = {0};
    char sym[7];
    int i;


    CORE_DEFER(hashmap_cleanup) {
        core_arena_free(&a);
    }
    core_hashmap_set(&hm, &a, "foo", 1);
    core_hashmap_set(&hm, &a, "bapp", 1);
    core_hashmap_set(&hm, &a, "bop", 1);
    core_hashmap_set(&hm, &a, "boop", 4);
        
    assert(*core_hashmap_get(&hm, "foo") == 1);
    assert(!core_hashmap_get(&hm, "bar"));
    assert(*core_hashmap_get(&hm, "boop") == 4);

    for(i = 0; i < 20; ++i) {
        core_gensym(sym, sizeof(sym));
        core_hashmap_set(&hm, &a, sym, rand());
    }

    /* Iterate through all values */
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
        core_Arena arena = {0};
        core_Hashmap(int) h = {0};
        char buf[8];
        
        for(i = 0; i < 200; ++i) {
            int val = rand();
            core_gensym(buf, sizeof(buf));
            core_hashmap_set(&h, &arena, buf, val);
        }
        core_hashmap_set(&h, &arena, "urmom", 69);
        assert(core_hashmap_get(&h, "urmom") != NULL);
        assert(*core_hashmap_get(&h, "urmom") == 69);

        for(i = 0; i < (long)h.keys.len; ++i) {
            /* printf("%s = %d,\n", h.keys.items[i], h.values.items[i]); */
        }
        
        core_arena_free(&arena);
    }

    {
        core_Arena arena = {0};
        core_Sexpr * s = core_sexpr_parse(
            &arena,
            "(foo (bar bap) (1 2 3) (\"hello\")"
            " ((()) \" the \") (\"aaaaa\\\"aaaaa\")"
            "            1    2   )");
        assert(s);
        s = core_sexpr_parse(
            &arena, "(age 10 name \"john\\\" mark\\n\" type :person health 0.5)");
        assert(core_plist_int(s, "age") == 10);
        assert(core_streql(core_plist_string(&arena, s, "name"), "john\" mark\n"));
        assert(core_streql(core_plist_atom(s, "type"), ":person"));
        assert(core_plist_float(s, "health") >= 0.5f);
        core_sexpr_print(s);
        core_arena_free(&arena);
    }

    return 0;
}
