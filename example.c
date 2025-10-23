#define CORE_IMPLEMENTATION
#include "core.h"

int main(void) {
    /*hashmap*/
    core_Hashmap(int) hm = {0};
    int result = 0;  

    CORE_DEFER(hashmap_cleanup) {
        core_hashmap_free(&hm);
    }
    core_hashmap_set(&hm, "foo", strlen("foo"), 1);
        
    assert(core_hashmap_get(&hm, "foo", strlen("foo"), &result));
    assert(result == 1);
    assert(!core_hashmap_get(&hm, "bar", strlen("bar"), &result));

    CORE_DEFERRED(hashmap_cleanup);

    return 0;
}
