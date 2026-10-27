/* Include after core_Arena, core_arena_alloc, core_arena_strdup,
 * core_Sexpr, core_sexpr_parse, core_Hashmap and core_hashmap_get are declared.
 * Define CORE_IMPLEMENTATION in exactly one translation unit.
 * C99; supports 1-64 fields per struct.
 */
#ifndef CORE_META_H
#define CORE_META_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    const char *name;
    size_t offset;
    const char *type;
    size_t size;
    size_t count; /* 1 for scalar; N for array */
    size_t element_size;
    int is_array;
} core_FieldMeta;

/* Preprocessor utilities */
#define CORE_CONCAT_(a, b) a##b
#define CORE_CONCAT(a, b) CORE_CONCAT_(a, b)
#define CORE_STRINGIFY_(x) #x
#define CORE_STRINGIFY(x) CORE_STRINGIFY_(x)

/* Count 1-64 arguments. Empty lists are not supported. */
#define CORE_COUNT_( \
    a1, a2, a3, a4, a5, a6, a7, a8, \
    a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, \
    a25, a26, a27, a28, a29, a30, a31, a32, \
    a33, a34, a35, a36, a37, a38, a39, a40, \
    a41, a42, a43, a44, a45, a46, a47, a48, \
    a49, a50, a51, a52, a53, a54, a55, a56, \
    a57, a58, a59, a60, a61, a62, a63, a64, \
    n, ...) n

#define CORE_COUNT_EXPAND(...) CORE_COUNT_(__VA_ARGS__)
#define CORE_COUNT(...) CORE_COUNT_EXPAND( __VA_ARGS__, \
    64, 63, 62, 61, 60, 59, 58, 57, \
    56, 55, 54, 53, 52, 51, 50, 49, \
    48, 47, 46, 45, 44, 43, 42, 41, \
    40, 39, 38, 37, 36, 35, 34, 33, \
    32, 31, 30, 29, 28, 27, 26, 25, \
    24, 23, 22, 21, 20, 19, 18, 17, \
    16, 15, 14, 13, 12, 11, 10, 9, \
    8, 7, 6, 5, 4, 3, 2, 1, \
    0, 0)

/* FOR_EACH, supporting 1-64 fields */
#define CORE_FOREACH_1(m, ctx, a) \
    m(ctx, a)
#define CORE_FOREACH_2(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_1(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_3(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_2(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_4(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_3(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_5(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_4(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_6(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_5(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_7(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_6(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_8(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_7(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_9(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_8(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_10(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_9(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_11(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_10(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_12(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_11(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_13(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_12(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_14(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_13(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_15(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_14(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_16(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_15(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_17(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_16(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_18(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_17(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_19(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_18(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_20(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_19(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_21(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_20(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_22(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_21(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_23(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_22(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_24(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_23(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_25(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_24(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_26(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_25(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_27(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_26(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_28(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_27(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_29(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_28(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_30(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_29(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_31(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_30(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_32(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_31(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_33(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_32(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_34(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_33(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_35(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_34(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_36(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_35(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_37(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_36(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_38(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_37(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_39(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_38(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_40(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_39(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_41(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_40(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_42(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_41(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_43(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_42(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_44(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_43(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_45(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_44(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_46(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_45(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_47(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_46(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_48(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_47(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_49(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_48(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_50(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_49(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_51(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_50(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_52(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_51(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_53(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_52(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_54(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_53(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_55(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_54(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_56(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_55(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_57(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_56(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_58(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_57(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_59(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_58(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_60(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_59(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_61(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_60(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_62(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_61(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_63(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_62(m, ctx, __VA_ARGS__)
#define CORE_FOREACH_64(m, ctx, a, ...) \
    m(ctx, a) CORE_FOREACH_63(m, ctx, __VA_ARGS__)

#define CORE_FOREACH(m, ctx, ...) \
    CORE_CONCAT(CORE_FOREACH_, CORE_COUNT(__VA_ARGS__))(m, ctx, __VA_ARGS__)

/* Field declarations: (type, name) or (type, name, length) */
#define CORE_DECL_2(type, name) type name;
#define CORE_DECL_3(type, name, count) type name[count];
#define CORE_DECL_DISPATCH(n, pair) CORE_DECL_DISPATCH_(n, pair)
#define CORE_DECL_DISPATCH_(n, pair) CORE_CONCAT(CORE_DECL_, n) pair
#define CORE_DECL_FIELD(ctx, pair) \
    CORE_DECL_DISPATCH(CORE_COUNT pair, pair)

