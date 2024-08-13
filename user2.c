#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

#define USER1 "/home/animesh/Desktop/SummerDev/cppchat/user1_FIFO"
#define USER2 "/home/animesh/Desktop/SummerDev/cppchat/user2_FIFO"

int main() {
    printf("Welcome User 2 :\n");
    int fd_u1 = open(USER1, O_RDONLY);
    int fd_u2 = open(USER2, O_WRONLY);
    
    fcntl(fd_u1, F_SETFL, O_NONBLOCK); // Set fd_u1 to non-blocking mode
    
    char msg[2048], read_msg[2048];
    fd_set readfds;
    
    while(1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds); // Monitor standard input (keyboard)
        FD_SET(fd_u1, &readfds); // Monitor the FIFO for User 1
        
        select(fd_u1 + 1, &readfds, NULL, NULL, NULL); // Wait for input
        
        if(FD_ISSET(STDIN_FILENO, &readfds)) {
            scanf("%s", msg);
            write(fd_u2, msg, strlen(msg) + 1);
        }
        
        if(FD_ISSET(fd_u1, &readfds)) {
            int bytes = read(fd_u1, read_msg, sizeof(read_msg));
            if (bytes > 0) {
                printf("User 1 : %s\n", read_msg);
            }
        }
    }
    close(fd_u1);
    close(fd_u2);
    return 0;
}
