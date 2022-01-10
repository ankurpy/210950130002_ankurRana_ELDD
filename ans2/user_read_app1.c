#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


int main ( ) {
        int i,fd;
        char read_buf[100];

        fd = open("/dev/mysemdev", O_RDONLY);

        if (fd == -1)
        {
                printf("Error in opening file \n");
                exit(-1);
        }

        read(fd, read_buf, sizeof(read_buf));
        printf ("The data in the device is %s\n", read_buf);

        close(fd);
        
        return 0;
}
