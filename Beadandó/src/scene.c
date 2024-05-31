#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_scene(Scene *scene)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    scene->difficulty = 1;
    scene->fog_strength = 0.07;

    scene->easy_on = load_texture("assets/textures/easy_1.jpg");
    scene->medium_on = load_texture("assets/textures/normal_1.jpg");
    scene->hard_on = load_texture("assets/textures/hard_1.jpg");
    scene->easy_off = load_texture("assets/textures/easy_0.jpg");
    scene->medium_off = load_texture("assets/textures/normal_0.jpg");
    scene->hard_off = load_texture("assets/textures/hard_0.jpg");

    load_model(&(scene->ground), "assets/models/ground.obj");
    scene->ground_texture = load_texture("assets/textures/ground_texture.jpg");

    scene->help_texture_id = load_texture("assets/textures/help_texture.jpg");

    load_model(&(scene->skybox), "assets/models/skyboxSphere.obj");
    scene->skybox_texture = load_texture("assets/textures/sky.jfif");

    scene->win_texture = load_texture("assets/textures/win.jpg");
    scene->lose_texture = load_texture("assets/textures/lose.jpg");

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_FOG);
    float color[] = {0.5, 0.5, 0.5, 1.0};
    glFogfv(GL_FOG_COLOR, color);
    glFogf(GL_FOG_DENSITY, scene->fog_strength);
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 1.0f);
    scene->light = 0.4f;

    init_environment(&(scene->environment));
    init_diamond(&(scene->diamond));
    init_timer(&(scene->timer));

    scene->showHelp = 1;
    scene->diamond.score = 0;
    scene->timer.start = clock();
    scene->show_win = false;
    scene->show_lose = false;
}

void set_lighting(float x)
{
    float ambient_light[] = {x, x, x, 1.0f};
    float diffuse_light[] = {x, x, x, 1.0f};
    float specular_light[] = {x, x, x, 1.0f};
    float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
    glFogf(GL_FOG_DENSITY, scene->fog_strength);
    set_lighting(scene->light);
    if (scene->diamond.score > 9)
    {
        scene->show_win = true;
    }

    scene->timer.end = clock();
    if ((float)(scene->timer.end - scene->timer.start) / CLOCKS_PER_SEC > scene->timer.max_time)
        scene->show_lose = true;
}

void place_diamond(Scene *scene)
{
    srand(rand());
    float random_x = (float)rand() / (float)(RAND_MAX / 14) - 7;
    float random_y = (float)rand() / (float)(RAND_MAX / 14) - 7;
    scene->diamond.diamond_x = random_x;
    scene->diamond.diamond_y = random_y;
}

void render_scene(const Scene *scene)
{
    // ground
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->ground));
    glPopMatrix();

    // diamond
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float ambient_material_color[] = {0.2f, 0.58f, 0.92f};
    float diffuse_material_color[] = {1.0f, 1.0f, 1.0f, 0.85f};
    float specular_material_color[] = {1.0f, 1.0f, 1.0f};

    float shininess = 50.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

    glPushMatrix();
    glScalef(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->diamond.diamond_texture);

    glTranslatef(scene->diamond.diamond_x, scene->diamond.diamond_y, scene->diamond.position_z);
    glRotated(90, 1, 0, 0);
    glRotatef(scene->diamond.rotation_x, 0, 1, 0);
    draw_model(&(scene->diamond.diamond));
    glPopMatrix();

    set_material(&(scene->material));

    glDisable(GL_BLEND);

    // tree
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->environment.tree_texture);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->environment.Tree));
    glPopMatrix();

    // snowman
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->environment.snowman_texture);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->environment.Snowman));
    glPopMatrix();

    // stone
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->environment.stone_texture);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->environment.Stone));
    glPopMatrix();

    // bush
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->environment.bush_texture);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->environment.Bush));
    glPopMatrix();

    // hill
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->environment.hill_texture);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->environment.Hill));
    glPopMatrix();

    // skybox
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->skybox_texture);

    draw_model(&(scene->skybox));
    glPopMatrix();

    points(&(scene->diamond));
    clocks(&(scene->timer));
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void additionalWindows(GLuint texture, float different)
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(different, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(different, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}

void help(GLuint texture)
{
    additionalWindows(texture, 0.7);
}

void winAndLose(GLuint texture)
{
    additionalWindows(texture, 2);
}

void restart(Scene *scene)
{
    scene->diamond.score = 0;
    scene->timer.start = clock();
    scene->show_win = false;
    scene->show_lose = false;
}

void draw(GLuint texture, float x1, float y1, float x2, float y2)
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(x1, y1, -3);
    glTexCoord2f(1, 0);
    glVertex3d(x2, y1, -3);
    glTexCoord2f(1, 1);
    glVertex3d(x2, y2, -3);
    glTexCoord2f(0, 1);
    glVertex3d(x1, y2, -3);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);

    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 6000);
}