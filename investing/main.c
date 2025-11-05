#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "dependencies/Map.h"
#include "dependencies/List.h"


/*

valgrind --leak-check=full --show-leak-kinds=all ./ti

leaks -atExit -- ./ti test/wizards.jpg


*/

char* RESET = "\033[0m";
char* RED = "\033[252;3;3m";
char* YELLOW = "\033[252;186;3m";


int main(int argc, char **argv) {
    if (argc < 2 || argv[1] == NULL) {
        printf("%sPlease provide a single path to and image file you'd like to display%s", RED, RESET);
        exit(-1);
    }


    // get file path
    char* path;

    int info = 0;
    if (argc > 2) {
        char* flag = argv[1];
        info = strcmp(flag, "-i") == 0;
        path = argv[2];
    }
    else {
        path = argv[1];
    }


    return 0;
}
