#include "penguin.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void init_penguin(Penguin *penguin)
{
    load_model(&(penguin->penguin), "assets/models/penguin.obj");
    penguin->penguin_texture = load_texture("assets/textures/penguin.jpg");

    penguin->penguin_0_texture = load_texture("assets/textures/penguin_0.jpg");
    penguin->penguin_1_texture = load_texture("assets/textures/penguin_1.jpg");
    penguin->penguin_2_texture = load_texture("assets/textures/penguin_2.jpg");
    penguin->penguin_3_texture = load_texture("assets/textures/penguin_3.jpg");
    penguin->penguin_4_texture = load_texture("assets/textures/penguin_4.jpg");
    penguin->penguin_5_texture = load_texture("assets/textures/penguin_5.jpg");
    penguin->penguin_6_texture = load_texture("assets/textures/penguin_6.jpg");
    penguin->penguin_7_texture = load_texture("assets/textures/penguin_7.jpg");
    penguin->penguin_8_texture = load_texture("assets/textures/penguin_8.jpg");
    penguin->penguin_9_texture = load_texture("assets/textures/penguin_9.jpg");
    penguin->penguin_10_texture = load_texture("assets/textures/penguin_10.jpg");

    srand(rand());
    penguin->penguin_x = 0;
    penguin->penguin_y = 0;
    penguin->rotation_x = 0.0;
    penguin->position_z = 0.0;
    penguin->score = 0;
}

void points(Penguin *penguin)
{
    GLuint render_texture;

    switch (penguin->score)
    {
    case 0:
        render_texture = penguin->penguin_0_texture;
        break;
    case 1:
        render_texture = penguin->penguin_1_texture;
        break;
    case 2:
        render_texture = penguin->penguin_2_texture;
        break;
    case 3:
        render_texture = penguin->penguin_3_texture;
        break;
    case 4:
        render_texture = penguin->penguin_4_texture;
        break;
    case 5:
        render_texture = penguin->penguin_5_texture;
        break;
    case 6:
        render_texture = penguin->penguin_6_texture;
        break;
    case 7:
        render_texture = penguin->penguin_7_texture;
        break;
    case 8:
        render_texture = penguin->penguin_8_texture;
        break;
    case 9:
        render_texture = penguin->penguin_9_texture;
        break;
    case 10:
        render_texture = penguin->penguin_10_texture;
        break;
    }

    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, render_texture);

    glBegin(GL_QUADS);
    // Adjust the vertex coordinates to make the quad smaller
    glTexCoord2f(0, 0);
    glVertex3d(2.5, 1.5, -3); // Top-left corner
    glTexCoord2f(1, 0);
    glVertex3d(1.5, 1.5, -3); // Top-right corner
    glTexCoord2f(1, 1);
    glVertex3d(1.5, 1.0, -3); // Bottom-right corner
    glTexCoord2f(0, 1);
    glVertex3d(2.5, 1.0, -3); // Bottom-left corner

    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    // glEnable(GL_FOG);

    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 6000);
}