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
    "core_on_exit",
    "CORE_STRIP_PREFIX",
    "CORE_SEXPR_STRIP_PREFIX"};


void core_indentifier_match(
    core_Arena * a,
    const char * input,
    const char * prefix,
    core_StrVec * out
) {
    size_t i, j;
    char * dup;
    size_t len = strlen(input);
    char buf[1024];
    if(len < strlen(prefix)) return;
    for(i = 0; i < len - strlen(prefix); ++i) {
        j = strlen(prefix);
        memcpy(buf, input + i, j);
        buf[j] = 0;
        if(!core_streql(buf, prefix)) continue;
        for(;j < sizeof(buf) - 2 && core_isidentifier(input[i + j]); ++j) {
            buf[j] = input[i + j];
            buf[j + 1] = 0;
        }
        dup = core_arena_strdup(a, buf);
        core_vec_append_unique(out, a, dup, core_streql);
    }
}

int main(void) {
    core_StrVec strs = {0};
    core_Arena a = {0};
    char * file = core_file_read_all_arena(&a, "core.h");
    unsigned int i;
    core_indentifier_match(&a, file, "core_", &strs);
    core_indentifier_match(&a, file, "CORE_", &strs);
    qsort(&strs.items[0], strs.len, sizeof(strs.items[0]), core_compare_string);
    printf("#ifdef CORE_STRIP_PREFIX\n");
    for(i = 0; i < strs.len; ++i) {
        const char * str = strs.items[i];
        if(!core_streql_any(str, exclude, CORE_ARRAY_LEN(exclude))) {
            printf("#   define %s %s\n", str + 5, str);
        }
    }
    printf("#endif /*CORE_STRIP_PREFIX*/\n");

    strs.len = 0;
    core_indentifier_match(&a, file, "core_sexpr_", &strs);
    core_indentifier_match(&a, file, "CORE_SEXPR_", &strs);
    qsort(&strs.items[0], strs.len, sizeof(strs.items[0]), core_compare_string);
    printf("#ifdef CORE_SEXPR_STRIP_PREFIX\n");
    printf("#   define Sexpr core_Sexpr\n");
    for(i = 0; i < strs.len; ++i) {
        const char * str = strs.items[i];
        printf("#   define %c_%s %s\n", str[5], str + strlen("core_sexpr_"), str);
    }
    printf("#endif /*CORE_SEXPR_STRIP_PREFIX*/\n");


    core_arena_free(&a);
    return 0;
}
