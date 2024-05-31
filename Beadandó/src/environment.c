#include "environment.h"

void init_environment(Environment *environment)
{

    load_model(&(environment->Tree), "assets/models/trees.obj");
    environment->tree_texture = load_texture("assets/textures/tree_texture.jpg");

    load_model(&(environment->Stone), "assets/models/stones.obj");
    environment->stone_texture = load_texture("assets/textures/stone_texture.jpg");

    load_model(&(environment->Bush), "assets/models/bushes.obj");
    environment->bush_texture = load_texture("assets/textures/bush_texture.jpg");

    load_model(&(environment->Hill), "assets/models/hills.obj");
    environment->hill_texture = load_texture("assets/textures/hill_texture.jpg");

    load_model(&(environment->Snowman), "assets/models/snowman.obj");
    environment->snowman_texture = load_texture("assets/textures/hill_texture.jpg");
}