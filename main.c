#include <injector.h>
#include <stdio.h>

int main() {
    injector_t *injector;
    void *handle;

    if (injector_attach(&injector, 28930) != 0) {
        printf("ATTACH ERROR: %s\n", injector_error());
        return 0;
    }
}
