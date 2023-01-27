#include "bmp.h"
#include "image.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
static enum read_status read_header(FILE* input, struct bmp_header* header){
    if(fseek(input,0, SEEK_END) == 0){
        size_t header_size = ftell(input);
        if(header_size >= sizeof(struct bmp_header)){
            rewind(input);
            if(fread(header, sizeof(struct bmp_header), 1, input) == 1){
                return READ_OK;
            }
            else{
                return READ_FAIL;
            }
        }
        else{
            return READ_INVALID_HEADER;
        }
    }else{
        return READ_FAIL;
    }
}

enum read_status read_pixel(struct image* img, FILE* input, uint32_t padding){
    size_t height = img -> height;
    size_t width = img -> width;
    struct pixel* pixel = malloc(height * width*sizeof(struct pixel));
    for(size_t i=0; i<height; i++){
        fread(pixel+i*width, sizeof(struct pixel), width, input);
        fseek(input, padding, SEEK_CUR);

    }
    img->data = pixel;
    return READ_OK;
}

static uint32_t get_padding(uint32_t width){
    if(width % 4 != 0){
        return 4 - (width * 3) % 4;
    }
    else return 0;
}

enum read_status from_bmp(FILE* input, struct image *img){
    struct bmp_header header = {0};
    enum read_status status = read_header(input, &header);
    if(status == READ_OK){
        const uint32_t height = header.biHeight;
        const uint32_t width = header.biWidth;
        const uint32_t padding = get_padding(width);
        img->height = height;
        img->width = width;
        return read_pixel(img, input, padding);
    }
    return READ_FAIL;
}

enum write_status to_bmp(FILE* output, struct image const* img){
    if(output && img){
        const uint32_t height = img->height;
        const uint32_t width = img->width;
        size_t padding = get_padding(width);
        const size_t img_size = (sizeof(struct pixel) * (width) + padding)* height;
        // struct pixel *data = img->data;
        struct bmp_header header = {
            .bfType = 0x4D42,
            .bfileSize = sizeof(struct bmp_header) + img_size,
            .bfReserved = 0,
            .bOffBits = sizeof(struct bmp_header), 
            .biWidth = width,
            .biHeight = height,
            .biPlanes = 1,
            .biBitCount = 24,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biCompression = 0,
            .biSizeImage =  img_size,
            .biClrUsed = 0,
            .biClrImportant = 0,
        };
        if(fwrite(&header,sizeof(struct bmp_header),1,output)!=1) return WRITE_ERROR;
        return WRITE_OK;
    }
    else{
        return WRITE_ERROR;
    }
}


