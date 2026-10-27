#ifdef CORE_C99
#include <stddef.h>
#include <errno.h>

typedef struct {
    const char * name;
    int offset;
    const char * type;
    int size;
    int count;
    int element_size;
    core_Bool is_array;
} core_FieldMeta;

#define CORE_STRINGIFY_(x) #x
#define CORE_STRINGIFY(x) CORE_STRINGIFY_(x)

/* Count 1-64 arguments. Empty lists are not supported. */
#define CORE_TYPE_COUNT_( \
    a1, a2, a3, a4, a5, a6, a7, a8, \
    a9, a10, a11, a12, a13, a14, a15, a16, \
    a17, a18, a19, a20, a21, a22, a23, a24, \
    a25, a26, a27, a28, a29, a30, a31, a32, \
    a33, a34, a35, a36, a37, a38, a39, a40, \
    a41, a42, a43, a44, a45, a46, a47, a48, \
    a49, a50, a51, a52, a53, a54, a55, a56, \
    a57, a58, a59, a60, a61, a62, a63, a64, \
    n, ...) n

#define CORE_TYPE_COUNT_EXPAND(...) CORE_TYPE_COUNT_(__VA_ARGS__)
#define CORE_TYPE_COUNT(...) CORE_TYPE_COUNT_EXPAND( __VA_ARGS__, \
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
#define CORE_TYPE_FOREACH_1(m, ctx, a) \
    m(ctx, a)
#define CORE_TYPE_FOREACH_2(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_1(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_3(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_2(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_4(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_3(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_5(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_4(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_6(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_5(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_7(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_6(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_8(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_7(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_9(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_8(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_10(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_9(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_11(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_10(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_12(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_11(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_13(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_12(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_14(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_13(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_15(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_14(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_16(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_15(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_17(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_16(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_18(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_17(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_19(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_18(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_20(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_19(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_21(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_20(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_22(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_21(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_23(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_22(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_24(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_23(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_25(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_24(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_26(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_25(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_27(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_26(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_28(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_27(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_29(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_28(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_30(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_29(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_31(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_30(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_32(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_31(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_33(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_32(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_34(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_33(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_35(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_34(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_36(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_35(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_37(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_36(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_38(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_37(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_39(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_38(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_40(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_39(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_41(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_40(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_42(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_41(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_43(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_42(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_44(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_43(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_45(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_44(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_46(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_45(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_47(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_46(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_48(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_47(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_49(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_48(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_50(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_49(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_51(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_50(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_52(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_51(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_53(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_52(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_54(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_53(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_55(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_54(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_56(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_55(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_57(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_56(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_58(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_57(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_59(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_58(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_60(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_59(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_61(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_60(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_62(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_61(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_63(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_62(m, ctx, __VA_ARGS__)
#define CORE_TYPE_FOREACH_64(m, ctx, a, ...) \
    m(ctx, a) CORE_TYPE_FOREACH_63(m, ctx, __VA_ARGS__)

#define CORE_TYPE_FOREACH(m, ctx, ...) \
    CORE_CONCAT(CORE_TYPE_FOREACH_, CORE_TYPE_COUNT(__VA_ARGS__))(m, ctx, __VA_ARGS__)

/* Field declarations: (type, name) or (type, name, length) */
#define CORE_TYPE_DECL_2(type, name) type name;
#define CORE_TYPE_DECL_3(type, name, count) type name[count];
#define CORE_TYPE_DECL_DISPATCH(n, pair) CORE_TYPE_DECL_DISPATCH_(n, pair)
#define CORE_TYPE_DECL_DISPATCH_(n, pair) CORE_CONCAT(CORE_TYPE_DECL_, n) pair
#define CORE_TYPE_DECL_FIELD(ctx, pair) \
    CORE_TYPE_DECL_DISPATCH(CORE_TYPE_COUNT pair, pair)

