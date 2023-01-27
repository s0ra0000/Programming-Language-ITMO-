#include "image.h"
#include <stdio.h>
#include <stdlib.h>



struct pixel get_image(struct image const* img, uint64_t x, uint64_t y) {
    return img->data[img->width * y + x];
}

void set_image(struct image *img, uint64_t x, uint64_t y, struct pixel pixel){
    img -> data[img->width*y+x] = pixel;
}


