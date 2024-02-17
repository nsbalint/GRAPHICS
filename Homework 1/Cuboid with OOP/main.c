#include "cub.c"

int main()
{
    Cuboid cuboid;

    float length = read_input("Length of cuboid: ");
    float width = read_input("Width of the cuboid: ");
    float height = read_input("Height of the cuboid: ");

    set_size(&cuboid, height, width, length);
    printf("Volume of the cuboid: %.2f.\n", calc_volume(cuboid));
    printf("Surface of the cuboid: %.2f.\n", calc_surface(cuboid));
    if (has_square_face(cuboid) == true)
        printf("The cuboid has a square face");
    else
        printf("The cuboid doesn't have a square face");
}