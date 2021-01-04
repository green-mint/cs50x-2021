#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size, end_size, counter, pop_size;

    do {
        start_size = get_int("Input the start size: ");
    } while(start_size < 9);

    do {
        end_size = get_int("Input the end size: ");
    } while(end_size < start_size);

    counter = 0;
    pop_size = start_size;

    while(pop_size < end_size) {
        pop_size += (pop_size / 3) - (pop_size / 4);
        counter++;
    }
    /* Instead of using the while loop, you could 
     also directly calculate the counter(years) 
     using an exponetial function */
    printf("Years: %d\n",counter);
}
