#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *content = malloc(size + 1);

    if (content == NULL) {
        fclose(fp);
        return NULL;
    }
    
    fread(content, 1, size, fp);
    content[size] = '\0';

    fclose(fp);
    return content;
}
