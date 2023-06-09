#include <stdio.h>
#include <string.h>
#include <injector.h>

int main() {
    injector_t *injector;
    // int pid = get_pid("Terraria");

    void *target = (void *)0x7f8ba20a8000;
    int value = 101;
    memcpy(target, &value, sizeof(int));
}
