#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

struct Record {
    char date[20];
    float price;
    float dividends;
    float cpi;
    float roi;
};

int main() {
    // read CSV file
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("data.csv", "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    // skip first line
    if (getline(&line, &len, fp) == -1) {
        exit(EXIT_FAILURE);
    }

    size_t rows_size = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char *date = strtok(line, ",");
        char *price = strtok(NULL, ",");
        char *dividends = strtok(NULL, ",");
        char *cpi = strtok(NULL, ",");

        if (cpi == NULL) {
            cpi = dividends;
            dividends = "0.00";
        }

        size_t r = rows_size;
        strcpy(rows[r].date, date);
        rows[r].price = atof(price);
        rows[r].dividends = atof(dividends);
        rows[r].cpi = atof(cpi);
        rows_size++;

        // stop reading after 50.000 rows
        if (rows_size >= 50000) {
            break;
        }
    }
    fclose(fp);


    for (size_t i = 0; i < rows_size; i++) {
        printf("{ \"%s\", %.4f, %.4f, %.4f },\n", rows[i].date, rows[i].price, rows[i].dividends, rows[i].cpi);
    }
}