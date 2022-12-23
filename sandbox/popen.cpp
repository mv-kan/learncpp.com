#include<iostream>
#define PATH_MAX 100
int main() {
    auto output = popen("pwd", "r");
    FILE *fp;
    int status;
    char path[PATH_MAX];


    fp = popen("ls *", "r");
    if (fp == NULL) {
        std::cout << "Error, unable to read output from popen()\n"; 
        exit(1);
    }


    while (fgets(path, PATH_MAX, fp) != NULL)
        printf("%s", path);


    status = pclose(fp);
    if (status == -1) {
        /* Error reported by pclose() */
        ...
    } else {
        /* Use macros described under wait() to inspect `status' in order
        to determine success/failure of command executed by popen() */
        ...
    }
    return 0;
}