#include "cub.h"

void set_size(Cuboid *cuboid, float height, float width, float length)
{
    cuboid->length = length;
    cuboid->width = width;
    cuboid->height = height;
}

float calc_volume(Cuboid cuboid)
{
    float volume = cuboid.length * cuboid.width * cuboid.height;
    return volume;
}

float calc_surface(Cuboid cuboid)
{
    float surface = (cuboid.width * cuboid.height + cuboid.height * cuboid.length + cuboid.length * cuboid.width) * 2;
    return surface;
}

bool has_square_face(Cuboid cuboid)
{
    if (cuboid.length == cuboid.width * cuboid.height || cuboid.width == cuboid.length * cuboid.height || cuboid.height == cuboid.length * cuboid.width)
    {
        return true;
    }
    return false;
}
float read_input(char *msg)
{
    float number = 0;
    puts(msg);
    bool ok;
    do
    {
        ok = true;
        if (scanf("%f", &number) != 1)
        {
            printf("Invalid input");
            ok = false;
            while (getchar() != '\n')
                ;
        }
    } while (!ok);
    return number;
}