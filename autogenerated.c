typedef struct {
   int * ptr;
   int len;
} IntSlice;

IntSlice intslice_init(int * items, unsigned long count) {
    IntSlice result = {0};
    result.ptr = items;
    result.len = count;
    return result;
}

#define INTSLICE_FROM_ARRAY(array) intslice_init(array, (sizeof(array) / sizeof(array[0])))

typedef struct {
   short * ptr;
   int len;
} ShortSlice;

ShortSlice shortslice_init(short * items, unsigned long count) {
    ShortSlice result = {0};
    result.ptr = items;
    result.len = count;
    return result;
}

#define SHORTSLICE_FROM_ARRAY(array) shortslice_init(array, (sizeof(array) / sizeof(array[0])))

typedef struct {
   long * ptr;
   int len;
} LongSlice;

LongSlice longslice_init(long * items, unsigned long count) {
    LongSlice result = {0};
    result.ptr = items;
    result.len = count;
    return result;
}

#define LONGSLICE_FROM_ARRAY(array) longslice_init(array, (sizeof(array) / sizeof(array[0])))

typedef struct {
   char * ptr;
   int len;
} CharSlice;

CharSlice charslice_init(char * items, unsigned long count) {
    CharSlice result = {0};
    result.ptr = items;
    result.len = count;
    return result;
}

#define CHARSLICE_FROM_ARRAY(array) charslice_init(array, (sizeof(array) / sizeof(array[0])))

typedef struct {
   float * ptr;
   int len;
} FloatSlice;

FloatSlice floatslice_init(float * items, unsigned long count) {
    FloatSlice result = {0};
    result.ptr = items;
    result.len = count;
    return result;
}

#define FLOATSLICE_FROM_ARRAY(array) floatslice_init(array, (sizeof(array) / sizeof(array[0])))

typedef struct {
   double * ptr;
   int len;
} DoubleSlice;

DoubleSlice doubleslice_init(double * items, unsigned long count) {
    DoubleSlice result = {0};
    result.ptr = items;
    result.len = count;
    return result;
}

#define DOUBLESLICE_FROM_ARRAY(array) doubleslice_init(array, (sizeof(array) / sizeof(array[0])))

