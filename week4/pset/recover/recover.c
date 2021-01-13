#include <stdio.h>
#include <stdlib.h>
 
int check_arg_validity(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    if (!check_arg_validity(argc, argv)) return 1;

    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Unable to open file.\n");
        return 1; 
    }

    FILE *output;


    unsigned char *buffer = malloc(512);
    printf("%ld",sizeof(buffer));
    char *filename = malloc(8);
    int count=0;

    while(fread(buffer,512,1,input)) {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef) {
            if (count > 1) {
                fclose(output);
            }
            
            sprintf(filename,"%03d.jpg",count);
            output = fopen(filename,"w");

            if (output == NULL) {
                printf("Couldn't open output file\n");
                return 1;
            }
            count++;
        }

        if (count > 0) {
            fwrite(buffer,512,1,output);
        }
    
    }

    fclose(input);
    fclose(output);
    free(buffer);
    free(filename);
    return 0;

}

int check_arg_validity(int argc, char *argv[]__attribute__((unused))) {
    if (argc != 2) {
        return 0; // 0 meaning false or not valid
    }
    else return 1;
}