#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main() {
    string text = get_string("Text: ");
    int l = count_letters(text);
    int w = count_words(text);
    int s = count_sentences(text);

    float L = ( (float) l / w) * 100;
    float S = ( (float) s / w) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index > 16) printf("Grade 16+\n");
    else if (index < 1) printf("Before Grade 1\n");
    else printf("Grade %.0f\n",index);
}

int count_letters(string text) {
    int count=0;
    int len = strlen(text);
    char c;

    for (int i=0; i<len; i++) {
        c = tolower(text[i]);
        if (c >= 'a' && c <= 'z') {
            count++;
        }
    }
    return count;
}

int count_words(string text) {
    int count=0;
    int len = strlen(text);

    for (int i=0; i<len; i++) {
        if (text[i] == ' ') {
            count++;
        }
    }
    count++;
    return count;
}

int count_sentences(string text) {
    int count=0;
    int len = strlen(text);
    
    for (int i=0; i<len; i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!' ) {
            count++;
        }
    }
    return count;
}