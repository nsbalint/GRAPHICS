#ifndef timer_H
#define timer_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>
#include <time.h>

typedef struct Timer
{
    clock_t start;
    clock_t end;

    float max_time;

    GLuint timer_texture;

    GLuint timer_0_texture;
    GLuint timer_1_texture;
    GLuint timer_2_texture;
    GLuint timer_3_texture;
    GLuint timer_4_texture;
    GLuint timer_5_texture;
} Timer;

void init_timer(Timer *timer);

#endif