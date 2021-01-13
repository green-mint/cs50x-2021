#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>
#include <math.h>

//gets the digit on index'th(1 to lenNum) place from the right of the number
int getDigit(long number, int index);
//caluclates the number of digits in a long
int lenLong(long number);
//does the checksum for validity of the card
bool checkSum(long card);


int main() {

    long card = get_long("Number: ");
    int card_len = lenLong(card);
    if (checkSum(card)) {
        //checking for the mastercard
        //checking for the length of the mastercard and the first digit
        if (card_len == 16 && getDigit(card,card_len) == 5) {
            //checking for the second digit of the master card
            if (getDigit(card,card_len-1) <= 5 && getDigit(card,card_len-1) >= 1) {
                printf("MASTERCARD\n");
                return 0;
            }
            else printf("INVALID\n");
        }
        //checking for the visa card
        //checking for the length of the visa card
        else if (card_len == 13 || card_len == 16) {
            //checking for the first digit of the visa card
            if (getDigit(card,card_len) == 4) {
                printf("VISA\n");
                return 0;
            }
            else printf("INVALID\n");
        }
        //checking for the american express card
        //checking for the length of the american express card and the first digit
        else if (card_len == 15 && getDigit(card,card_len) == 3) {
            //checking for the second digit of the american express card
            if ((getDigit(card,card_len-1) == 4 || getDigit(card,card_len-1) == 7)) {
                printf("AMEX\n");
                return 0;
            }
            else printf("INVALID\n");

        }
        //if it is neither of the cards, print invalid
        else printf("INVALID\n");
        
    }
    // if checksum doesnt pass, print invalid
    else printf("INVALID\n");
    return 0;
}


int getDigit(long number, int index) {
    int digit = (number / (long) pow(10,index-1)) % 10;
    return digit;
}

bool checkSum(long card) {
    int digit,result;
    int sum=0;

    for (int index=1,len=lenLong(card); index<=len ;index++) {
        digit = getDigit(card,index);
        // the digits on the even place(starting from the right of the number)
        if (index % 2 == 0) {
            //multiply the digit by two and calculate the result
            result = digit * 2;
            //loop through the digits of the result and add the digits to sum
            for (int i=1;i<=lenLong(result);i++) sum += getDigit(result,i);
        }
        // the digits on the odd places (starting from the right of the number)
        // just add the digit to the sum
        else sum += digit;
    }
    //check if the last digit of sum is 0 
    if (sum % 10 == 0) return 1;
    else return 0;

}

int lenLong(long number) {
    int len = 0;
    for (;number >= 1; number /= 10) {
        len++;
    }
    return len;
}