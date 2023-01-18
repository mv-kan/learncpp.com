#include <unistd.h>

#define BUFFER_SIZE 100

int main()
{
    char buff[BUFFER_SIZE];
    read(STDIN_FILENO, buff, BUFFER_SIZE);

    if (buff[0] == '0') {
        char zero = '0';
        write(STDOUT_FILENO, &zero, 1);
    }
    else if (buff[0] == '-') {
        int strlen = 0;
        while(buff[strlen] != '\n')
            strlen++;
        write(STDOUT_FILENO, buff + 1, strlen);
    } else {
        char minus = '-';
        write(STDOUT_FILENO, &minus, 1);

        int strlen = 0;
        while(buff[strlen] != '\n')
            strlen++;
        write(STDOUT_FILENO, buff, strlen);
    }

    
}