/* Tuple accessors */
#define CORE_TYPE_2(type, name) type
#define CORE_TYPE_3(type, name, count) type
#define CORE_NAME_2(type, name) name
#define CORE_NAME_3(type, name, count) name
#define CORE_EXTRACT(m, pair) CORE_EXTRACT_(m, CORE_COUNT pair, pair)
#define CORE_EXTRACT_(m, n, pair) CORE_EXTRACT_IMPL(m, n, pair)
#define CORE_EXTRACT_IMPL(m, n, pair) CORE_CONCAT(m, n) pair
#define CORE_GET_TYPE(pair) CORE_EXTRACT(CORE_TYPE_, pair)
#define CORE_GET_NAME(pair) CORE_EXTRACT(CORE_NAME_, pair)

#define CORE_FIELD_COUNT_2(type, name) 1
#define CORE_FIELD_COUNT_3(type, name, n) (n)
#define CORE_FIELD_ARRAY_2(type, name) 0
#define CORE_FIELD_ARRAY_3(type, name, n) 1
#define CORE_FIELD_COUNT(pair) CORE_EXTRACT(CORE_FIELD_COUNT_, pair)
#define CORE_FIELD_ARRAY(pair) CORE_EXTRACT(CORE_FIELD_ARRAY_, pair)

#define CORE_META_FIELD(ctx, pair) \
    { \
        .name = CORE_STRINGIFY(CORE_GET_NAME(pair)), \
        .offset = offsetof(ctx, CORE_GET_NAME(pair)), \
        .type = CORE_STRINGIFY(CORE_GET_TYPE(pair)), \
        .size = sizeof(((ctx *)0)->CORE_GET_NAME(pair)), \
        .count = CORE_FIELD_COUNT(pair), \
        .element_size = sizeof(((ctx *)0)->CORE_GET_NAME(pair)) / CORE_FIELD_COUNT(pair), \
        .is_array = CORE_FIELD_ARRAY(pair) \
    },

#define CORE_DEFSTRUCT(name, ...) \
    typedef struct { \
        CORE_FOREACH(CORE_DECL_FIELD, name, __VA_ARGS__) \
    } name; \
    static const core_FieldMeta name##_fields[] = { \
        CORE_FOREACH(CORE_META_FIELD, name, __VA_ARGS__) \
    }


#define CORE_FIELD_COUNT_OF(name) (sizeof(name##_fields)/sizeof(name##_fields[0]))
#define CORE_STRUCT_DESC(name) {#name, sizeof(name), name##_fields, CORE_FIELD_COUNT_OF(name)}

typedef struct {
    const char *name;
    size_t size;
    const core_FieldMeta *fields;
    size_t field_count;
} core_StructMeta;


/* The registry is the sole authority for supported types. */
typedef struct core_TypeRegistry core_TypeRegistry;
typedef int core_SerializeFn(core_Arena *, const void *, core_TypeRegistry *, core_Sexpr **);
typedef int core_DeserializeFn(core_Arena *, const core_Sexpr *, void *, core_TypeRegistry *);
typedef struct {
    core_SerializeFn *serialize;
    core_DeserializeFn *deserialize;
    const void *metadata;
    size_t size;
} core_TypeInfo;
struct core_TypeRegistry { core_Hashmap(core_TypeInfo) types; };

typedef struct { const char *name; long long value; } core_EnumEntry;
typedef struct {
    const char *name;
    size_t size;
    const core_EnumEntry *entries;
    size_t count;
    /* Generated enum values are represented as C int by default. */
} core_EnumMeta;
#define CORE_ENUM_DECL(ctx, item) item,
#define CORE_ENUM_ENTRY(ctx, item) {#item, (long long)(item)},
#define CORE_DEFENUM(name, ...) \
    typedef enum { CORE_FOREACH(CORE_ENUM_DECL, name, __VA_ARGS__) } name; \
    static const core_EnumEntry name##_enum_entries[] = { \
        CORE_FOREACH(CORE_ENUM_ENTRY, name, __VA_ARGS__) \
    }
#define CORE_ENUM_META(name) ((core_EnumMeta){#name, sizeof(name), \
    name##_enum_entries, sizeof(name##_enum_entries)/sizeof(name##_enum_entries[0])})
#define CORE_STRUCT_META(name) ((core_StructMeta)CORE_STRUCT_DESC(name))

