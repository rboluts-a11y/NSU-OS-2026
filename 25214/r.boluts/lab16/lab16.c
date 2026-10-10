#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
int main() {
    struct termios old_settings;
    struct termios new_settings;

    if (tcgetattr(STDIN_FILENO, &old_settings) == -1) {
        perror("tcgetattr");
        exit(1);
    }

    new_settings = old_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings) == -1) {
        perror("tcsetattr_change");
        exit(2);
    }

    char answer;

    printf("Enter a character: ");
    fflush(stdout);

    if (read(STDIN_FILENO,&answer,1) == -1) {
        perror("read");
        if (tcsetattr(STDIN_FILENO, TCSANOW, &old_settings) == -1) {
            perror("tcsetattr_restore");
            exit(3);
        }
        exit(4);
    }
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_settings) == -1) {
        perror("tcsetattr_restore");
        exit(5);
    }

    printf("\nYou answered: %c\n", answer);
    return 0;
}