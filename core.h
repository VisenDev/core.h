/*
MIT License

Copyright (c) 2025 Robert Burnett

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _CORE_H_
#define _CORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

/****  C STANDARD ****/
#ifdef __STDC_VERSION
#   if __STDC_VERSION >= 202311L
#      define CORE_C23
#   elif __STDC_VERSION__ >=  201710L
#      define CORE_C17
#   elif __STDC_VERSION__ >= 201112L
#      define CORE_C11
#   elif __STDC_VERSION__ >= 199901L
#      define CORE_C99
#   endif 
#else
#   define CORE_C89
#endif /*__STDC_VERSION__*/


/**** BOOL ****/
typedef unsigned char core_Bool;
#define CORE_TRUE 1
#define CORE_FALSE 0

#if !defined(CORE_C89)
#    include <stdbool.h>
#endif

/**** ATTRIBUTES ****/
#if defined(__clang__) || defined(__GNUC__)
#   define CORE_NORETURN __attribute__((noreturn))
#   define CORE_NODISCARD __attribute__((warn_unused_result))
#else
#   define CORE_NORETURN
#   define CORE_NODISCARD
#endif /*__clang__ || __GNUC__*/


/**** ANSI ****/
#define CORE_ANSI_RED     "\x1b[31m"
#define CORE_ANSI_GREEN   "\x1b[32m"
#define CORE_ANSI_YELLOW  "\x1b[33m"
#define CORE_ANSI_BLUE    "\x1b[34m"
#define CORE_ANSI_MAGENTA "\x1b[35m"
#define CORE_ANSI_CYAN    "\x1b[36m"
#define CORE_ANSI_RESET   "\x1b[0m"


/**** MACROS ****/
#define CORE_LOG(msg) do { \
    fprintf(stderr, "%10s:%4d:0:   ", __FILE__, __LINE__);  \
    fprintf(stderr, "%s\n", msg); \
    fflush(stderr); \
} while (0)

#define CORE_UNREACHABLE do { CORE_LOG("unreachable code block reached!"); core_exit(1); } while (0)
#define CORE_TODO(msg) do { CORE_LOG(CORE_ANSI_RESET "TODO:  "); CORE_LOG(msg); core_exit(1); } while (0)
#define CORE_FATAL_ERROR(msg) do {CORE_LOG("ERROR"); CORE_LOG(msg); core_exit(1); } while (0)
#define CORE_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))


/**** EXIT ****/
#ifdef CORE_IMPLEMENTATION
#define CORE_ON_EXIT_MAX_FUNCTIONS 64
void (*core_on_exit_fns[CORE_ON_EXIT_MAX_FUNCTIONS])(void * ctx) = {0};
void * core_on_exit_ctx[CORE_ON_EXIT_MAX_FUNCTIONS] = {0};
int core_on_exit_fn_count = 0;
#endif /*CORE_IMPLEMENTATION*/


