#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "environment.h"
#include "penguin.h"
#include <obj/model.h>
#include <math.h>

typedef struct Scene
{

    Material material;

    Model ground;
    GLuint ground_texture_id;

    Model skybox;
    GLuint skybox_texture_id;

    Penguin penguin;
    GLuint penguin_texture;

    GLuint help_texture_id;
    int showHelp;

    float light;
    GLuint end_textrue_id;

    Environment environment;
    float fogposition;

} Scene;

void init_scene(Scene *scene);

void set_lighting(float x);

void set_material(const Material *material);

void update_scene(Scene *scene);

void render_scene(const Scene *scene);

void draw_origin();

void help(GLuint texture);

void additionalWindows(GLuint texture, float different);

void winAndLose(GLuint texture);

void restart(Scene *scene);

void draw(GLuint texture, float x1, float y1, float x2, float y2);

#endif
