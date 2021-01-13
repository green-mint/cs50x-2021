#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

int valid_cl_args(int argc, string argv[]);

int main(int argc, string argv[]) {
    if (valid_cl_args(argc,argv)) {
        string plain = get_string("plaintext: ");
        int len = strlen(plain);

        string key = argv[1];
        char cipher[len+1];

        for (int i=0; i<len; i++) {
            char c = plain[i];

            bool upper=false;
            if (isupper(c)) {
                c = tolower(c);
                upper = true;
            }

            if (c >= 'a' && c <= 'z') {
                c = tolower(key[c - 97]);
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
        if (len != 26) {
            return 0;
        }
        else {
            for (int i=0; i<len; i++) {
                for (int j=0; j<len; j++) {
                    if (tolower(key[i]) == tolower(key[j]) && i != j) {
                        return 0;
                    }
                }
            }

            for (int i=0; i<len; i++) {
                if (tolower(key[i]) < 'a' || tolower(key[i]) > 'z') {
                    return 0;
                }
            }
        }

        
    }
    return 1;
}
