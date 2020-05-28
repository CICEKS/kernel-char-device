#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char **argv)
{
        if(argc < 2) {
                printf("device name should be entered\n");
                return -1;
        }

        char buffer[128];
        int st;

        int dev = open(argv[1], O_RDWR);
        if(dev < 0) {
                perror("filed to open char device");
                return errno;
        }

        printf("write to kernel device buffer : ");
        scanf("%s", buffer);

        st = write(dev, buffer, sizeof(buffer));
        if(st < 0) {
                perror("filed to write to char device");
                close(dev);
                return errno;
        }

        memset(buffer, '\0', 128);
        st = read(dev, buffer, 128);
        if(st < 0) {
                perror("failed to read from char device");
                close(dev);
                return errno;
        }
        printf("read from kernel device buffer : %s\n",buffer);
        return 0;
}
