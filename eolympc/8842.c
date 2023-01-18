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
    for (size_t i = 0; i < BUF_SIZE; i++)
    {
        if (buf[last_char - i] >= 48 && buf[last_char - i] <= 57)
        {
            write(STDOUT_FILENO, &buf[last_char - i - 2], 1);
            return 0;
        }
    }
}