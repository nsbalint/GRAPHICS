#ifndef PENGUIN_H
#define PENGUIN_H

#include "utils.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Penguin
{
    Model penguin;
    GLuint penguin_texture;
    GLuint penguin_0_texture;
    GLuint penguin_1_texture;
    GLuint penguin_2_texture;
    GLuint penguin_3_texture;
    GLuint penguin_4_texture;
    GLuint penguin_5_texture;
    GLuint penguin_6_texture;
    GLuint penguin_7_texture;
    GLuint penguin_8_texture;
    GLuint penguin_9_texture;
    GLuint penguin_10_texture;

    float penguin_x;
    float penguin_y;
    float rotation_x;
    float position_z;
    int score;

} Penguin;

void init_penguin(Penguin *penguin);

#endif // PENGUIN_H
