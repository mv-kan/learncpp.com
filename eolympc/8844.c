#include <unistd.h>
#define BUF_SIZE 100

int main()
{
    char buf[BUF_SIZE];
    read(STDIN_FILENO, buf, BUF_SIZE);
    size_t last_char = 0;
    for (size_t i = 0; i < BUF_SIZE; i++)
    {
        if (buf[i] == '\0')
        {
            last_char = i;
            break;
        }
    }
    size_t to_del = 0;
    for (size_t i = 0; i < BUF_SIZE; i++)
    {
        if (buf[last_char - i] >= 48 && buf[last_char - i] <= 57)
        {
            // swap
            to_del = last_char - i - 1;
            buf[to_del] =  buf[last_char - i];
            break;
        }
    }
    buf[to_del + 1] = '\0';
    // printf("%s", buf);
    write(STDOUT_FILENO, buf, to_del + 1);
}