/* Tuple accessors */
#define CORE_TYPE_FIELD_TYPE_2(type, name) type
#define CORE_TYPE_FIELD_TYPE_3(type, name, count) type
#define CORE_TYPE_FIELD_NAME_2(type, name) name
#define CORE_TYPE_FIELD_NAME_3(type, name, count) name
#define CORE_TYPE_EXTRACT(m, pair) CORE_TYPE_EXTRACT_(m, CORE_TYPE_COUNT pair, pair)
#define CORE_TYPE_EXTRACT_(m, n, pair) CORE_TYPE_EXTRACT_IMPL(m, n, pair)
#define CORE_TYPE_EXTRACT_IMPL(m, n, pair) CORE_CONCAT(m, n) pair
#define CORE_TYPE_GET_TYPE(pair) CORE_TYPE_EXTRACT(CORE_TYPE_FIELD_TYPE_, pair)
#define CORE_TYPE_GET_NAME(pair) CORE_TYPE_EXTRACT(CORE_TYPE_FIELD_NAME_, pair)

#define CORE_TYPE_FIELD_COUNT_2(type, name) 1
#define CORE_TYPE_FIELD_COUNT_3(type, name, n) (n)
#define CORE_TYPE_FIELD_ARRAY_2(type, name) 0
#define CORE_TYPE_FIELD_ARRAY_3(type, name, n) 1
#define CORE_TYPE_FIELD_COUNT(pair) CORE_TYPE_EXTRACT(CORE_TYPE_FIELD_COUNT_, pair)
#define CORE_TYPE_FIELD_ARRAY(pair) CORE_TYPE_EXTRACT(CORE_TYPE_FIELD_ARRAY_, pair)

#define CORE_TYPE_META_FIELD(ctx, pair) \
    { \
        .name = CORE_STRINGIFY(CORE_TYPE_GET_NAME(pair)), \
        .offset = (int)offsetof(ctx, CORE_TYPE_GET_NAME(pair)), \
        .type = CORE_STRINGIFY(CORE_TYPE_GET_TYPE(pair)), \
        .size = (int)sizeof(((ctx *)0)->CORE_TYPE_GET_NAME(pair)), \
        .count = CORE_TYPE_FIELD_COUNT(pair), \
        .element_size = (int)sizeof(((ctx *)0)->CORE_TYPE_GET_NAME(pair)) / CORE_TYPE_FIELD_COUNT(pair), \
        .is_array = CORE_TYPE_FIELD_ARRAY(pair) \
    },

#define CORE_DEFSTRUCT(name, ...) \
    typedef struct { \
        CORE_TYPE_FOREACH(CORE_TYPE_DECL_FIELD, name, __VA_ARGS__) \
    } name; \
    static const core_FieldMeta name##_fields[] = { \
        CORE_TYPE_FOREACH(CORE_TYPE_META_FIELD, name, __VA_ARGS__) \
    }


#define CORE_TYPE_FIELD_COUNT_OF(name) CORE_ARRAY_LEN(name##_fields)
#define CORE_STRUCT_DESC(name) {#name, (int)sizeof(name), name##_fields, CORE_TYPE_FIELD_COUNT_OF(name)}


/**** TYPE REGISTRY ****/
typedef struct {
    const char * name;
    int size;
    const core_FieldMeta * fields;
    int field_count;
} core_StructMeta;

typedef struct {
    const char * name;
    long long value;
} core_EnumEntry;

typedef struct {
    const char * name;
    int size;
    const core_EnumEntry * entries;
    int count;
} core_EnumMeta;

#define CORE_TYPE_ENUM_DECL(ctx, item) item,
#define CORE_TYPE_ENUM_ENTRY(ctx, item) {#item, (long long)(item)},

#define CORE_DEFENUM(name, ...) \
    typedef enum { \
        CORE_TYPE_FOREACH(CORE_TYPE_ENUM_DECL, name, __VA_ARGS__) \
    } name; \
    static const core_EnumEntry name##_enum_entries[] = { \
        CORE_TYPE_FOREACH(CORE_TYPE_ENUM_ENTRY, name, __VA_ARGS__) \
    }

