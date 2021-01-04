#include <cs50.h>
#include <stdio.h>

int main() {
    int height;
    do {
        height = get_int("Height: ");
    } while(height < 1 || height > 8);

    // looping through the rows, height times
    for (int i=1; i<=height; i++) {
        
        //calculating the whitespaces required in each row
        int whitespaces = height - i;
        for (int j=1; j <= whitespaces; j++) {
            printf(" ");
        }
        //hashes in each row are equal to the row number
        int hashes = i;
        for (int j=1; j<=hashes; j++) {
            printf("#");
        }
        printf("\n");
    }
}