#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define USER1 "/home/animesh/Desktop/SummerDev/cppchat/user1_FIFO"
#define USER2 "/home/animesh/Desktop/SummerDev/cppchat/user2_FIFO"

int main(){
    mkfifo(USER1, 0777);
    mkfifo(USER2, 0777);  
}