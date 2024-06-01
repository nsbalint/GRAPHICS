#ifndef PENGUIN_H
#define PENGUIN_H

#include "utils.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Penguin
{
    double penguin_x;
    double penguin_y;
    double position_z;
    double rotation_x;
    double direction_y;
    double speed_y;        // Add speed for y direction
    double rotation_angle; // Add rotation angle for facing direction
    int score;
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
    Model penguin;
} Penguin;

void init_penguin(Penguin *penguin);

#endif // PENGUIN_H
