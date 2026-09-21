#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Axis error: cannot open  file %s\n", filename);
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        fprintf(stderr, "Axis error: cannot seek file '%s'\n", filename);
        fclose(fp);
        return NULL;
    };

    long size = ftell(fp);

    if (size < 0)
    {
        fprintf(stderr, "Axis error: cannot determine file size \n");
        fclose(fp);
        return NULL;
    }

    rewind(fp);

    char *content = malloc(size + 1);

    if (content == NULL)
    {
        fprintf(stderr, "Axis error: out of memory\n");
        fclose(fp);
        return NULL;
    }

    size_t bytes_read = fread(content, 1, (size_t)size, fp);

    if (bytes_read != (size_t)size)
    {
        fprintf(stderr, "Axis error: failed to read file '%s'\n", filename);
        free(content);
        fclose(fp);
        return NULL;
    }

    content[bytes_read] = '\0';
    fclose(fp);
    return content;
}
