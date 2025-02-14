#ifndef ENVIRONMENT_H

#define ENVIRONMENT_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Environment
{
    Model Tree;
    GLuint tree_texture;

    Model Hill;
    GLuint hill_texture;

    Model Snowman;
    GLuint snowman_texture;

} Environment;

void init_environment(Environment *environment);

#endif