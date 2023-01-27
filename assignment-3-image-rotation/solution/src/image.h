#pragma once
#include <stdint.h>
#include <stdio.h>

struct pixel{
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct pixel get_image(struct image const* img, uint64_t x, uint64_t y);

void set_image(struct image *img, uint64_t x, uint64_t y, struct pixel pixel);

