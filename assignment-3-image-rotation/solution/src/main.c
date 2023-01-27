#include "bmp.h"
#include "image.h"
#include "rotate.h"

#include <stdio.h>
#include <stdlib.h>
int main( int argc, char** argv ) {
    (void) argc; (void) argv; // supress 'unused parameters' warning
    if(argc == 3){
        FILE* input = fopen(argv[1],"r");
        FILE* output = fopen(argv[2],"w");
        struct image img = {0};
        if(from_bmp(input, &img) == READ_OK){
            struct image rotated_img = rotate(&img);
            if(to_bmp(output,&rotated_img) == WRITE_OK){
                fclose(input);
                fclose(output);
                free(img.data);
                free(rotated_img.data);
                return 0;
            }
            else{
                printf("Error writing! \n");
                fclose(output);
                return 1;
            }
        }
        return 0;
    }else{
        printf("Wrong argument \n");
        return 1;
    }
}
