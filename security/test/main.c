#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

int main(void)
{
    char buf[BUF_SIZE];
    int char_count = 0;

    while(1) {
        memset(buf, 0, sizeof(buf));  // Clear the buffer
        printf("Waiting for input:\n");  

        if (fgets(buf, sizeof(buf), stdin) != NULL) {  
            if (buf[strlen(buf) - 1] == '\n') {
                buf[strlen(buf) - 1] = '\0';
            }

            char_count += strlen(buf);
            printf("Received message: %s\n", buf);  
            printf("Total characters received so far: %d\n", char_count);
        }
    }

    return 0;
}
