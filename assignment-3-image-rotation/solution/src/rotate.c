#include "rotate.h"
#include <malloc.h>
struct image rotate(struct image const* source){
    struct image output;
    output.height = source->height;
    output.width = source->width;
    output.data = malloc(sizeof(struct pixel) * source->width * source->height);
    for(size_t i =0; i <source->width; i++){
        for(size_t j = 0; j < source->height; j++){
            set_image(&output, source->height-j-1,i,get_image(source,i,j));
        }
    }
    return output;
}
