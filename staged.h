#include "core.h"

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

