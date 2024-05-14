#include "camera.h"

#include <GL/gl.h>

#include <math.h>

void init_camera(Camera *camera)
{
    camera->position.x = 2.0;
    camera->position.y = 2.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
}

void update_camera(Camera *camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    vec3 newPosition;
    newPosition.x = camera->position.x + cos(angle) * camera->speed.y * time;
    newPosition.y = camera->position.y + sin(angle) * camera->speed.y * time;
    newPosition.x += cos(side_angle) * camera->speed.x * time;
    newPosition.y += sin(side_angle) * camera->speed.x * time;

    if (check_collisions(newPosition) == 0)
    {
        camera->position.x = newPosition.x;
        camera->position.y = newPosition.y;
    }
}

void set_view(const Camera *camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera *camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0)
    {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0)
    {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0)
    {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0)
    {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera *camera, double speed)
{
    camera->speed.y = speed*3;
}

void set_camera_side_speed(Camera *camera, double speed)
{
    camera->speed.x = speed*3;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

int check_collisions(vec3 newposition)
{
    /* map Y edges */
    if ((newposition.y < -8) || (newposition.y > 7.5))
        return 1;

    /* map X edges */
    if ((newposition.x < -8) || (newposition.x > 8))
        return 1;

    //Trees
    if (calc_collision(newposition, 2.53, -5.51, 0.2, 0.3) == 1)
        return 1;
    
    if (calc_collision(newposition, -5.373, 4.304, 0.2, 0.3) == 1)
        return 1;

    // No collision found
    return 0;
}

int calc_collision(vec3 newposition, float posX, float posY, float boxSizeX, float boxSizeY)
{
    if ((newposition.x > posX - boxSizeX) && (newposition.x < posX + boxSizeX))
        if ((newposition.y > posY - boxSizeY) && (newposition.y < posY + boxSizeY))
            return 1;
    return 0;
}
