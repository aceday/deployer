#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 8192
#define SRC_COLLATION "utf8mb4_0900_ai_ci"
#define TGT_COLLATION "utf8mb4_general_ci"

void replace_collation(const char *src, const char *dest) {
    FILE *infile = fopen(src, "r");
    FILE *outfile = fopen(dest, "w");

    if (!infile) {
        fprintf(stderr, "Error: File not found: %s\n", src);
        exit(1);
    }

    if (!outfile) {
        fprintf(stderr, "Error: Could not create output file: %s\n", dest);
        fclose(infile);
        exit(1);
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), infile)) {
        char *pos;
        while ((pos = strstr(line, SRC_COLLATION)) != NULL) {
            *pos = '\0';
            fprintf(outfile, "%s%s", line, TGT_COLLATION);
            memmove(line, pos + strlen(SRC_COLLATION), strlen(pos + strlen(SRC_COLLATION)) + 1);
        }
        fputs(line, outfile);
    }

    fclose(infile);
    fclose(outfile);
    printf("Conversion completed successfully. Output saved to: %s\n", dest);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source.sql> <dest.sql>\n", argv[0]);
        return 1;
    }

    replace_collation(argv[1], argv[2]);
    return 0;
}