int core_serialize(core_Arena *, const void *, const char *, core_TypeRegistry *, core_Sexpr **);
int core_deserialize(core_Arena *, const core_Sexpr *, void *, const char *, core_TypeRegistry *);
int core_serialize_string(core_Arena *, const void *, const char *, core_TypeRegistry *, char **);
int core_deserialize_string(core_Arena *, const char *, void *, const char *, core_TypeRegistry *);
core_TypeRegistry core_get_default_type_registry(core_Arena *);
int core_serialize_struct(core_Arena *, const void *, core_TypeRegistry *, core_Sexpr **);
int core_deserialize_struct(core_Arena *, const core_Sexpr *, void *, core_TypeRegistry *);
int core_serialize_enum(core_Arena *, const void *, core_TypeRegistry *, core_Sexpr **);
int core_deserialize_enum(core_Arena *, const core_Sexpr *, void *, core_TypeRegistry *);

/* Callbacks need metadata for their own type. Since the callback signature
 * has no type parameter, register structs/enums using the type-specific
 * wrappers generated below. Custom serializers may use arbitrary callbacks. */
#define CORE_DEFINE_STRUCT_CODEC(name) \
    static int name##_serialize(core_Arena *a, const void *v, core_TypeRegistry *r, core_Sexpr **out) { \
        core_StructMeta m = CORE_STRUCT_META(name); \
        return core_ds_struct_out(a, v, &m, r, out); \
    } \
    static int name##_deserialize(core_Arena *a, const core_Sexpr *s, void *v, core_TypeRegistry *r) { \
        core_StructMeta m = CORE_STRUCT_META(name); \
        return core_ds_struct_in(a, s, v, &m, r); \
    }
#define CORE_DEFINE_ENUM_CODEC(name) \
    static int name##_serialize(core_Arena *a, const void *v, core_TypeRegistry *r, core_Sexpr **out) { \
        core_EnumMeta m = CORE_ENUM_META(name); \
        return core_ds_enum_out(a, v, &m, r, out); \
    } \
    static int name##_deserialize(core_Arena *a, const core_Sexpr *s, void *v, core_TypeRegistry *r) { \
        core_EnumMeta m = CORE_ENUM_META(name); \
        return core_ds_enum_in(a, s, v, &m, r); \
    }
#define CORE_REGISTER_TYPE(reg, arena, name, info) \
    core_hashmap_set(&(reg)->types, (arena), (name), (info))
