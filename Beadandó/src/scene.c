
#include "scene.h"
#include "environment.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    load_model(&(scene->ground), "assets/models/ground.obj");
    scene->ground_texture_id = load_texture("assets/textures/ground.jpg");

    load_model(&(scene->penguin), "assets/models/penguin.obj");
    scene->penguin_texture_id = load_texture("assets/textures/penguin.jpg");

    load_model(&(scene->skybox), "assets/models/skybox.obj");
    scene->skybox_texture_id = load_texture("assets/textures/sky.jfif");

    scene->help_texture_id = load_texture("assets/textures/Untitled-2.png");
    scene->end_textrue_id = load_texture("assets/textures/gameover.jpg");

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

    scene->light = 1.0f;

    scene->showHelp = 0;

    init_penguin(&(scene->penguin));

    glEnable(GL_FOG);
    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    scene->fogposition = 0.0f;
}

void set_lighting(float x)
{
    float ambient_light[] = {x, x, x, 1.0f};
    float diffuse_light[] = {x, x, x, 1.0f};
    float specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
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
    set_lighting(scene->light);

    glFogf(GL_FOG_START, scene->fogposition);
    glFogf(GL_FOG_END, scene->fogposition + 10.0f);
}
void render_scene(const Scene *scene)
{

    // ground
    glPushMatrix();
    glScalef(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
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
    glBindTexture(GL_TEXTURE_2D, scene->penguin.penguin_texture);

    glRotated(90, 1, 0, 0);
    draw_model(&(scene->penguin.penguin));
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

    // skybox
    glPushMatrix();
    glScalef(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->skybox_texture_id);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->skybox));
    glPopMatrix();

    // snowman
    glColor3f(1, 1, 1);
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->penguin_texture_id);
    glRotated(90, 1, 0, 0);
    glTranslatef(1, 0, 1);
    draw_model(&(scene->penguin));
    glPopMatrix();
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

void help(GLuint texture)
{
    glDisable(GL_FOG);
    //  glDisable(GL_LIGHTING);
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
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    //  glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}
