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
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//// ATTRIBUTES
#if defined(__clang__) || defined(__GNUC__)
#   define core_NORETURN __attribute__((noreturn))
#   define core_NODISCARD __attribute__((warn_unused_result))
#else
#   define core_NORETURN
#   define core_NODISCARD
#endif /*__clang__ || __GNUC__*/

//// EXIT
void core_on_exit(void (*fn)(void *ctx), void * ctx);
core_NORETURN void core_exit(int exitcode);

//// MACROS
#define core_LOG(...) do { fprintf(stderr, "%s:%d:0:   ", __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr); } while (0)
#define core_UNREACHABLE do { core_LOG("unreachable code block reached!"); core_exit(1); } while (0)
#define core_TODO(...) do { core_LOG("TODO" __VA_ARGS__); core_exit(1); } while (0)

//// ARENA
typedef struct core_Allocation {
    struct core_Allocation * next;

    void * mem;
    size_t len;
    bool active;
} core_Allocation;

typedef struct {
    core_Allocation * head;
} core_Arena;

core_NODISCARD
void * core_arena_alloc(core_Arena *, const size_t);
void core_arena_free(core_Arena *);

//// VEC
#define core_Vec(Type) struct {Type * items; int len; int cap; }
#define core_vec_append(vec, arena, item) do { \
    if((vec)->cap <= 0) { \
        (vec)->cap = 8; \
        (vec)->len = 0; \
        (vec)->items = core_arena_alloc(arena, sizeof(item) * (vec)->cap); \
    } else if((vec)->len + 1 >= (vec)->cap) { \
        (vec)->cap = (vec)->cap * 2 + 1; \
        void * newmem = core_arena_alloc(arena, sizeof(item) * (vec)->cap); \
        memcpy(newmem, (vec)->items, sizeof(item) * (vec)->len); \
    } \
    (vec)->items[(vec)->len++] = item; \
} while (0)


//// CTYPE
bool core_isidentifier(char ch);

/*===================IMPLEMENTATION===================*/
#ifdef CORE_IMPLEMENTATION

//// EXIT
#define core_ON_EXIT_MAX_FUNCTIONS 64
void (*core_on_exit_fns[core_ON_EXIT_MAX_FUNCTIONS])(void * ctx) = {0};
void * core_on_exit_ctx[core_ON_EXIT_MAX_FUNCTIONS] = {0}; 
int core_on_exit_fn_count = 0;

void core_on_exit(void (*fn)(void *ctx), void * ctx) {
    if(core_on_exit_fn_count + 1 > core_ON_EXIT_MAX_FUNCTIONS) UNREACHABLE;
    core_on_exit_fns[core_on_exit_fn_count] = fn; 
    core_on_exit_ctx[core_on_exit_fn_count] = ctx; 
    ++core_on_exit_fn_count;
}

core_NORETURN
void core_exit(int exitcode) {
    for(int i = 0; i < core_on_exit_fn_count; ++i) {
        core_on_exit_fns[i](core_on_exit_ctx[i]);
    }
    exit(exitcode);
}

//// PROFILER
unsigned long core_profiler_timestamp(void) {
    struct timeval currentTime = {0};
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * 1000000 + currentTime.tv_usec;
}

static FILE * core_profiler_output_file = NULL;
void core_profiler_init(const char * output_file_path) {
    core_profiler_output_file = fopen(output_file_path, "w");
    fprintf(blok_profiler_output_file, "[\n");
}

void core_profiler_deinit(void) {
    fprintf(core_profiler_output_file, "\n]\n");
    fclose(core_profiler_output_file);
}

#define core_profiler_start(event) _core_profiler_log(event, 'B', __FILE__, __LINE__)
#define core_profiler_stop(event) _core_profiler_log(event, 'E', __FILE__, __LINE__)
void _core_profiler_log(const char * event_name, char begin_or_end, const char * srcfile, const int srcline) {
    static bool prepend_comma = false;
    if(prepend_comma) {
        fprintf(output, ",\n");
    } 
    prepend_comma = true;
    fprintf(core_profiler_output_file,
            "{ \"name\": \"%s\", \"ph\": \"%c\", \"ts\": %lu, \"tid\": 1, \"pid\": 1, \"args\": { \"file\": \"%s\", \"line\": %d } }",
            name, begin_or_end, core_profiler_timestamp(), file, line);
}