CORE_NORETURN void core_exit(int exitcode)
#ifdef CORE_IMPLEMENTATION
{
    int i = 0;
    for(i = 0; i < core_on_exit_fn_count; ++i) {
        core_on_exit_fns[i](core_on_exit_ctx[i]);
    }
    exit(exitcode);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


void core_on_exit(void (*fn)(void *ctx), void * ctx)
#ifdef CORE_IMPLEMENTATION
{
    if(core_on_exit_fn_count + 1 > CORE_ON_EXIT_MAX_FUNCTIONS) CORE_UNREACHABLE;
    core_on_exit_fns[core_on_exit_fn_count] = fn;
    core_on_exit_ctx[core_on_exit_fn_count] = ctx;
    ++core_on_exit_fn_count;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


/****  PROFILER ****/

/*profiler requires unix system*/
#ifdef __unix__

#include <sys/time.h>
long _core_profiler_timestamp(void)
#ifdef CORE_IMPLEMENTATION
{
    struct timeval currentTime = {0};
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * 1000000 + currentTime.tv_usec;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

#ifdef CORE_IMPLEMENTATION
static FILE * _core_profiler_output_file = NULL;
#endif /*CORE_IMPLEMENTATION*/

void core_profiler_init(const char * output_file_path)
#ifdef CORE_IMPLEMENTATION
{
    _core_profiler_output_file = fopen(output_file_path, "w");
    fprintf(_core_profiler_output_file, "[\n");
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void core_profiler_deinit(void)
#ifdef CORE_IMPLEMENTATION
{
    fprintf(_core_profiler_output_file, "\n]\n");
    fclose(_core_profiler_output_file);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void _core_profiler_log(const char * event_name, char begin_or_end, const char * srcfile, const int srcline)
#ifdef CORE_IMPLEMENTATION
{
    static core_Bool prepend_comma = CORE_FALSE;
    if(prepend_comma) {
        fprintf(_core_profiler_output_file, ",\n");
    }
    prepend_comma = CORE_TRUE;
    fprintf(_core_profiler_output_file,
            "{ \"name\": \"%s\", \"ph\": \"%c\", \"ts\": %ld, \"tid\": 1, \"pid\": 1, \"args\": { \"file\": \"%s\", \"line\": %d } }",
            event_name, begin_or_end, _core_profiler_timestamp(), srcfile, srcline);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

#define core_profiler_start(event) _core_profiler_log(event, 'B', __FILE__, __LINE__)
#define core_profiler_stop(event) _core_profiler_log(event, 'E', __FILE__, __LINE__)
#endif /*__unix__*/


/**** ARENA ****/
typedef struct core_Allocation {
    struct core_Allocation * next;
    void * mem;
    size_t len;
    core_Bool active;
} core_Allocation;

typedef struct {
    core_Allocation * head;
} core_Arena;

core_Allocation * core_arena_allocation_new(size_t bytes)
#ifdef CORE_IMPLEMENTATION
{
    core_Allocation * ptr = malloc(sizeof(core_Allocation));
    assert(ptr);
    ptr->mem = malloc(bytes);
    assert(ptr->mem);
    ptr->len = bytes;
    ptr->active = CORE_TRUE;
    ptr->next = NULL;
    return ptr;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

CORE_NODISCARD
void * core_arena_alloc(core_Arena * a, const size_t bytes)
#ifdef CORE_IMPLEMENTATION
{
    core_Allocation * ptr = NULL;
    if(a->head == NULL) {
        core_Allocation * head = core_arena_allocation_new(bytes);
        a->head = head;
        return a->head->mem;
    }
   ptr = a->head;
    for(;ptr->next != NULL; ptr = ptr->next) {
        if(!ptr->active && ptr->len >= bytes) {
            ptr->active = CORE_TRUE;
            return ptr->mem;
        }
    }
    assert(ptr != NULL);
    assert(ptr->next == NULL);
    {
        core_Allocation * next =  core_arena_allocation_new(bytes);
        ptr->next = next;
        return next->mem;
    }
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

CORE_NODISCARD
void * core_arena_realloc(core_Arena * a, void * ptr, const size_t bytes)
#ifdef CORE_IMPLEMENTATION
{
    core_Allocation * node = NULL;
    core_Allocation * new = NULL;
    assert(ptr != NULL);
    for(node = a->head; node != NULL && node->mem != ptr; node = node->next);
    assert(node != NULL);
    assert(node->mem == ptr);
    assert(bytes >= node->len);
    node->active = CORE_FALSE;
    new = core_arena_allocation_new(bytes);
    assert(new);
    assert(new->len >= node->len);
    memcpy(new->mem, node->mem, node->len);
    new->next = a->head;
    a->head = new;
    return new->mem;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/
    
    

void core_arena_free(core_Arena * a)
#ifdef CORE_IMPLEMENTATION
{
    core_Allocation * ptr = NULL;
    if(a->head == NULL) return;
    for(ptr = a->head;;) {
        core_Allocation * next = ptr->next;
        free(ptr->mem);
        free(ptr);
        if(next == NULL) return;
        ptr = next;
    }
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


/**** VEC ****/
#define core_Vec(Type) struct {Type * items; unsigned int len; unsigned int cap; }

#define core_vec_append(vec, arena, item) do { \
    if((vec)->cap <= 0) { \
        (vec)->cap = 8; \
        (vec)->len = 0; \
        (vec)->items = core_arena_alloc(arena, sizeof(item) * (vec)->cap); \
    } else if((vec)->len + 1 >= (vec)->cap) { \
        (vec)->cap = (vec)->cap * 2 + 1; \
        { \
            void * newmem = core_arena_alloc(arena, sizeof(item) * (vec)->cap); \
            memcpy(newmem, (vec)->items, sizeof(item) * (vec)->len);    \
        } \
    } \
    (vec)->items[(vec)->len++] = item; \
} while (0)

#define core_vec_free(vec) do { free(vec->items); vec->cap = 0; vec->len = 0;} while (0)

/**** CTYPE ****/
core_Bool core_isidentifier(char ch)
#ifdef CORE_IMPLEMENTATION
{
    return isalpha(ch) || isdigit(ch) || ch == '_';
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

/**** SYMBOL ****/
#ifndef CORE_SYMBOL_MAX_LEN
#   define CORE_SYMBOL_MAX_LEN 128
#endif /*CORE_SYMBOL_MAX_LEN*/
#ifndef CORE_MAX_SYMBOLS
#   define CORE_MAX_SYMBOLS 2048
#endif /*CORE_MAX_SYMBOLS*/

typedef int core_Symbol;
typedef struct {
    char symbols[CORE_MAX_SYMBOLS][CORE_SYMBOL_MAX_LEN];
    int count;
} core_Symbols;

core_Symbol core_symbol_intern(core_Symbols * state, const char * str)
#ifdef CORE_IMPLEMENTATION
{
    int i = 0;
    int result = -1;
    for(i = 0; i < state->count; ++i) {
        if(strcmp(state->symbols[i], str) == 0) return i;
    }
    strncpy(state->symbols[state->count], str, CORE_SYMBOL_MAX_LEN - 1);
    result = state->count;
    ++state->count;
    return result;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

const char * core_symbol_get(core_Symbols * state, core_Symbol sym)
#ifdef CORE_IMPLEMENTATION
{
    assert(sym < state->count);
    return state->symbols[sym];
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

/**** PEEK ****/
char core_peek(FILE * fp)
#ifdef CORE_IMPLEMENTATION
{
    char ch = (char)fgetc(fp);
    ungetc(ch, fp);
    return ch;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void core_skip_whitespace(FILE * fp)
#ifdef CORE_IMPLEMENTATION
{
    while(isspace(core_peek(fp))) (void)fgetc(fp);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


/**** DEFER ****/
#define CORE_DEFER(label) \
    while(0) \
        while(1) \
            if (1) { \
                goto label##_done_; \
            } else label:

#define CORE_DEFERRED(label) do { goto label; label##_done_:; } while (0)


/**** CONCAT ****/
#define CORE_CONCAT9(x, y) x##y
#define CORE_CONCAT8(x, y) CORE_CONCAT9(x, y)
#define CORE_CONCAT7(x, y) CORE_CONCAT8(x, y)
#define CORE_CONCAT6(x, y) CORE_CONCAT7(x, y)
#define CORE_CONCAT5(x, y) CORE_CONCAT6(x, y)
#define CORE_CONCAT4(x, y) CORE_CONCAT5(x, y)
#define CORE_CONCAT3(x, y) CORE_CONCAT4(x, y)
#define CORE_CONCAT2(x, y) CORE_CONCAT3(x, y)
#define CORE_CONCAT1(x, y) CORE_CONCAT2(x, y)
#define CORE_CONCAT(x, y)  CORE_CONCAT1(x, y)


/**** STATIC ASSERT ****/
#if defined(CORE_C23)
#   define STATIC_ASSERT(condition, message) static_assert(condition, message)
#elif defined(CORE_C11)
#   define STATIC_ASSERT(condition, message) _Static_assert(condition, message)
#else
#   define STATIC_ASSERT(condition, message) const int static_assertion_##__COUNTER__[ condition ? 1 : -1 ];
#endif /*__STDC_VERSION__*/

/**** ALIGNOF ****/
#if defined(__GNUC__) || defined(__clang__)
#    define CORE_ALIGNOF(type) __alignof__(type)
#elif defined(_MSC_VER)
#    define CORE_ALIGNOF(type) __alignof(type)
#else
#    define CORE_ALIGNOF(type) ((size_t)&((struct { char c; type member; } *)0)->member)
#endif /*defined(__GNUC__) || defined(__clang__)*/

/**** LIKELY ****/
#if defined(__GNUC__) || defined(__clang__)
#    define CORE_LIKELY_TRUE(expr)  __builtin_expect(expr, 1)
#    define CORE_LIKELY_FALSE(expr) __builtin_expect(expr, 0)
#else
#    define CORE_LIKELY_TRUE(expr)
#    define CORE_LIKELY_FALSE(expr)
#endif /*defined(__GNUC__) || defined(__clang__)*/


/**** STRING ****/
void core_strfmt(char * dst, size_t dst_len, size_t * dst_fill_pointer, const char * src, const size_t src_len)
#ifdef CORE_IMPLEMENTATION
{
    size_t i = 0;
    assert(dst_fill_pointer);
    assert(dst);
    assert(src);
    assert(strlen(src) == src_len && "inaccurate length");
    
    if(*dst_fill_pointer + src_len + 1 >= dst_len) CORE_FATAL_ERROR("Buffer overflow");
    for(i = 0; i < src_len; ++i) {
        dst[*dst_fill_pointer] = src[i];
        ++*dst_fill_pointer;
        assert(*dst_fill_pointer < dst_len);
    }
    dst[*dst_fill_pointer] = 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


core_Bool core_streql(const char * lhs, size_t lhs_len, const char * rhs, size_t rhs_len)
#ifdef CORE_IMPLEMENTATION
{
    size_t i = 0;
    if(lhs_len != rhs_len) {
        return CORE_FALSE;
    }
    assert(lhs_len == rhs_len);
    for(i = 0; i < lhs_len; ++i) {
        assert(lhs[i] != 0 && "Unexpected NULL terminator");
        assert(rhs[i] != 0 && "Unexpected NULL terminator");
        if(lhs[i] != rhs[i]) return CORE_FALSE;
    }
    return CORE_TRUE;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

char * core_strdup_via_arena(core_Arena * arena, const char * str, size_t len)
#ifdef CORE_IMPLEMENTATION
{
    char * new = NULL;
    unsigned long i = 0;
    assert(strlen(str) == len && "inaccurate length");
    new = core_arena_alloc(arena, len + 1);
    for(i = 0; i <= len; ++i) {
        new[i] = str[i];
    }
    assert(new[len] == 0);
    return new;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


/**** MULTI-STAGE-COMPILATION ****/

#define CORE_STAGED_NAME_LEN_MAX 128
typedef struct {
    char typename[CORE_STAGED_NAME_LEN_MAX];
    char all_lower[CORE_STAGED_NAME_LEN_MAX];
    char pascal[CORE_STAGED_NAME_LEN_MAX];
    char all_caps[CORE_STAGED_NAME_LEN_MAX];
} core_StagedNameCases;

#ifdef CORE_IMPLEMENTATION
void _core_staged_name_cases_derive(const char * prefix, const char * typename, core_StagedNameCases * result) {
    unsigned int i = 0;
    unsigned int src_i = 0;
    unsigned int dst_i = 0;
    unsigned int prefix_len = prefix == NULL ? 0 : (unsigned int)strlen(prefix);
    assert(prefix_len + strlen(typename) < CORE_STAGED_NAME_LEN_MAX);

    /*add typename*/
    strcpy(result->typename, typename);

    /*add prefixes*/
    if(prefix) {
        strcpy(result->all_lower, prefix);
        strcpy(result->pascal, prefix);
        for(i = 0; i < prefix_len; ++i) {
            result->all_caps[i] = (char)toupper(prefix[i]);
        }
    }
    
    /*pascal case*/
    for(dst_i = prefix_len, src_i = 0; typename[src_i] != 0;) {
        if(typename[src_i] == '_' || typename[src_i] == ' ') {
            ++src_i;
        } else if(typename[src_i] == '*') {
            result->pascal[dst_i++] = 'P';
            result->pascal[dst_i++] = 't';
            result->pascal[dst_i++] = 'r';
            ++src_i;
        } else {
            if(src_i == 0 || typename[src_i - 1] == ' ') {
                result->pascal[dst_i] = (char)toupper(typename[src_i]);
            } else {
                result->pascal[dst_i] = typename[src_i];
            }
            ++src_i;
            ++dst_i;
        }
    }
    
    /* all lower*/
    for(dst_i = prefix_len, src_i = 0; typename[src_i] != 0;) {
        if(typename[src_i] == '_' || typename[src_i] == ' ') {
            ++src_i;
        } else if(typename[src_i] == '*') {
            result->all_lower[dst_i++] = 'p';
            result->all_lower[dst_i++] = 't';
            result->all_lower[dst_i++] = 'r';
            ++src_i;
        } else {
            result->all_lower[dst_i] = (char)tolower(typename[src_i]);
            ++src_i;
            ++dst_i;
        }
    }

    /*all caps*/
    for(dst_i = prefix_len, src_i = 0; typename[src_i] != 0;) {
        if(typename[src_i] == '_' || typename[src_i] == ' ') {
            ++src_i;
        } else if(typename[src_i] == '*') {
            result->all_caps[dst_i++] = 'P';
            result->all_caps[dst_i++] = 'T';
            result->all_caps[dst_i++] = 'R';
            ++src_i;
        } else {
            result->all_caps[dst_i] = (char)toupper(typename[src_i]);
            ++src_i;
            ++dst_i;
        }
    }
}
#endif /*CORE_IMPLEMENTATION*/

void core_staged_slice_generate(FILE * out, const char * prefix, const char * typename)
#ifdef CORE_IMPLEMENTATION
{
    core_StagedNameCases cases = {0};
    _core_staged_name_cases_derive(prefix, typename, &cases);

    fprintf(out, "#ifndef _%sSLICE_\n", cases.all_caps);
    fprintf(out, "#define _%sSLICE_\n\n", cases.all_caps);
    fprintf(out, "#include <assert.h>\n\n");
    
    fprintf(
        out,
        "typedef struct {\n"
        "   %s * ptr;\n"
        "   int len;\n"
        "} %sSlice;\n"
        "\n",
        cases.typename,
        cases.pascal
    );
    fprintf(
        out,
        "%sSlice %sslice_init(%s * items, unsigned long count) {\n"
        "    %sSlice result = {0};\n"
        "    result.ptr = items;\n"
        "    result.len = count;\n"
        "    return result;\n"
        "}\n"
        "\n",
        cases.pascal,
        cases.all_lower,
        cases.typename,
        cases.pascal
    );
    fprintf(
        out,
        "#define %sSLICE_FROM_ARRAY(array) "
        "%sslice_init(array, (sizeof(array) / sizeof(array[0])))\n"
        "\n",
        cases.all_caps,
        cases.all_lower
    );
    fprintf(
        out,
        "%sSlice %sslice_get_first_n_items(%sSlice slice, int n) {\n"
        "    %sSlice result = slice;\n"
        "    assert(n <= slice.len);\n"
        "    result.len = n;\n"
        "    return result;\n"
        "}\n"
        "\n",
        cases.pascal,
        cases.all_lower,
        cases.pascal,
        cases.pascal
    );
    fprintf(
        out,
        "%sSlice %sslice_get_last_n_items(%sSlice slice, int n) {\n"
        "    %sSlice result = slice;\n"
        "    assert(n <= slice.len);\n"
        "    result.len = n;\n"
        "    result.ptr += slice.len - n;\n"
        "    return result;\n"
        "}\n"
        "\n",
        cases.pascal,
        cases.all_lower,
        cases.pascal,
        cases.pascal
    );
    fprintf(
        out,
        "%sSlice %sslice_trim_first_n_items(%sSlice slice, int n) {\n"
        "    %sSlice result = slice;\n"
        "    assert(n <= slice.len);\n"
        "    result.len = slice.len - n;\n"
        "    result.ptr += slice.len - n;\n"
        "    return result;\n"
        "}\n"
        "\n",
        cases.pascal,
        cases.all_lower,
        cases.pascal,
        cases.pascal
    );
    fprintf(
        out,
        "%sSlice %sslice_trim_last_n_items(%sSlice slice, int n) {\n"
        "    %sSlice result = slice;\n"
        "    assert(n <= slice.len);\n"
        "    result.len = slice.len - n;\n"
        "    return result;\n"
        "}\n"
        "\n",
        cases.pascal,
        cases.all_lower,
        cases.pascal,
        cases.pascal
    );
    
    fprintf(out, "#endif /*_%sSLICE_*/\n\n", cases.all_caps);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void core_staged_vec_generate(FILE * out, const char * prefix, const char * typename)
#ifdef CORE_IMPLEMENTATION
{
    core_StagedNameCases cases = {0};
    _core_staged_name_cases_derive(prefix, typename, &cases);

    fprintf(out, "#ifndef _%sVEC_\n", cases.all_caps);
    fprintf(out, "#define _%sVEC_\n\n", cases.all_caps);

    fprintf(
        out,
        "#include <stdlib.h>\n"
        "#include <assert.h>\n\n"
    );

    fprintf(
        out,
        "typedef struct {\n"
        "    %s * items;\n"
        "    unsigned long len;\n"
        "    unsigned long cap;\n"
        "} %sVec;\n"
        "\n",
        cases.typename,
        cases.pascal
    );
    fprintf(
        out,
        "void %svec_ensure_capacity(%sVec * vec, unsigned long capacity) {\n"
        "    if(vec->items == NULL || vec->cap <= 0) {\n"
        "        vec->cap = capacity;\n"
        "        vec->items = malloc(vec->cap * sizeof(vec->items[0]));\n"
        "        assert(vec->items);\n"
        "        vec->len = 0;\n"
        "    } else if(vec->cap < capacity) {\n"
        "        vec->cap = capacity * 2;\n"
        "        vec->items = realloc(vec->items, vec->cap * sizeof(vec->items[0]));\n"
        "        assert(vec->items);\n"
        "    }\n"
        "    assert(vec->cap >= capacity);\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal
    );
    fprintf(
        out,
        "#ifdef _CORE_H_\n"
        "void %svec_ensure_capacity_via_arena(%sVec * vec, core_Arena * arena, unsigned long capacity) {\n"
        "    if(vec->items == NULL || vec->cap <= 0) {\n"
        "        vec->cap = capacity;\n"
        "        vec->items = core_arena_alloc(arena, vec->cap * sizeof(vec->items[0]));\n"
        "        vec->len = 0;\n"
        "    } else if(vec->cap < capacity) {\n"
        "        vec->cap = capacity * 2;\n"
        "        vec->items = core_arena_realloc(arena, vec->items, vec->cap * sizeof(vec->items[0]));\n"
        "    }\n"
        "    assert(vec->cap >= capacity);\n"
        "}\n"
        "#endif /*_CORE_H_*/\n"
        "\n",
        cases.all_lower,
        cases.pascal
    );
    
    fprintf(
        out,
        "void %svec_append(%sVec * vec, %s item) {\n"
        "    %svec_ensure_capacity(vec, vec->len + 1);\n"
        "    vec->items[vec->len++] = item;\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        cases.typename,
        cases.all_lower
    );
    fprintf(
        out,
        "#ifdef _CORE_H_\n"
        "void %svec_append_via_arena(%sVec * vec, core_Arena * arena, %s item) {\n"
        "    %svec_ensure_capacity_via_arena(vec, arena, vec->len + 1);\n"
        "    vec->items[vec->len++] = item;\n"
        "}\n"
        "#endif /*_CORE_H_*/\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        cases.typename,
        cases.all_lower
    );
    fprintf(
        out,
        "void %svec_free(%sVec * vec) {\n"
        "    if(vec->items != NULL || vec->cap > 0) {\n"
        "        free(vec->items);\n"
        "    }\n"
        "    vec->len = 0;\n"
        "    vec->cap = 0;\n"
        "    vec->items = NULL;\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal
    );
    fprintf(
        out,
        "void %svec_append_n_times(%sVec * vec, %s item, unsigned long times) {\n"
        "    unsigned long i = 0;\n"
        "    %svec_ensure_capacity(vec, vec->len + times);\n"
        "    for(i = 0; i < times; ++i) {\n"
        "        %svec_append(vec, item);\n"
        "    }\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        cases.typename,
        cases.all_lower,
        cases.all_lower
    );
    fprintf(
        out,
        "void %svec_ensure_length(%sVec * vec, %s default_value, unsigned long minimum_length) {\n"
        "    if(vec->len >= minimum_length) return;\n"
        "    %svec_append_n_times(vec, default_value, minimum_length - vec->len);\n"
        "    assert(vec->len >= minimum_length);\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        cases.typename,
        cases.all_lower
    );
    fprintf(
        out,
        "%s %svec_get(%sVec * vec, unsigned long index) {\n"
        "    assert(index < vec->len);\n"
        "    return vec->items[index];\n"
        "}\n"
        "\n",
        cases.typename,
        cases.all_lower,
        cases.pascal
    );
    fprintf(
        out,
        "%s %svec_pop(%sVec * vec) {\n"
        "    assert(vec->len > 0);\n"
        "    return vec->items[--vec->len];\n"
        "}\n"
        "\n",
        cases.typename,
        cases.all_lower,
        cases.pascal
    );
        
    fprintf(out, "#endif /*_%sVEC_*/\n\n", cases.all_caps);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void core_staged_sset_generate(FILE * out, const char * prefix, const char * typename)
#ifdef CORE_IMPLEMENTATION
{
    core_StagedNameCases cases = {0};
    _core_staged_name_cases_derive(prefix, typename, &cases);
        
    fprintf(out, "#ifndef _%sSSET_\n", cases.all_caps);
    fprintf(out, "#define _%sSSET_\n\n", cases.all_caps);
    fprintf(out, "#include <assert.h>\n\n");

    core_staged_vec_generate(out, prefix, "unsigned long");
    core_staged_vec_generate(out, prefix, "unsigned long");
    core_staged_vec_generate(out, prefix, typename);
    fprintf(
        out,
        "typedef struct {\n"
        "    %sVec dense;\n"
        "    %sUnsignedLongVec dense_to_sparse;\n"
        "    %sUnsignedLongVec sparse;\n"
        "} %sSSet;\n"
        "\n",
        cases.pascal,
        prefix,
        prefix,
        cases.pascal
    );
    fprintf(
        out,
        "void %ssset_insert(%sSSet * sset, unsigned long index, %s item) {\n"
        "    unsigned long dense_index = 0;\n"
        "    %sunsignedlongvec_ensure_length(&sset->sparse, 0, index + 1);\n"
        "    dense_index = sset->sparse.items[index];\n"
        "    if(dense_index == 0) {\n"
        "        assert(sset->dense.len == sset->dense_to_sparse.len);\n"
        "        dense_index = sset->dense.len;\n"
        "        %svec_append(&sset->dense, item);\n"
        "        %sunsignedlongvec_append(&sset->dense_to_sparse, index);\n"
        "        sset->sparse.items[index] = dense_index + 1; /*dense index is incremented by 1 so that zero is the NULL value*/\n"
        "    } else {\n"
        "        dense_index -= 1; /*adjust the dense index back to baseline (the dense_index in the sparse array is always 1 higher than the actual index)*/\n"
        "        sset->dense.items[dense_index] = item;\n"
        "    }\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        cases.typename,
        prefix,
        cases.all_lower,
        prefix
    );
    fprintf(
        out,
        "void %ssset_free(%sSSet * sset) {\n"
        "    %sunsignedlongvec_free(&sset->dense_to_sparse);\n"
        "    %sunsignedlongvec_free(&sset->sparse);\n"
        "    %svec_free(&sset->dense);\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        prefix,
        prefix,
        cases.all_lower
    );
    fprintf(
        out,
        "int %ssset_get(%sSSet * sset, unsigned long index, %s * result) {\n"
        "    if(index >= sset->sparse.len) return 1;\n"
        "    assert(index < sset->sparse.len);\n"
        "    if(sset->sparse.items[index] == 0) return 1;\n"
        "    if(result == NULL) return 0;\n"
        "    *result = sset->dense.items[sset->sparse.items[index] - 1];\n"
        "    return 0;\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        cases.typename
    );
    fprintf(
        out,
        "void %ssset_remove(%sSSet * sset, unsigned long index) {\n"
        "    %s top = {0};\n"
        "    unsigned long top_index = 0;\n"
        "    assert(sset->dense.len == sset->dense_to_sparse.len);\n"
        "    assert(sset->dense.len > 0);\n"
        "    if(index >= sset->sparse.len) return;\n"
        "    if(sset->sparse.items[index] == 0) return;\n"
        "    top = %svec_pop(&sset->dense);\n"
        "    top_index = %sunsignedlongvec_pop(&sset->dense_to_sparse);\n"
        "    sset->dense.items[sset->sparse.items[index] - 1] = top;\n"
        "    sset->sparse.items[top_index] = sset->sparse.items[index];\n"
        "    sset->dense_to_sparse.items[sset->sparse.items[index] - 1] = top_index;\n"
        "    sset->sparse.items[index] = 0;\n"
        "}\n"
        "\n",
        cases.all_lower,
        cases.pascal,
        cases.typename,
        cases.all_lower,
        prefix
    );

        
    fprintf(out, "#endif /*_%sSSET_*/\n\n", cases.all_caps);
    
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

#ifdef CORE_IMPLEMENTATION
const char * _core_string_toupper(const char * str) {
    static char buf[1024] = {0};
    unsigned long i = 0; 
    assert(strlen(str) + 1 < sizeof(buf));
    for(i = 0; str[i] != 0; ++i) {
        assert(i + 1 < sizeof(buf));
        buf[i] = (char)toupper(str[i]);
    }
    buf[i] = 0;
    return buf;
}
#endif /*CORE_IMPLEMENTATION*/

void core_staged_enum_generate(FILE * out, const char * prefix, const char * enum_name, unsigned long len, const char ** field_names)
#ifdef CORE_IMPLEMENTATION
{
    core_StagedNameCases cases = {0};
    char prefix_and_name[1024] = {0};
    unsigned int i = 0;
    size_t fill_tracker = 0;
    /*    assert(prefix_len + enum_name_len + 1 < sizeof(prefix_and_name));*/
    core_strfmt(prefix_and_name, sizeof(prefix_and_name), &fill_tracker, prefix, strlen(prefix));
    core_strfmt(prefix_and_name, sizeof(prefix_and_name), &fill_tracker, enum_name, strlen(enum_name));
    core_strfmt(prefix_and_name, sizeof(prefix_and_name), &fill_tracker, "_", strlen("_"));
    
    /*sprintf(prefix_and_name, "%s%s_", prefix, enum_name);*/
    _core_staged_name_cases_derive(prefix, enum_name, &cases);
    fprintf(out, "#ifndef _%s_ENUM_\n", cases.all_caps);
    fprintf(out, "#define _%s_ENUM_\n", cases.all_caps);
    fprintf(out, "\n");

    fprintf(out, "#define %s_COUNT %lu\n", cases.all_caps, len);
    fprintf(out, "typedef enum {\n");
    for(i = 0; i < len; ++i) {
        fprintf(out, "    %s_%s", cases.all_caps, _core_string_toupper(field_names[i]));
        if(i + 1 < len) {
            fprintf(out, ",");
        }
        fprintf(out, "\n");
    }
    fprintf(out, "} %s;\n", cases.pascal);
    fprintf(out, "\n");

    fprintf(out, "const char * %s_names[] = {\n", cases.all_lower);
    for(i = 0; i < len; ++i) {
        fprintf(out, "    \"%s_%s\"", cases.all_caps, _core_string_toupper(field_names[i]));
        if(i + 1 < len) {
            fprintf(out, ",");
        }
        fprintf(out, "\n");
    }
    fprintf(out, "};\n");
    fprintf(out, "\n");
    fprintf(out, "#endif /*_%s_ENUM_*/\n", cases.all_caps);
    fprintf(out, "\n");

}
#else
;
#endif /*CORE_IMPLEMENTATION*/

typedef struct {
    const char * name;
    const char * type;
} core_StagedTaggedUnionFields;

void core_staged_taggedunion_generate(FILE * out, const char * prefix, const char * name, unsigned long len, const char ** field_types, const char ** field_names)
#ifdef CORE_IMPLEMENTATION
{
    static char buf[1024] = {0};
    core_StagedNameCases enum_cases = {0};
    core_StagedNameCases cases = {0};
    unsigned long i = 0;
    size_t fill_pointer = 0;
    assert(strlen(name) + 4 < sizeof(buf));
    core_strfmt(buf, sizeof(buf), &fill_pointer, name, strlen(name));
    core_strfmt(buf, sizeof(buf), &fill_pointer, "Tag", strlen("Tag"));
    /*sprintf(buf, "%sTag", name);*/
    core_staged_enum_generate(out, prefix, buf, len, field_names);

    _core_staged_name_cases_derive(prefix, buf, &enum_cases);
    _core_staged_name_cases_derive(prefix, name, &cases);
    
    fprintf(out, "#ifndef _%s_TAGGEDUNION_\n", cases.all_caps);
    fprintf(out, "#define _%s_TAGGEDUNION_\n", cases.all_caps);
    fprintf(out, "\n");

    
    fprintf(out, "typedef struct {\n");
    fprintf(out, "    %s tag;\n", enum_cases.pascal);
    fprintf(out, "    union {\n");
    for(i = 0; i < len; ++i) {
        fprintf(out, "        %s %s;\n", field_types[i], field_names[i]);
    }
    fprintf(out, "    } as;\n");
    fprintf(out, "} %s;\n", cases.pascal);
    fprintf(out, "\n");

    for(i = 0; i < len; ++i) {
        fprintf(
            out,
            "%s %s_%s_make(%s value) {\n"
            "    %s result = {0};\n"
            "    result.tag = %s_%s;\n"
            "    result.as.%s = value;\n"
            "    return result;\n"
            "}\n"
            "\n",
            cases.pascal,
            cases.all_lower,
            field_names[i],
            field_types[i],
            cases.pascal,
            enum_cases.all_caps,
            _core_string_toupper(field_names[i]),
            field_names[i]
        );
    }
    
    for(i = 0; i < len; ++i) {
        fprintf(
            out,
            "%s %s_%s_get(%s value) {\n"
            "    assert(value.tag == %s_%s);\n"
            "    return value.as.%s;\n"
            "}\n"
            "\n",
            field_types[i],
            cases.all_lower,
            field_names[i],
            cases.pascal,
            enum_cases.all_caps,
            _core_string_toupper(field_names[i]),
            field_names[i]
        );
    }

    fprintf(out, "#endif /*_%s_TAGGEDUNION_*/\n", cases.all_caps);
    fprintf(out, "\n");


}
#else
;
#endif /*CORE_IMPLEMENTATION*/


/**** BITSET ****/
#define CORE_BITARRAY(n) struct { char bits[(n / CHAR_BIT) + 1]; }
typedef CORE_BITARRAY(8) core_BitArray8;
typedef CORE_BITARRAY(16) core_BitArray16;
typedef CORE_BITARRAY(32) core_BitArray32;
typedef CORE_BITARRAY(64) core_BitArray64;
typedef CORE_BITARRAY(128) core_BitArray128;
typedef CORE_BITARRAY(256) core_BitArray256;
typedef CORE_BITARRAY(512) core_BitArray512;
typedef CORE_BITARRAY(1024) core_BitArray1024;
typedef CORE_BITARRAY(2048) core_BitArray2048;
typedef CORE_BITARRAY(4096) core_BitArray4096;
typedef CORE_BITARRAY(8192) core_BitArray8192;

void core_bitarray_set(void * ptr, unsigned int bit)
#ifdef CORE_IMPLEMENTATION
{
    (void)(ptr);
    (void)(bit);
    CORE_TODO("implement");
}
#else
;
#endif /*CORE_IMPLEMENTATION*/
/*#define CORE_BITSET_SET(bitset, bit) (assert(bit / CHARBIT) < sizeof(bitset->bits), bitset->bits[bit / CHARBIT] >> bit % CHARBIT)*/

typedef struct {
    unsigned char * bits;
    unsigned int len;
} core_BitVec;

void core_bitvec_set(core_BitVec * self, unsigned int bit)
#ifdef CORE_IMPLEMENTATION
{
    const unsigned int index = bit / CHAR_BIT;
    const unsigned char shift = bit % CHAR_BIT;
    const unsigned char byte = (unsigned char)(1 << shift);
    if(self->bits == NULL || self->len == 0) {
        self->len = index + 1;
        self->bits = malloc(sizeof(self->bits[0]) * self->len);
        assert(self->bits);
        memset(self->bits, 0, self->len);
    } else if(index + 1 > self->len) {
        const unsigned int oldlen = self->len;
        self->len = index + 1;
        self->bits = realloc(self->bits, sizeof(self->bits[0]) * self->len);
        assert(self->bits);
        memset(&self->bits[oldlen], 0, self->len - oldlen);
    }
    self->bits[index] |= byte;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


/**** HASH ****/

unsigned long core_hash(const char * key, size_t keylen, unsigned long modulus) 
#ifdef CORE_IMPLEMENTATION
{
    /* Inspired by djbt2 by Dan Bernstein - http://www.cse.yorku.ca/~oz/hash.html */
    unsigned long hash = 5381;
    unsigned long i = 0;

    for(i = 0; i < keylen; ++i) {
        unsigned char c = (unsigned char)key[i];
        assert(c != 0 && "keylen should reflect the location of the null terminator");
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return (hash % modulus);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/


/**** HASHMAP ****/

typedef struct {
    char * key;
    size_t keylen;
    void * value;
    size_t value_byte_count;
} core_HashmapEntry;

typedef core_Vec(core_HashmapEntry) core_HashmapBucket;

typedef core_Vec(core_HashmapBucket) core_HashmapBuckets;

typedef struct {
    core_Arena arena;
    unsigned int num_entries;
    core_HashmapBuckets buckets;
} core_Hashmap;

#define CORE_HASHMAP_REHASH_DENSITY_THRESHOLD 0.5f

float core_hashmap_density_calculate(core_Hashmap * self)
#ifdef CORE_IMPLEMENTATION
{
    if(self->buckets.len == 0) return 1.0;
    return (float)self->num_entries / (float)self->buckets.len;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void core_hashmap_init_capacity(unsigned long initial_capacity, core_Hashmap * result)
#ifdef CORE_IMPLEMENTATION
{
    unsigned long i = 0;
    memset(result, 0, sizeof(core_Hashmap));
    for(i = 0; i < initial_capacity; ++i) {
        core_HashmapBucket nullbucket = {0};
        core_vec_append(&result->buckets, &result->arena, nullbucket);
    }
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void core_hashmap_set(core_Hashmap * self, const char * key, size_t keylen, void * value, size_t value_byte_count);

void core_hashmap_rehash(core_Hashmap * self, unsigned long new_capacity) {
    unsigned long i = 0;
    unsigned long j = 0;
    core_Hashmap temp = {0};
    assert(new_capacity > self->buckets.len);
    core_hashmap_init_capacity(new_capacity, &temp);
    for(i = 0; i < self->buckets.len; ++i) {
        core_HashmapBucket bucket = self->buckets.items[i];
        for(j = 0; j < bucket.len; ++j) {
            core_HashmapEntry entry = bucket.items[j];
            if(entry.key == NULL) continue;
            core_hashmap_set(&temp, entry.key, entry.keylen, entry.value, entry.value_byte_count);
        }
    }
    core_arena_free(&self->arena);
    *self = temp;
}

core_HashmapBucket * core_hashmap_bucket_find(core_Hashmap * self, const char * key, size_t keylen) {
    unsigned long hash = (unsigned long)-1;
    if(core_hashmap_density_calculate(self) > CORE_HASHMAP_REHASH_DENSITY_THRESHOLD) {
        core_hashmap_rehash(self, (self->buckets.len + 1) * 2);
    }
    hash = core_hash(key, keylen, self->buckets.len);
    return &self->buckets.items[hash];
}

core_Bool core_hashmap_get(core_Hashmap * self, const char * key, size_t keylen, void * result, size_t result_byte_count)
#ifdef CORE_IMPLEMENTATION
{
    core_HashmapBucket * bucket = core_hashmap_bucket_find(self, key, keylen);
    unsigned long i = 0;
    for(i = 0; i < bucket->len; ++i) {
        core_HashmapEntry * entry = &bucket->items[i];
        if(core_streql(entry->key, entry->keylen, key, keylen)) {
            assert(entry->value_byte_count == result_byte_count);
            memcpy(result, entry->value, result_byte_count);
            return CORE_TRUE;
        }
    }

    return CORE_FALSE;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

void core_hashmap_set(core_Hashmap * self, const char * key, size_t keylen, void * value, size_t value_byte_count) {
    core_HashmapBucket * bucket = core_hashmap_bucket_find(self, key, keylen);
    unsigned long i = 0;
    for(i = 0; i < bucket->len; ++i) {
        core_HashmapEntry * entry = &bucket->items[i];
        if(core_streql(entry->key, entry->keylen, key, keylen)) {
            assert(entry->value_byte_count == value_byte_count);
            memcpy(entry->value, value, value_byte_count);
            return;
        }
    }
    /*no matching key found, append a new one*/
    {
        core_HashmapEntry entry = {0};
        entry.key = core_strdup_via_arena(&self->arena, key, keylen);
        entry.keylen = keylen;
        entry.value = core_arena_alloc(&self->arena, value_byte_count);
        memcpy(entry.value, value, value_byte_count);
        entry.value_byte_count = value_byte_count;
        core_vec_append(bucket, &self->arena, entry);
    }
}


#define core_Hm(Type) struct { core_Hashmap backing; core_Bool error; Type temp; }

#define core_hm_set(self, key, keylen, value) do {(self)->temp = value; core_hashmap_set(&(self)->backing, key, keylen, &(self)->temp, sizeof((self)->temp)); } while (0)
#define core_hm_get(self, key, keylen, result_ptr) ((self)->error = core_hashmap_get(&(self)->backing, key, keylen, &(self)->temp, sizeof((self)->temp)), *(result_ptr) = (self)->temp, (self)->error)

#endif /*_CORE_H_*/
