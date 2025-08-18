#ifndef _CORE_H_
#define _CORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define core_NORETURN __attribute__((noreturn))

#define core_ON_EXIT_MAX_FUNCTIONS 64
void core_on_exit(void (*fn)(void *ctx), void * ctx);
core_NORETURN void core_exit(int exitcode);

#define core_LOG(...) do { fprintf(stderr, "%s:%d:0:   ", __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr); } while (0)
#define core_UNREACHABLE do { core_LOG("unreachable code block reached!"); core_exit(1); } while (0)
#define core_TODO(...) do { core_LOG("TODO" __VA_ARGS__); core_exit(1); } while (0)

typedef struct core_Allocation {
    struct core_Allocation * next;

    void * mem;
    size_t len;
    bool active;
} core_Allocation;

typedef struct {
    core_Allocation * head;
} core_Arena;

void * core_arena_alloc(core_Arena *, const size_t);
void core_arena_free(core_Arena *);

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


bool core_is_identifier_char(char ch);


/*===================IMPLEMENTATION===================*/
#ifdef CORE_IMPLEMENTATION

void (*core_on_exit_fns[core_ON_EXIT_MAX_FUNCTIONS])(void * ctx) = {0};
void * core_on_exit_ctx[core_ON_EXIT_MAX_FUNCTIONS] = {0}; 
int core_on_exit_fn_count = 0;

void core_on_exit(void (*fn)(void *ctx), void * ctx) {
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

#endif /*CORE_IMPLEMENTATION*/

#ifdef CORE_STRIP_PREFIX
#   define NORETURN    core_NORETURN
/*#   define on_exit     core_on_exit*/
/*#   define exit        core_exit*/
#   define LOG         core_LOG
#   define UNREACHABLE core_UNREACHABLE
#   define TODO        core_TODO
#   define Arena       core_Arena
#   define arena_alloc core_arena_alloc
#   define arena_free  core_arena_free
#   define Vec         core_Vec
#   define vec_append  core_vec_append
#endif /*CORE_STRIP_PREFIX*/

#endif /*_CORE_H_*/