#define CORE_STRUCT_META(name) \
    ((core_StructMeta)CORE_STRUCT_DESC(name))

#define CORE_ENUM_META(name) \
    ((core_EnumMeta){ \
        #name, \
        (int)sizeof(name), \
        name##_enum_entries, \
        CORE_ARRAY_LEN(name##_enum_entries) \
    })

typedef struct core_TypeRegistry core_TypeRegistry;

typedef int core_SerializeFn(
    core_Arena * arena,
    const void * value,
    core_TypeRegistry * registry,
    core_Sexpr ** out
);

typedef int core_DeserializeFn(
    core_Arena * arena,
    const core_Sexpr * sexpr,
    void * value,
    core_TypeRegistry * registry
);

typedef struct {
    core_SerializeFn * serialize;
    core_DeserializeFn * deserialize;
    const void * metadata;
    int size;
} core_TypeInfo;

struct core_TypeRegistry {
    core_Hashmap(core_TypeInfo) types;
};

#define CORE_REGISTER_TYPE(registry, arena, name, info) \
    core_hashmap_set(&(registry)->types, arena, name, info)

#define CORE_REGISTER_STRUCT(registry, arena, name) do { \
    core_TypeInfo info = {0}; \
    info.serialize = name##_serialize; \
    info.deserialize = name##_deserialize; \
    info.metadata = name##_fields; \
    info.size = (int)sizeof(name); \
    CORE_REGISTER_TYPE(registry, arena, #name, info); \
} while (0)

#define CORE_REGISTER_ENUM(registry, arena, name) do { \
    core_TypeInfo info = {0}; \
    info.serialize = name##_serialize; \
    info.deserialize = name##_deserialize; \
    info.metadata = name##_enum_entries; \
    info.size = (int)sizeof(name); \
    CORE_REGISTER_TYPE(registry, arena, #name, info); \
} while (0)

int core_ds_struct_out(
    core_Arena * arena,
    const void * value,
    const core_StructMeta * meta,
    core_TypeRegistry * registry,
    core_Sexpr ** out
);

int core_ds_struct_in(
    core_Arena * arena,
    const core_Sexpr * sexpr,
    void * value,
    const core_StructMeta * meta,
    core_TypeRegistry * registry
);

int core_ds_enum_out(
    core_Arena * arena,
    const void * value,
    const core_EnumMeta * meta,
    core_TypeRegistry * registry,
    core_Sexpr ** out
);

int core_ds_enum_in(
    core_Arena * arena,
    const core_Sexpr * sexpr,
    void * value,
    const core_EnumMeta * meta,
    core_TypeRegistry * registry
);

/* Generated wrappers have their own metadata and can be defined in any TU. */
#define CORE_DEFINE_STRUCT_CODEC(name) \
    static int name##_serialize( \
        core_Arena * arena, \
        const void * value, \
        core_TypeRegistry * registry, \
        core_Sexpr ** out \
    ) { \
        core_StructMeta meta = CORE_STRUCT_META(name); \
        return core_ds_struct_out( \
            arena, value, &meta, registry, out \
        ); \
    } \
    static int name##_deserialize( \
        core_Arena * arena, \
        const core_Sexpr * sexpr, \
        void * value, \
        core_TypeRegistry * registry \
    ) { \
        core_StructMeta meta = CORE_STRUCT_META(name); \
        return core_ds_struct_in( \
            arena, sexpr, value, &meta, registry \
        ); \
    }

#define CORE_DEFINE_ENUM_CODEC(name) \
    static int name##_serialize( \
        core_Arena * arena, \
        const void * value, \
        core_TypeRegistry * registry, \
        core_Sexpr ** out \
    ) { \
        core_EnumMeta meta = CORE_ENUM_META(name); \
        return core_ds_enum_out( \
            arena, value, &meta, registry, out \
        ); \
    } \
    static int name##_deserialize( \
        core_Arena * arena, \
        const core_Sexpr * sexpr, \
        void * value, \
        core_TypeRegistry * registry \
    ) { \
        core_EnumMeta meta = CORE_ENUM_META(name); \
        return core_ds_enum_in( \
            arena, sexpr, value, &meta, registry \
        ); \
    }