//// ARENA
core_Allocation * core_arena_allocation_new(size_t bytes) {
    core_Allocation * ptr = malloc(sizeof(core_Allocation));
    ptr->mem = malloc(bytes);
    ptr->len = bytes;
    ptr->active = true;
    ptr->next = NULL;
    return ptr;
}

void * core_arena_alloc(core_Arena * a, const size_t bytes) {
    if(a->head == NULL) {
        core_Allocation * head =  core_arena_allocation_new(bytes);       
        a->head = head;
        return a->head->ptr;
    }
    for(core_Allocation * ptr = a->head; ptr->next != NULL; ptr = ptr->next) {
        if(!ptr->active && ptr->len >= bytes) {
            ptr->active = true;
            return ptr->mem;
        }
    }
    assert(ptr != NULL);
    assert(ptr->next != NULL);
    core_Allocation * next =  core_arena_allocation_new(bytes);       
    ptr->next = next;
    return next->mem;
}

void core_arena_free(core_Arena * a) {
    if(a->ptr == NULL) return;
    for(core_Allocation * ptr = a->head;;) {
        core_Allocation * next = ptr->next;
        free(ptr->mem);
        free(ptr);
        if(next == NULL) return;
        ptr = next;
    }
}

//// CTYPE
bool core_isidentifier(char ch) {
    return isalpha(ch) || isdigit(ch) || ch == '_';
}


//// SYMBOL
#ifndef core_SYMBOL_MAX_LEN
#   define core_SYMBOL_MAX_LEN 32
#endif /*core_SYMBOL_MAX_LEN*/
#define core_MAX_SYMBOLS
#   define core_MAX_SYMBOLS 128
#endif /*core_MAX_SYMBOLS*/

typedef int core_Symbol;
typedef struct {
    char symbols[core_MAX_SYMBOLS][core_SYMBOL_MAX_LEN];
    int count;
} core_Symbols;

core_Symbol core_symbol_intern(core_Symbols * state, const char * str) {
    for(int i = 0; i < state->count; ++i) {
        if(strcmp(state->symbols[i], str) == 0) return i;
    }
    strncpy(state->symbols[state->count], str, core_SYMBOL_MAX_LEN - 1);
    int result = state->count;
    ++state->count;
    return result;
}

const char * core_symbol_get(core_Symbols * state, core_Symbol sym) {
    assert(sym < state->count);
    return state->symbols[sym];
}


//// PEEK
char core_peek(FILE * fp) {
    char ch = fgetc(fp);
    ungetc(fp);
    return ch;
}

void core_skip_whitespace(FILE * fp) {
    while(isspace(core_peek(fp))) (void)fgetc(fp);
}

#endif /*CORE_IMPLEMENTATION*/

#ifdef CORE_STRIP_PREFIX
#   define NORETURN        core_NORETURN
#   define NODISCARD       core_NODISCARD
#   define LOG             core_LOG
#   define UNREACHABLE     core_UNREACHABLE
#   define TODO            core_TODO
#   define profiler_init   core_profiler_init
#   define profiler_deinit core_profiler_deinit
#   define profiler_start  core_profiler_start
#   define profiler_stop   core_profiler_stop
#   define Arena           core_Arena
#   define arena_alloc     core_arena_alloc
#   define arena_free      core_arena_free
#   define Vec             core_Vec
#   define vec_append      core_vec_append
#   define isidentifier    core_isidentifier
#   define peek            core_peek
#   define skip_whitespace core_skip_whitespace 
#   define Symbol          core_Symbol
#   define Symbols         core_Symbols
#   define symbol_intern   core_symbol_intern
#   define symbol_get      core_symbol_get
#endif /*CORE_STRIP_PREFIX*/

#endif /*_CORE_H_*/
