#include <unistd.h>

#define BUFFER_SIZE 100

int main()
{
    char buf[BUFFER_SIZE];
    read(STDIN_FILENO, buf, BUFFER_SIZE);

    size_t last_char = 0;
    while (buf[last_char] != '\0')
        last_char++;

    size_t last_digit = 0;
    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        if (buf[last_char - i] >= 48 && buf[last_char - i] <= 57)
        {
            // swap
            last_digit = last_char - i;
            break;
        }
    }
    char minus = '-';
    if (buf[0] == '0') {
        write(STDOUT_FILENO, buf, 1);
    }
    else if (buf[0] == minus) {
        write(STDOUT_FILENO, buf + 1, last_digit + 1);
    } else {
        write(STDOUT_FILENO, &minus, 1);
        write(STDOUT_FILENO, buf, last_digit + 1);
    }
}
