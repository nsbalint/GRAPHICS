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
    GLuint timer_10_texture;
    GLuint timer_20_texture;
    GLuint timer_30_texture;
    GLuint timer_40_texture;
    GLuint timer_50_texture;
} Timer;

void init_timer(Timer *timer);

#endif
