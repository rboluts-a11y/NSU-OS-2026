#include <stdio.h>
#define MAX_MSG_SIZE 50
int main() {
    static char filename[] = "file.txt";
    static char command[MAX_MSG_SIZE];
    static char buffer[MAX_MSG_SIZE];
    sprintf(command, "grep \'^$\' %s", filename);
    FILE* fpin = popen(command, "r");
    FILE* fpout = popen("wc -l", "w");
    while (fgets(buffer, MAX_MSG_SIZE, fpin)) {
        fprintf(fpout, "%s", buffer);
    }
    pclose(fpin);
    pclose(fpout);
    return 0;
}