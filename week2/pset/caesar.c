#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

int valid_cl_args(int argc, string argv[]);
int stoi(string s_number);

int main(int argc, string argv[]) {
    if (valid_cl_args(argc,argv)) {
        string plain = get_string("plaintext: ");
        int len = strlen(plain);

        int key = stoi(argv[1]) % 26;

        char cipher[len+1];

        for (int i=0; i<len; i++) {
            char c = plain[i];

            bool upper=false;
            if (isupper(c)) {
                c = tolower(c);
                upper = true;
            }

            if (c >= 'a' && c <= 'z') {
                c = (((c - 97) + key) % 26) + 97;
            }

            if (upper) {
                c = toupper(c);
            }
            cipher[i] = c;
        }
        cipher[len] = '\0';
        printf("ciphertext: %s\n",cipher);
    }
    else {
        printf("Usage: ./ceaser key\n");
        return 1;
    }
}

int valid_cl_args(int argc, string argv[]) {
    if (argc != 2) {
        return 0;
    }
    else {
        string key = argv[1];
        int len = strlen(key);
        for (int i=0; i<len; i++) {
            if (key[i] > '9' || key[i] < '0') {
                return 0;
            }
        }
    }
    return 1;
}

int stoi(string s_number) {
    int len = strlen(s_number);
    int i_number=0;

    for (int i=0; i<len; i++) {
        i_number += ( (int) s_number[i] - 48) * (int) pow(10,len - 1 - i);
    }
    return i_number;
}
