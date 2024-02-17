#ifndef CUBOID_H
#define CUBOID_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
    float height;
    float width;
    float length;
} Cuboid;

void set_size(Cuboid *cuboid, float height, float width, float length);
float calc_volume(Cuboid cuboid);
float calc_surface(Cuboid cuboid);
bool has_square_face(Cuboid cuboid);
float read_input(char *msg);

#endif /* CUBOID_H */