#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int seed = (int)time(NULL);
    srand(seed);
    int numbers[100];
    for (int i = 0; i < 100; i++) {
        numbers[i] = rand() & 0x7f;
        while (numbers[i] > 99) {
            numbers[i] = rand() & 0x7f;
        }
    }
    FILE* fp[2];
    if (p2open("sort -n", fp) == -1) {
        perror("sort");
        exit(1);
    }
    for (int i = 0; i < 100; i++) {
        if (fprintf(fp[0], "%d\n", numbers[i]) == -1) {
            perror("fprintf");
            p2close(fp);
            exit(2);
        }
    }
    if (fclose(fp[0]) == -1) {
        perror("fclose");
        exit(3);
    }
    int result[100];
    for (int i = 0; i < 100; i++) {
        if (fscanf(fp[1], "%d", &result[i]) == -1) {
            perror("fscanf");
            exit(4);
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", result[10 * i + j]);
        }
        printf("\n");
    }
    return 0;
}