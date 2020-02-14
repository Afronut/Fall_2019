#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int MAXLINE=2000;

int read_in(int *f, char *buffer, int length);
int write_out(int *f, char *string);
void flush_input();

int main(int argc, char const *argv[])
{

    int fd = open("/dev/simple_character_device", O_RDWR);
    if (fd < 0){
        perror("Failed to open the device...\n");
        return -1;
    }

    char input;
    int bytes_to_read;
    char *bytes_to_write;
    int quit=0;
    while (!quit)
    {
        printf("Enter an option. h to print help menu\n");
        input=getchar();
        flush_input();
        switch (input)
        {
        case 'r'/* constant-expression */:
            printf("Please enter the number of bytes to read\n");
            scanf("%d", &bytes_to_read);
            flush_input();
            char *buffer_read=malloc(sizeof(char)*bytes_to_read);
            if (!buffer_read) perror("Memory allocation to store read bytes\n");
            printf("Reading %d bytes\n", bytes_to_read);
            int ret=read_in(&fd, buffer_read, bytes_to_read);
            if(ret <0) printf("Unable to read the requested bytes\n");
            printf("Device sends: [%s] \n", buffer_read);
            free(buffer_read);
            break;
        case 'w':
            printf("Please enter a text to write to device\n");
            bytes_to_write=malloc(sizeof(char)*MAXLINE);
            if (!bytes_to_write) perror("Memory allocation to user input bytes\n");
            scanf("%[^\n]%*c", bytes_to_write);
            ret=write_out(&fd,  bytes_to_write);
            if (ret <0) printf("Failed to write to device\n");
            printf("Wrote %d bytes to device\n", (int)ret);
            free(bytes_to_write);
            break;
        case 's':
            printf("Please enter the value of the OFFSET\n");
            int offset;
            scanf("%d", &offset);
            flush_input();
            printf("Please enter the value of WHENCE\n");
            int whence;
            scanf("%d", &whence);
            flush_input();
            ret=lseek(fd,offset,whence);
            if (ret<0){
                perror("Unable to set requested seek pos\n");
            }
            else
            {
                printf("Seek position is set\n");
            }
            break;
        case 'c':
            quit=1;
            break;
        case 'h':
            printf("-------------------\033[36mHelp Menu\e[0m------------------\n");
            printf("r -\033[31mRead from  device     \e[0m-- Required total bytes to read\n");
            printf("w -\033[31mWrite to device       \e[0m-- Required string to write\n");
            printf("s -\033[31mseek into device      \e[0m-- Required OFFSET and WHENCE\n");
            printf("c -\033[31mClose device and Quit\e[0m\n");
            break;
        default:
            printf("Invalid Option\n");
            break;
        }
    }
    close(fd);
    return 0;

}


void flush_input(){
    while ((getchar()) != '\n');

}


int write_out(int *f, char *string){
    int ret = write(*f, string, strlen(string));
    return ret;
    if (ret < 0){
      perror("Failed to write the message to the device.");
      return errno;
   }
}


int read_in(int *f, char *buffer, int length)
{
    int ret;
    ret = read(*f, buffer, length);
    if (ret<0){
        perror("Unable to read from device\n");
        printf("Return value is %d\n", ret);
        return -1 ;
    }
    return 0;
}