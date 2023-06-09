#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <regex.h>
#include <injector.h>


int get_pid(const char *process_name) {
    DIR *dir;
    struct dirent *entry;
    char cmdline_path[128];
    char cmdline[256];
    int pid = -1;
    regex_t regex;

    if (regcomp(&regex, process_name, REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Failed to compile regex pattern\n");
        return -1;
    }

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir failed");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", entry->d_name);
            FILE *cmdline_file = fopen(cmdline_path, "r");
            if (cmdline_file) {
                if (fgets(cmdline, sizeof(cmdline), cmdline_file) != NULL) {
                    if (regexec(&regex, cmdline, 0, NULL, 0) == 0) {
                        pid = atoi(entry->d_name);
                        break;
                    }
                }
                fclose(cmdline_file);
            }
        }
    }

    closedir(dir);
    regfree(&regex);

    return pid;
}


int main() {
    injector_t *injector;
    void *handle;
    int pid = get_pid("Terraria");

    if (injector_attach(&injector, pid) != 0) {
        printf("ATTACH ERROR: %s\n", injector_error());
        return 1;
    } else
        printf("PID found: %d!\n", pid);

    void *target = (void *)0x57037cab;
    int value = 101;
    memcpy(target, &value, sizeof(int));

    if(injector_detach(injector) != 0) {
        printf("Failed to detach DLL from the target process\n");
        return 1;
    }
}
