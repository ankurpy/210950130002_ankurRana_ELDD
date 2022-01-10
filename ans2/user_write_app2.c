#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


int main ( ) 
{
        int i,fd;
        char write_buf[]="this is my buff";

        fd = open("/dev/mysemdev", O_WRONLY);

        if (fd == -1)
        {
                printf("Error in opening file \n");
                exit(-1);
        }


        write(fd, write_buf, sizeof(write_buf));

        close(fd);
        
        return 0;
}
