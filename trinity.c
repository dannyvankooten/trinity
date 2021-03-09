#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include <stdarg.h>

int streq(char *haystack,  char *needle) { 
   return strcmp(haystack, needle) == 0;
}


double sim(double capital, double withdrawal, double fees, int duration) {
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

    double inflation, g, w, f, c;

    for (size_t i = 0; i < sample_count; i++) {
        c = capital;

        for (size_t m = 0; m < duration; m++) {
            inflation = rows[i + m].cpi / rows[i].cpi;
            g = c * rows[i + m].roi;
            w = withdrawal * inflation;
            f = c * fees;
            c = c + g - f - w;
            if (c < 0.00) {
                break;
            }
        }

        if (c > 0.00) {
            successful_simulations++;
        }
    }

    double success_rate = (double) successful_simulations / (double) sample_count;
    return success_rate;
}

int main(int argc, char *argv[]) {
    double capital = 1000000;
    double withdrawal = 40000;
    double fees = 0.15;
    unsigned int duration = 30;

    // parse CLI args
    for (int i = 1; argc > 0 && i < argc - 1; i++) {  
        if (streq(argv[1], "-c") || streq(argv[i], "-capital")) {
            capital = atof(argv[i + 1]);
        } else if (streq(argv[i], "-w") || streq(argv[i], "-withdrawal")) {
            withdrawal = atof(argv[i + 1]);
        } else if(streq(argv[i], "-f") || streq(argv[i], "-fees")) {
            fees = atof(argv[i + 1]);
        } else if(streq(argv[i], "-d") || streq(argv[i], "-duration")) {
            duration = atoi(argv[i + 1]);
        }

        i++;
    }

    // validate CLI args
    if (capital <= 0) {
        printf("Capital should be higher than zero.\n");
        exit(EXIT_FAILURE);
    }

    
    printf("Capital: $%.2f\n", capital);
    printf("Withdrawal: $%.2f per month\n", withdrawal);
    printf("Fees: %.2f%% per year\n", fees);
    printf("Duration: %d years\n", duration);   

    double success_rate = sim(capital, withdrawal, fees, duration);
    printf("Success ratio: %.2f%% \n", success_rate * 100);

    exit(EXIT_SUCCESS);
}
