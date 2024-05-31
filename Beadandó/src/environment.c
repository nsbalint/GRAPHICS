#include "environment.h"

void init_environment(Environment *environment)
{

    load_model(&(environment->Tree), "assets/models/trees.obj");
    environment->tree_texture = load_texture("assets/textures/tree_texture.jpg");

    load_model(&(environment->Hill), "assets/models/hills.obj");
    environment->hill_texture = load_texture("assets/textures/hill_texture.jpg");

    load_model(&(environment->Snowman), "assets/models/snowman.obj");
    environment->snowman_texture = load_texture("assets/textures/ground_texture.jpg");
}