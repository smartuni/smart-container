#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

// int main(void)
// {
//     // char *line[0];
//     getchar();
//     // getline(,stdin);
//     // char buf[BUF_SIZE];

//     while(1) {
//         memset(buf, 0, sizeof(buf));  // Clear the buffer
//         puts("Waiting for input:");  // Print prompt

//         if (gets(buf) != NULL) {     // Get input
//             printf("Echo: %s\n", buf);  // Echo input
//         }
//     }

//     return 0;
// }

int main(void)
{
    // getchar();
    char buf[BUF_SIZE];

    while(1) {
        memset(buf, 0, sizeof(buf));  // Clear the buffer
        puts("Waiting for input:");  // Print prompt

        if (fgets(buf, sizeof(buf), stdin) != NULL) {  // Get input
            // Remove trailing newline character, if it exists
            if (buf[strlen(buf) - 1] == '\n') {
                buf[strlen(buf) - 1] = '\0';
            }

            printf("Echo: %s\n", buf);  // Echo input
        }
    }

    return 0;
}
