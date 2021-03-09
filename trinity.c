#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int main(int argc, char *argv[]) {
    double capital = 1000000;
    double withdrawal = 40000;
    double fees = 0.15;
    unsigned int duration = 30;

    // parse CLI args
    for (int i = 1; argc > 0 && i < argc; i++) {  
        if (strcmp(argv[i], "-c") == 0) {                 
            capital = atof(argv[i + 1]);
        } else if (strcmp(argv[i], "-w") == 0) {
            withdrawal = atof(argv[i + 1]);
        } else if(strcmp(argv[i], "-f") == 0) {
            fees = atof(argv[i + 1]);
        } else if(strcmp(argv[i], "-d") == 0) {
            duration = atoi(argv[i + 1]);
        }
    }
    printf("Capital: %.2f\n", capital);
    printf("Withdrawal: %.2f per month\n", withdrawal);
    printf("Fees: %.2f%% per year\n", fees);
    printf("Duration: %d years\n", duration);   

    // calculate returns (price change + dividends)
    rows[0].roi = 0.00;
    for (size_t i = 1; i < row_count; i++) {
        struct Row a = rows[i-1];
        struct Row b = rows[i];
        rows[i].roi = ((b.price - a.price) / a.price) +  (b.dividends / b.price / 12);
    }

    // run simulation
    withdrawal = withdrawal / 12.0;
    fees = fees / 100.0 / 12.0;
    duration = duration * 12;
    size_t successful_simulations = 0.00;
    unsigned int sample_count = row_count - duration;

    for (size_t i = 0; i < sample_count; i++) {
        double c = capital;

        for (size_t m = 0; m < duration; m++) {
            double inflation = rows[i + m].cpi / rows[i].cpi;
            double g = c * rows[i + m].roi;
            double w = withdrawal * inflation;
            double f = c * fees;
            c = c + g - f - w;
            if (c < 0.00) {
                break;
            }
        }

        if (c > 0.00) {
            successful_simulations++;
        }
    }

    double success_rate = (double) successful_simulations / sample_count;
    printf("Success ratio: %ld / %d (%.2f%%) \n", successful_simulations, sample_count, success_rate * 100);

    exit(EXIT_SUCCESS);
}