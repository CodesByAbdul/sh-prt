#include "shell.h"

int main(void)
{
        pid_t process_id;
        process_id = getppid();

        printf("Parent Process ID: %u\n", process_id);
        return (0);
}