#define CORE_REGISTER_STRUCT(reg, arena, name) do { \
    core_TypeInfo info = {name##_serialize, name##_deserialize, name##_fields, sizeof(name)}; \
    CORE_REGISTER_TYPE(reg, arena, #name, info); \
} while (0)
#define CORE_REGISTER_ENUM(reg, arena, name) do { \
    core_TypeInfo info = {name##_serialize, name##_deserialize, name##_enum_entries, sizeof(name)}; \
    CORE_REGISTER_TYPE(reg, arena, #name, info); \
} while (0)

/* Helpers are public to allow the generated wrappers in other translation units. */
int core_ds_struct_out(core_Arena *, const void *, const core_StructMeta *, core_TypeRegistry *, core_Sexpr **);
int core_ds_struct_in(core_Arena *, const core_Sexpr *, void *, const core_StructMeta *, core_TypeRegistry *);
int core_ds_enum_out(core_Arena *, const void *, const core_EnumMeta *, core_TypeRegistry *, core_Sexpr **);
int core_ds_enum_in(core_Arena *, const core_Sexpr *, void *, const core_EnumMeta *, core_TypeRegistry *);

#ifdef CORE_IMPLEMENTATION
static core_Sexpr *core_ts_node(core_Arena *a) {
    core_Sexpr *s = core_arena_alloc(a, sizeof(*s));
    if (s) memset(s, 0, sizeof(*s));
    return s;
}
static core_Sexpr *core_ts_atom(core_Arena *a, const char *text) {
    core_Sexpr *s = core_ts_node(a);
    if (!s) return NULL;
    s->atom = core_arena_strdup(a, text);
    return s->atom ? s : NULL;
}
static int core_ts_append(core_Arena *a, core_Sexpr ***tail, core_Sexpr *value) {
    core_Sexpr *cell = core_ts_node(a);
    if (!cell) return 1;
    cell->car = value;
    **tail = cell;
    *tail = &cell->cdr;
    return 0;
}
int core_serialize(core_Arena *a, const void *v, const char *type, core_TypeRegistry *r, core_Sexpr **out) {
    core_TypeInfo *info;
    if (!a || !v || !type || !r || !out) return 1;
    *out = NULL;
    info = core_hashmap_get(&r->types, type);
    if (!info || !info->serialize) return 1;
    return info->serialize(a, v, r, out);
}
int core_deserialize(core_Arena *a, const core_Sexpr *s, void *v, const char *type, core_TypeRegistry *r) {
    core_TypeInfo *info;
    if (!a || !s || !v || !type || !r) return 1;
    info = core_hashmap_get(&r->types, type);
    if (!info || !info->deserialize) return 1;
    return info->deserialize(a, s, v, r);
}

/* Primitive codecs: C99 range checks and round-trippable floating formats. */
#define CORE_TS_SIGNED(type, tag, minval, maxval) \
static int core_ts_out_##tag(core_Arena *a, const void *v, core_TypeRegistry *r, core_Sexpr **out) { \
    char b[128]; (void)r; snprintf(b, sizeof(b), "%lld", (long long)*(const type *)v); \
    *out = core_ts_atom(a, b); return *out ? 0 : 1; \
} \
static int core_ts_in_##tag(core_Arena *a, const core_Sexpr *s, void *v, core_TypeRegistry *r) { \
    char *end; long long x; (void)a; (void)r; \
    if (!s || !s->atom || !*s->atom || isspace((unsigned char)*s->atom)) return 1; \
    errno=0; x=strtoll(s->atom,&end,10); \
    if (errno || *end || x < (long long)(minval) || x > (long long)(maxval)) return 1; \
    *(type *)v=(type)x; return 0; \
}
#define CORE_TS_UNSIGNED(type, tag, maxval) \
static int core_ts_out_##tag(core_Arena *a, const void *v, core_TypeRegistry *r, core_Sexpr **out) { \
    char b[128]; (void)r; snprintf(b, sizeof(b), "%llu", (unsigned long long)*(const type *)v); \
    *out=core_ts_atom(a,b); return *out ? 0 : 1; \
} \
static int core_ts_in_##tag(core_Arena *a, const core_Sexpr *s, void *v, core_TypeRegistry *r) { \
    char *end; unsigned long long x; (void)a; (void)r; \
    if (!s || !s->atom || !*s->atom || isspace((unsigned char)*s->atom) || *s->atom=='-') return 1; \
    errno=0; x=strtoull(s->atom,&end,10); \
    if (errno || *end || x > (unsigned long long)(maxval)) return 1; \
    *(type *)v=(type)x; return 0; \
}
CORE_TS_SIGNED(char, char, CHAR_MIN, CHAR_MAX)
CORE_TS_SIGNED(signed char, schar, SCHAR_MIN, SCHAR_MAX)
CORE_TS_UNSIGNED(unsigned char, uchar, UCHAR_MAX)
CORE_TS_SIGNED(short, short, SHRT_MIN, SHRT_MAX)
CORE_TS_UNSIGNED(unsigned short, ushort, USHRT_MAX)
CORE_TS_SIGNED(int, int, INT_MIN, INT_MAX)
CORE_TS_UNSIGNED(unsigned int, uint, UINT_MAX)
CORE_TS_SIGNED(long, long, LONG_MIN, LONG_MAX)
CORE_TS_UNSIGNED(unsigned long, ulong, ULONG_MAX)
CORE_TS_SIGNED(long long, llong, LLONG_MIN, LLONG_MAX)
CORE_TS_UNSIGNED(unsigned long long, ullong, ULLONG_MAX)
#define CORE_TS_FLOAT(type, tag, precision, limit) \
static int core_ts_out_##tag(core_Arena *a, const void *v, core_TypeRegistry *r, core_Sexpr **out) { \
    char b[128]; type x=*(const type *)v; (void)r; \
    if (!isfinite(x)) return 1; \
    snprintf(b,sizeof(b),"%.*g",(precision),(double)x); \
    *out=core_ts_atom(a,b); return *out ? 0 : 1; \
} \
static int core_ts_in_##tag(core_Arena *a, const core_Sexpr *s, void *v, core_TypeRegistry *r) { \
    char *end; double x; (void)a; (void)r; \
    if (!s || !s->atom || !*s->atom || isspace((unsigned char)*s->atom)) return 1; \
    errno=0; x=strtod(s->atom,&end); \
    if (errno || *end || !isfinite(x) || x > (limit) || x < -(limit)) return 1; \
    *(type *)v=(type)x; return 0; \
}
CORE_TS_FLOAT(float, float, FLT_DIG + 3, FLT_MAX)
CORE_TS_FLOAT(double, double, DBL_DIG + 3, DBL_MAX)
static int core_ts_out_bool(core_Arena *a, const void *v, core_TypeRegistry *r, core_Sexpr **out) {
    (void)r; *out=core_ts_atom(a, *(const _Bool *)v ? "true" : "false"); return *out ? 0 : 1;
}
static int core_ts_in_bool(core_Arena *a, const core_Sexpr *s, void *v, core_TypeRegistry *r) {
    (void)a; (void)r;
    if (!s || !s->atom) return 1;
    if (!strcmp(s->atom,"true")) *( _Bool *)v=1;
    else if (!strcmp(s->atom,"false")) *(_Bool *)v=0;
    else return 1;
    return 0;
}
#define CORE_TS_ADD(reg,a,name,tag,type) do { \
    core_TypeInfo info = {core_ts_out_##tag, core_ts_in_##tag, NULL, sizeof(type)}; \
    CORE_REGISTER_TYPE(reg,a,name,info); \
} while (0)
core_TypeRegistry core_get_default_type_registry(core_Arena *a) {
    core_TypeRegistry r = {0};
    CORE_TS_ADD(&r,a,"char",char,char);
    CORE_TS_ADD(&r,a,"signed char",schar,signed char);
    CORE_TS_ADD(&r,a,"unsigned char",uchar,unsigned char);
    CORE_TS_ADD(&r,a,"short",short,short);
    CORE_TS_ADD(&r,a,"unsigned short",ushort,unsigned short);
    CORE_TS_ADD(&r,a,"int",int,int);
    CORE_TS_ADD(&r,a,"unsigned int",uint,unsigned int);
    CORE_TS_ADD(&r,a,"long",long,long);
    CORE_TS_ADD(&r,a,"unsigned long",ulong,unsigned long);
    CORE_TS_ADD(&r,a,"long long",llong,long long);
    CORE_TS_ADD(&r,a,"unsigned long long",ullong,unsigned long long);
    CORE_TS_ADD(&r,a,"float",float,float);
    CORE_TS_ADD(&r,a,"double",double,double);
    CORE_TS_ADD(&r,a,"bool",bool,_Bool);
    CORE_TS_ADD(&r,a,"_Bool",bool,_Bool);
    return r;
}
int core_ds_struct_out(core_Arena *a, const void *v, const core_StructMeta *m, core_TypeRegistry *r, core_Sexpr **out) {
    core_Sexpr *root=NULL, **tail=&root;
    size_t i,j;
    if (!a || !v || !m || !r || !out) return 1;
    *out=NULL;
    if (core_ts_append(a,&tail,core_ts_atom(a,m->name))) return 1;
    for (i=0;i<m->field_count;++i) {
        const core_FieldMeta *f=&m->fields[i];
        const char *base=(const char *)v+f->offset;
        core_Sexpr *pair=NULL, **pt=&pair, *item=NULL;
        if (!f->count || !f->element_size || f->count > f->size/f->element_size ||
            f->count*f->element_size!=f->size) return 1;
        if (core_ts_append(a,&pt,core_ts_atom(a,f->name))) return 1;
        if (f->is_array) {
            core_Sexpr **at=&item;
            for (j=0;j<f->count;++j) {
                core_Sexpr *element=NULL;
                if (core_serialize(a,base+j*f->element_size,f->type,r,&element) ||
                    core_ts_append(a,&at,element)) return 1;
            }
        } else if (core_serialize(a,base,f->type,r,&item)) return 1;
        if (core_ts_append(a,&pt,item) || core_ts_append(a,&tail,pair)) return 1;
    }
    *out=root; return 0;
}
int core_ds_struct_in(core_Arena *a, const core_Sexpr *s, void *v, const core_StructMeta *m, core_TypeRegistry *r) {
    const core_Sexpr *entry;
    size_t i,j;
    if (!a || !s || !v || !m || !r || s->atom || !s->car || !s->car->atom ||
        strcmp(s->car->atom,m->name)) return 1;
    entry=s->cdr;
    for (i=0;i<m->field_count;++i) {
        const core_FieldMeta *f=&m->fields[i];
        const core_Sexpr *pair,*item;
        char *base=(char *)v+f->offset;
        if (!entry || !(pair=entry->car) || pair->atom || !pair->car ||
            !pair->car->atom || strcmp(pair->car->atom,f->name) ||
            !pair->cdr || pair->cdr->cdr) return 1;
        item=pair->cdr->car;
        if (f->is_array) {
            const core_Sexpr *element=item;
            for (j=0;j<f->count;++j) {
                if (!element || core_deserialize(a,element->car,base+j*f->element_size,f->type,r)) return 1;
                element=element->cdr;
            }
            if (element) return 1;
        } else if (core_deserialize(a,item,base,f->type,r)) return 1;
        entry=entry->cdr;
    }
    return entry ? 1 : 0;
}
int core_ds_enum_out(core_Arena *a, const void *v, const core_EnumMeta *m, core_TypeRegistry *r, core_Sexpr **out) {
    size_t i; int value;
    (void)r;
    if (!a || !v || !m || !out || m->size!=sizeof(int)) return 1;
    memcpy(&value,v,sizeof(value));
    for (i=0;i<m->count;++i) if (m->entries[i].value==value) {
        *out=core_ts_atom(a,m->entries[i].name); return *out ? 0 : 1;
    }
    return 1;
}
int core_ds_enum_in(core_Arena *a, const core_Sexpr *s, void *v, const core_EnumMeta *m, core_TypeRegistry *r) {
    size_t i; (void)a; (void)r;
    if (!s || !s->atom || !v || !m || m->size!=sizeof(int)) return 1;
    for (i=0;i<m->count;++i) if (!strcmp(s->atom,m->entries[i].name)) {
        int value;
        if (m->entries[i].value<INT_MIN || m->entries[i].value>INT_MAX) return 1;
        value=(int)m->entries[i].value; memcpy(v,&value,sizeof(value)); return 0;
    }
    return 1;
}
/* Arena-backed S-expression printer. */
static int core_ts_measure(const core_Sexpr *s, size_t *out) {
    size_t n=2,k;
    const core_Sexpr *p;
    if (!s) { *out=2; return 0; }
    if (s->atom) { *out=strlen(s->atom); return 0; }
    for (p=s;p;p=p->cdr) {
        if (core_ts_measure(p->car,&k) || k>SIZE_MAX-n) return 1;
        n+=k;
        if (p->cdr) { if (n==SIZE_MAX) return 1; ++n; }
    }
    *out=n; return 0;
}
static int core_ts_print(char *b, size_t cap, size_t *pos, const core_Sexpr *s) {
    const core_Sexpr *p;
    size_t n;
    if (!s) { if (cap-*pos<2) return 1; memcpy(b+*pos,"()",2); *pos+=2; return 0; }
    if (s->atom) {
        n=strlen(s->atom); if (n>cap-*pos) return 1;
        memcpy(b+*pos,s->atom,n); *pos+=n; return 0;
    }
    if (cap-*pos<1) return 1;
    b[(*pos)++]='(';
    for (p=s;p;p=p->cdr) {
        if (core_ts_print(b,cap,pos,p->car)) return 1;
        if (p->cdr) { if (cap-*pos<1) return 1; b[(*pos)++]=' '; }
    }
    if (cap-*pos<1) return 1;
    b[(*pos)++]=')';
    return 0;
}
int core_serialize_string(core_Arena *a, const void *v, const char *type, core_TypeRegistry *r, char **out) {
    core_Sexpr *s=NULL; size_t n,pos=0; char *b;
    if (!a || !out) return 1;
    *out=NULL;
    if (core_serialize(a,v,type,r,&s) || core_ts_measure(s,&n) || n==SIZE_MAX) return 1;
    b=core_arena_alloc(a,n+1); if (!b || core_ts_print(b,n,&pos,s)) return 1;
    b[pos]=0; *out=b; return 0;
}
int core_deserialize_string(core_Arena *a, const char *text, void *v, const char *type, core_TypeRegistry *r) {
    core_Sexpr *s; core_Stream stream;
    if (!a || !text || strlen(text)>INT_MAX) return 1;
    stream.ptr=text; stream.len=(int)strlen(text); stream.i=0;
    if (core_sexpr_parse_ex(a,&stream,&s) || !s) return 1;
    core_stream_skip_whitespace(&stream);
    if (!core_stream_eof(&stream)) return 1;
    return core_deserialize(a,s,v,type,r);
}
#endif /* CORE_IMPLEMENTATION */
#endif /* CORE_META_H */
