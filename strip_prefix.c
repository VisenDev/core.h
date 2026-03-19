#define CORE_IMPLEMENTATION
#include "core.h"

const char * exclude[] = {
    "_CORE_H_",
    "CORE_H_",
    "CORE_C23",
    "CORE_C17",
    "CORE_C11",
    "CORE_C99",
    "CORE_C89",
    "CORE_H",
    "CORE_IMPLEMENTATION",
    "CORE_LINUX",
    "CORE_MACOS",
    "CORE_UNIX",
    "CORE_TCC",
    "CORE_GCC",
    "CORE_WINDOWS",
    "CORE_MSVC",
    "CORE_TRUE",
    "CORE_FALSE",
    "core_snprintf",
    "core_exit",
    "core_on_exit"};


int main() {
    core_Vec(const char *) strs = {0};
    core_Arena a = {0};
    unsigned int i;
    char * file = core_file_read_all_arena(&a, "core.h");
    size_t len;
    assert(file);
    len = strlen(file);
    assert(len >= 5);
    for(i = 0; i < len - 5; ++i) {
        char buf[1024];
        unsigned int j = 5;
        memcpy(buf, file + i, (size_t) j);
        buf[j] = 0;
        if(strcmp(buf, "core_") == 0 ||
           strcmp(buf, "CORE_") == 0
        ) {
            char * dup;
            for(;j < sizeof(buf) - 2 && core_isidentifier(file[i + j]); ++j) {
                buf[j] = file[i + j];
                buf[j + 1] = 0;
            }
            dup = core_arena_strdup(&a, buf);
            core_vec_append_unique(&strs, &a, dup, core_streql);
        }
    }
    for(i = 0; i < strs.len; ++i) {
        const char * str = strs.items[i];
        if(!core_streql_any(str, exclude, CORE_ARRAY_LEN(exclude))) {
            printf("#define %s %s\n", str + 5, str);
        }
    }

    core_arena_free(&a);
}
