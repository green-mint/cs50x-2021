#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main() {
    float dollars;
    int cents,coins=0;

    do {
        dollars = get_float("Change owed: ");
    } while(dollars < 0);

    cents = round(dollars * 100);
    
    for (;cents / 25 >= 1; cents -= 25) {
        coins++;
    }

    for (;cents / 10 >= 1; cents -= 10) {
        coins++;
    }

    for (;cents / 5 >= 1; cents -= 5) {
        coins++;
    }

    for (;cents / 1 >= 1; cents -= 1) {
        coins++;
    }

    printf("%d\n",coins);
}