/**** S-EXPRESSION HELPERS ****/
core_Sexpr * _core_type_node(core_Arena * arena)
#ifdef CORE_IMPLEMENTATION
{
    core_Sexpr * result;

    result = core_arena_alloc(arena, sizeof(*result));
    if(!result) return NULL;

    memset(result, 0, sizeof(*result));
    return result;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

core_Sexpr * _core_type_atom(core_Arena * arena, const char * text)
#ifdef CORE_IMPLEMENTATION
{
    core_Sexpr * result;

    result = _core_type_node(arena);
    if(!result) return NULL;

    result->atom = core_arena_strdup(arena, text);
    if(!result->atom) return NULL;

    return result;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int _core_type_append(
    core_Arena * arena,
    core_Sexpr *** tail,
    core_Sexpr * value
)
#ifdef CORE_IMPLEMENTATION
{
    core_Sexpr * cell;

    cell = _core_type_node(arena);
    if(!cell) return 1;

    cell->car = value;
    **tail = cell;
    *tail = &cell->cdr;
    return 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

/**** SERIALIZATION ****/
int core_serialize(
    core_Arena * arena,
    const void * value,
    const char * type,
    core_TypeRegistry * registry,
    core_Sexpr ** out
)
#ifdef CORE_IMPLEMENTATION
{
    core_TypeInfo * info;

    if(!arena || !value || !type || !registry || !out) return 1;
    *out = NULL;

    info = core_hashmap_get(&registry->types, type);
    if(!info || !info->serialize) return 1;

    return info->serialize(arena, value, registry, out);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int core_deserialize(
    core_Arena * arena,
    const core_Sexpr * sexpr,
    void * value,
    const char * type,
    core_TypeRegistry * registry
)
#ifdef CORE_IMPLEMENTATION
{
    core_TypeInfo * info;

    if(!arena || !sexpr || !value || !type || !registry) return 1;

    info = core_hashmap_get(&registry->types, type);
    if(!info || !info->deserialize) return 1;

    return info->deserialize(arena, sexpr, value, registry);
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

/**** PRIMITIVE CODECS ****/
#define CORE_TYPE_SIGNED(type, tag, minimum, maximum) \
    int _core_type_out_##tag( \
        core_Arena * arena, \
        const void * value, \
        core_TypeRegistry * registry, \
        core_Sexpr ** out \
    ) \
    { \
        char buffer[128]; \
        (void)registry; \
        snprintf( \
            buffer, sizeof(buffer), "%lld", \
            (long long)*(const type *)value \
        ); \
        *out = _core_type_atom(arena, buffer); \
        return *out ? 0 : 1; \
    } \
    int _core_type_in_##tag( \
        core_Arena * arena, \
        const core_Sexpr * sexpr, \
        void * value, \
        core_TypeRegistry * registry \
    ) \
    { \
        char * end; \
        long long number; \
        (void)arena; \
        (void)registry; \
        if(!sexpr || !sexpr->atom) return 1; \
        if(!sexpr->atom[0]) return 1; \
        if(isspace((unsigned char)sexpr->atom[0])) return 1; \
        errno = 0; \
        number = strtoll(sexpr->atom, &end, 10); \
        if(errno || *end) return 1; \
        if(number < (long long)(minimum)) return 1; \
        if(number > (long long)(maximum)) return 1; \
        *(type *)value = (type)number; \
        return 0; \
    }

#define CORE_TYPE_UNSIGNED(type, tag, maximum) \
    int _core_type_out_##tag( \
        core_Arena * arena, \
        const void * value, \
        core_TypeRegistry * registry, \
        core_Sexpr ** out \
    ) \
    { \
        char buffer[128]; \
        (void)registry; \
        snprintf( \
            buffer, sizeof(buffer), "%llu", \
            (unsigned long long)*(const type *)value \
        ); \
        *out = _core_type_atom(arena, buffer); \
        return *out ? 0 : 1; \
    } \
    int _core_type_in_##tag( \
        core_Arena * arena, \
        const core_Sexpr * sexpr, \
        void * value, \
        core_TypeRegistry * registry \
    ) \
    { \
        char * end; \
        unsigned long long number; \
        (void)arena; \
        (void)registry; \
        if(!sexpr || !sexpr->atom) return 1; \
        if(!sexpr->atom[0]) return 1; \
        if(isspace((unsigned char)sexpr->atom[0])) return 1; \
        if(sexpr->atom[0] == '-') return 1; \
        errno = 0; \
        number = strtoull(sexpr->atom, &end, 10); \
        if(errno || *end) return 1; \
        if(number > (unsigned long long)(maximum)) return 1; \
        *(type *)value = (type)number; \
        return 0; \
    }

#define CORE_TYPE_FLOAT(type, tag, precision, maximum) \
    int _core_type_out_##tag( \
        core_Arena * arena, \
        const void * value, \
        core_TypeRegistry * registry, \
        core_Sexpr ** out \
    ) \
    { \
        char buffer[128]; \
        type number; \
        (void)registry; \
        number = *(const type *)value; \
        if(!isfinite(number)) return 1; \
        snprintf( \
            buffer, sizeof(buffer), "%.*g", \
            precision, (double)number \
        ); \
        *out = _core_type_atom(arena, buffer); \
        return *out ? 0 : 1; \
    } \
    int _core_type_in_##tag( \
        core_Arena * arena, \
        const core_Sexpr * sexpr, \
        void * value, \
        core_TypeRegistry * registry \
    ) \
    { \
        char * end; \
        double number; \
        (void)arena; \
        (void)registry; \
        if(!sexpr || !sexpr->atom) return 1; \
        if(!sexpr->atom[0]) return 1; \
        if(isspace((unsigned char)sexpr->atom[0])) return 1; \
        errno = 0; \
        number = strtod(sexpr->atom, &end); \
        if(errno || *end || !isfinite(number)) return 1; \
        if(number > maximum || number < -(maximum)) return 1; \
        *(type *)value = (type)number; \
        return 0; \
    }

