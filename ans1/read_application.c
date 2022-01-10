#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buff[50];
    fd = open("/dev/mychardevice",O_RDONLY);
    printf("\n%d\n",fd);
    read(fd,buff,21);
    printf("\n%s\n",buff);
    close(fd);

    return 0;
}
