#define core_STRIP_PREFIX
#define core_IMPLEMENTATION
#include "core.h"


int main() {
    defer(foo) {
        TODO("finish the example!");
    }

    LOG(ANSI_GREEN "Hello World!" ANSI_RESET);

    deferred(foo);
    return 0;
}
