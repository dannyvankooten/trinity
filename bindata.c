#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    char date[20];
    float price;
    float dividends;
    float cpi;
    float roi;
};

char *trim(char *str) {
    for (size_t i=strlen(str) - 1; str[i] == '\n'; str[i--] = '\0');
    return str;
}

int main() {
    // read CSV file
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fin = fopen("data.csv", "r");
    if (!fin) return EXIT_FAILURE;

    FILE *fout = fopen("data.h", "w");
    if (!fout) return EXIT_FAILURE;

    // skip first line (CSV header)
    if (getline(&line, &len, fin) == -1) {
        exit(EXIT_FAILURE);
    }

    fputs(
        "struct Row {\n"
            "\tchar date[20];\n"
            "\tfloat price;\n"
            "\tfloat dividends;\n"
            "\tfloat cpi;\n"
            "\tfloat roi;\n"
        "};\n\n"
        "struct Row rows[] = {\n", fout);

    size_t row_count = 0;
    while ((read = getline(&line, &len, fin)) != -1) {
        char *date = strtok(line, ",");
        char *price = strtok(NULL, ",");
        char *dividends = strtok(NULL, ",");
        char *cpi = strtok(NULL, ",");

        if (cpi == NULL) {
            cpi = dividends;
            dividends = "0.00";
        }

        trim(cpi);
        fprintf(fout, "\t{ \"%s\", %s, %s, %s }, \n", date, price, dividends, cpi);

        row_count++;

    }
    fputs("};\n\n", fout);
    fprintf(fout, "#define row_count %ld\n", row_count);
    fclose(fin);
    fclose(fout);

}