#ifdef CORE_IMPLEMENTATION
CORE_TYPE_SIGNED(char, char, CHAR_MIN, CHAR_MAX)
CORE_TYPE_SIGNED(signed char, schar, SCHAR_MIN, SCHAR_MAX)
CORE_TYPE_UNSIGNED(unsigned char, uchar, UCHAR_MAX)
CORE_TYPE_SIGNED(short, short, SHRT_MIN, SHRT_MAX)
CORE_TYPE_UNSIGNED(unsigned short, ushort, USHRT_MAX)
CORE_TYPE_SIGNED(int, int, INT_MIN, INT_MAX)
CORE_TYPE_UNSIGNED(unsigned int, uint, UINT_MAX)
CORE_TYPE_SIGNED(long, long, LONG_MIN, LONG_MAX)
CORE_TYPE_UNSIGNED(unsigned long, ulong, ULONG_MAX)
CORE_TYPE_SIGNED(long long, llong, LLONG_MIN, LLONG_MAX)
CORE_TYPE_UNSIGNED(unsigned long long, ullong, ULLONG_MAX)
CORE_TYPE_FLOAT(float, float, FLT_DIG + 3, FLT_MAX)
CORE_TYPE_FLOAT(double, double, DBL_DIG + 3, DBL_MAX)

#else
#define CORE_TYPE_DECLARE(tag) \
    int _core_type_out_##tag( \
        core_Arena *, const void *, core_TypeRegistry *, core_Sexpr ** \
    ); \
    int _core_type_in_##tag( \
        core_Arena *, const core_Sexpr *, void *, core_TypeRegistry * \
    );
