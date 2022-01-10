#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buff[]="this is my exam";
    fd = open("/dev/mychardevice",O_WRONLY);
    printf("\n%d\n",fd);
    write(fd,buff,21);
    close(fd);

    return 0;
}