CORE_TYPE_DECLARE(char)
CORE_TYPE_DECLARE(schar)
CORE_TYPE_DECLARE(uchar)
CORE_TYPE_DECLARE(short)
CORE_TYPE_DECLARE(ushort)
CORE_TYPE_DECLARE(int)
CORE_TYPE_DECLARE(uint)
CORE_TYPE_DECLARE(long)
CORE_TYPE_DECLARE(ulong)
CORE_TYPE_DECLARE(llong)
CORE_TYPE_DECLARE(ullong)
CORE_TYPE_DECLARE(float)
CORE_TYPE_DECLARE(double)
#undef CORE_TYPE_DECLARE
#endif /*CORE_IMPLEMENTATION*/

int _core_type_out_bool(
    core_Arena * arena,
    const void * value,
    core_TypeRegistry * registry,
    core_Sexpr ** out
)
#ifdef CORE_IMPLEMENTATION
{
    (void)registry;
    *out = _core_type_atom(
        arena, *(const _Bool *)value ? "true" : "false"
    );
    return *out ? 0 : 1;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int _core_type_in_bool(
    core_Arena * arena,
    const core_Sexpr * sexpr,
    void * value,
    core_TypeRegistry * registry
)
#ifdef CORE_IMPLEMENTATION
{
    (void)arena;
    (void)registry;

    if(!sexpr || !sexpr->atom) return 1;

    if(strcmp(sexpr->atom, "true") == 0) {
        *(_Bool *)value = 1;
    } else if(strcmp(sexpr->atom, "false") == 0) {
        *(_Bool *)value = 0;
    } else {
        return 1;
    }

    return 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

#define CORE_TYPE_ADD(registry, arena, name, tag, type) do { \
    core_TypeInfo info = {0}; \
    info.serialize = _core_type_out_##tag; \
    info.deserialize = _core_type_in_##tag; \
    info.size = (int)sizeof(type); \
    CORE_REGISTER_TYPE(registry, arena, name, info); \
} while (0)

core_TypeRegistry core_get_default_type_registry(core_Arena * arena)
#ifdef CORE_IMPLEMENTATION
{
    core_TypeRegistry registry = {0};

    CORE_TYPE_ADD(&registry, arena, "char", char, char);
    CORE_TYPE_ADD(&registry, arena, "signed char", schar, signed char);
    CORE_TYPE_ADD(&registry, arena, "unsigned char", uchar, unsigned char);
    CORE_TYPE_ADD(&registry, arena, "short", short, short);
    CORE_TYPE_ADD(&registry, arena, "unsigned short", ushort, unsigned short);
    CORE_TYPE_ADD(&registry, arena, "int", int, int);
    CORE_TYPE_ADD(&registry, arena, "unsigned int", uint, unsigned int);
    CORE_TYPE_ADD(&registry, arena, "long", long, long);
    CORE_TYPE_ADD(&registry, arena, "unsigned long", ulong, unsigned long);
    CORE_TYPE_ADD(&registry, arena, "long long", llong, long long);
    CORE_TYPE_ADD(&registry, arena, "unsigned long long", ullong, unsigned long long);
    CORE_TYPE_ADD(&registry, arena, "float", float, float);
    CORE_TYPE_ADD(&registry, arena, "double", double, double);
    CORE_TYPE_ADD(&registry, arena, "bool", bool, _Bool);
    CORE_TYPE_ADD(&registry, arena, "_Bool", bool, _Bool);

    return registry;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

/**** STRUCT CODECS ****/
int core_ds_struct_out(
    core_Arena * arena,
    const void * value,
    const core_StructMeta * meta,
    core_TypeRegistry * registry,
    core_Sexpr ** out
)
#ifdef CORE_IMPLEMENTATION
{
    core_Sexpr * root = NULL;
    core_Sexpr ** tail = &root;
    int i;
    int j;

    if(!arena || !value || !meta || !registry || !out) return 1;
    *out = NULL;

    if(_core_type_append(
        arena, &tail, _core_type_atom(arena, meta->name)
    )) return 1;

    for(i = 0; i < meta->field_count; ++i) {
        const core_FieldMeta * field = &meta->fields[i];
        const char * base = (const char *)value + field->offset;
        core_Sexpr * pair = NULL;
        core_Sexpr ** pair_tail = &pair;
        core_Sexpr * item = NULL;

        if(field->count <= 0 || field->element_size <= 0) return 1;
        if(field->count > INT_MAX / field->element_size) return 1;
        if(field->count * field->element_size != field->size) return 1;

        if(_core_type_append(
            arena, &pair_tail, _core_type_atom(arena, field->name)
        )) return 1;

        if(field->is_array) {
            core_Sexpr ** item_tail = &item;

            for(j = 0; j < field->count; ++j) {
                core_Sexpr * element = NULL;
                const char * ptr = base + j * field->element_size;

                if(core_serialize(
                    arena, ptr, field->type, registry, &element
                )) return 1;

                if(_core_type_append(
                    arena, &item_tail, element
                )) return 1;
            }
        } else {
            if(core_serialize(
                arena, base, field->type, registry, &item
            )) return 1;
        }

        if(_core_type_append(arena, &pair_tail, item)) return 1;
        if(_core_type_append(arena, &tail, pair)) return 1;
    }

    *out = root;
    return 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int core_ds_struct_in(
    core_Arena * arena,
    const core_Sexpr * sexpr,
    void * value,
    const core_StructMeta * meta,
    core_TypeRegistry * registry
)
#ifdef CORE_IMPLEMENTATION
{
    const core_Sexpr * entry;
    int i;
    int j;

    if(!arena || !sexpr || !value || !meta || !registry) return 1;
    if(sexpr->atom || !sexpr->car) return 1;
    if(!sexpr->car->atom) return 1;
    if(strcmp(sexpr->car->atom, meta->name) != 0) return 1;

    entry = sexpr->cdr;

    for(i = 0; i < meta->field_count; ++i) {
        const core_FieldMeta * field = &meta->fields[i];
        const core_Sexpr * pair;
        const core_Sexpr * item;
        char * base = (char *)value + field->offset;

        if(!entry || !entry->car) return 1;
        pair = entry->car;
        if(pair->atom || !pair->car) return 1;
        if(!pair->car->atom) return 1;
        if(strcmp(pair->car->atom, field->name) != 0) return 1;
        if(!pair->cdr || pair->cdr->cdr) return 1;

        item = pair->cdr->car;

        if(field->is_array) {
            const core_Sexpr * element = item;

            for(j = 0; j < field->count; ++j) {
                char * ptr = base + j * field->element_size;

                if(!element) return 1;
                if(core_deserialize(
                    arena, element->car, ptr, field->type, registry
                )) return 1;

                element = element->cdr;
            }

            if(element) return 1;
        } else {
            if(core_deserialize(
                arena, item, base, field->type, registry
            )) return 1;
        }

        entry = entry->cdr;
    }

    return entry ? 1 : 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

/**** ENUM CODECS ****/
int core_ds_enum_out(
    core_Arena * arena,
    const void * value,
    const core_EnumMeta * meta,
    core_TypeRegistry * registry,
    core_Sexpr ** out
)
#ifdef CORE_IMPLEMENTATION
{
    int i;
    int number;

    (void)registry;
    if(!arena || !value || !meta || !out) return 1;
    if(meta->size != (int)sizeof(int)) return 1;

    memcpy(&number, value, sizeof(number));

    for(i = 0; i < meta->count; ++i) {
        if(meta->entries[i].value == number) {
            *out = _core_type_atom(arena, meta->entries[i].name);
            return *out ? 0 : 1;
        }
    }

    return 1;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int core_ds_enum_in(
    core_Arena * arena,
    const core_Sexpr * sexpr,
    void * value,
    const core_EnumMeta * meta,
    core_TypeRegistry * registry
)
#ifdef CORE_IMPLEMENTATION
{
    int i;
    int number;

    (void)arena;
    (void)registry;
    if(!sexpr || !sexpr->atom || !value || !meta) return 1;
    if(meta->size != (int)sizeof(int)) return 1;

    for(i = 0; i < meta->count; ++i) {
        if(strcmp(sexpr->atom, meta->entries[i].name) == 0) {
            if(meta->entries[i].value < INT_MIN) return 1;
            if(meta->entries[i].value > INT_MAX) return 1;

            number = (int)meta->entries[i].value;
            memcpy(value, &number, sizeof(number));
            return 0;
        }
    }

    return 1;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

/**** S-EXPRESSION STRING OUTPUT ****/
int _core_type_measure(const core_Sexpr * sexpr, int * out)
#ifdef CORE_IMPLEMENTATION
{
    const core_Sexpr * cell;
    int length = 2;
    int part;

    if(!sexpr) {
        *out = 2;
        return 0;
    }

    if(sexpr->atom) {
        if(strlen(sexpr->atom) > INT_MAX) return 1;
        *out = (int)strlen(sexpr->atom);
        return 0;
    }

    for(cell = sexpr; cell; cell = cell->cdr) {
        if(_core_type_measure(cell->car, &part)) return 1;
        if(part > INT_MAX - length) return 1;
        length += part;

        if(cell->cdr) {
            if(length == INT_MAX) return 1;
            ++length;
        }
    }

    *out = length;
    return 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int _core_type_print(
    char * buffer,
    int capacity,
    int * position,
    const core_Sexpr * sexpr
)
#ifdef CORE_IMPLEMENTATION
{
    const core_Sexpr * cell;
    int length;

    if(!sexpr) {
        if(capacity - *position < 2) return 1;
        memcpy(buffer + *position, "()", 2);
        *position += 2;
        return 0;
    }

    if(sexpr->atom) {
        if(strlen(sexpr->atom) > INT_MAX) return 1;
        length = (int)strlen(sexpr->atom);
        if(length > capacity - *position) return 1;

        memcpy(buffer + *position, sexpr->atom, length);
        *position += length;
        return 0;
    }

    if(capacity - *position < 1) return 1;
    buffer[(*position)++] = '(';

    for(cell = sexpr; cell; cell = cell->cdr) {
        if(_core_type_print(
            buffer, capacity, position, cell->car
        )) return 1;

        if(cell->cdr) {
            if(capacity - *position < 1) return 1;
            buffer[(*position)++] = ' ';
        }
    }

    if(capacity - *position < 1) return 1;
    buffer[(*position)++] = ')';
    return 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int core_serialize_string(
    core_Arena * arena,
    const void * value,
    const char * type,
    core_TypeRegistry * registry,
    char ** out
)
#ifdef CORE_IMPLEMENTATION
{
    core_Sexpr * sexpr = NULL;
    int length;
    int position = 0;
    char * buffer;

    if(!arena || !out) return 1;
    *out = NULL;

    if(core_serialize(
        arena, value, type, registry, &sexpr
    )) return 1;
    if(_core_type_measure(sexpr, &length)) return 1;
    if(length == INT_MAX) return 1;

    buffer = core_arena_alloc(arena, length + 1);
    if(!buffer) return 1;

    if(_core_type_print(
        buffer, length, &position, sexpr
    )) return 1;

    buffer[position] = 0;
    *out = buffer;
    return 0;
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

int core_deserialize_string(
    core_Arena * arena,
    const char * text,
    void * value,
    const char * type,
    core_TypeRegistry * registry
)
#ifdef CORE_IMPLEMENTATION
{
    core_Sexpr * sexpr = NULL;
    core_Stream stream = {0};

    if(!arena || !text) return 1;
    if(strlen(text) > INT_MAX) return 1;

    stream.ptr = text;
    stream.len = (int)strlen(text);
    stream.i = 0;

    if(core_sexpr_parse_ex(arena, &stream, &sexpr)) return 1;
    if(!sexpr) return 1;

    core_stream_skip_whitespace(&stream);
    if(!core_stream_eof(&stream)) return 1;

    return core_deserialize(
        arena, sexpr, value, type, registry
    );
}
#else
;
#endif /*CORE_IMPLEMENTATION*/

#endif /*CORE_C99*/
