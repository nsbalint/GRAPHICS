#include "app.h"
#include <SDL2/SDL_image.h>

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "PenguinGame",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene)); // This ensures show_lose is set to false

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 1500);
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    // Inicializáljuk az egér pozícióját a program elején
    SDL_GetMouseState(&mouse_x, &mouse_y);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_SPACE:
                if (app->scene.show_win || app->scene.show_lose)
                {
                    restart(&(app->scene));
                }
                break;
            case SDL_SCANCODE_DOWN:
                if (app->scene.difficulty < 3 && app->scene.showHelp == 1)
                {
                    app->scene.difficulty += 1;
                    restart(&(app->scene));
                }
                break;
            case SDL_SCANCODE_UP:
                if (app->scene.difficulty > 1 && app->scene.showHelp == 1)
                {
                    app->scene.difficulty -= 1;
                    restart(&(app->scene));
                }
                break;
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                if (!(app->scene.show_win || app->scene.show_lose))
                {
                    set_camera_speed(&(app->camera), 1);
                }
                break;
            case SDL_SCANCODE_S:
                if (!(app->scene.show_win || app->scene.show_lose))
                {
                    set_camera_speed(&(app->camera), -1);
                }
                break;
            case SDL_SCANCODE_A:
                if (!(app->scene.show_win || app->scene.show_lose))
                {
                    set_camera_side_speed(&(app->camera), 1);
                }
                break;
            case SDL_SCANCODE_D:
                if (!(app->scene.show_win || app->scene.show_lose))
                {
                    set_camera_side_speed(&(app->camera), -1);
                }
                break;
            case SDL_SCANCODE_KP_PLUS:
                app->scene.light += 0.1;
                break;
            case SDL_SCANCODE_KP_MINUS:
                app->scene.light -= 0.1;
                break;
            case SDL_SCANCODE_F1:
                if (app->scene.showHelp == 0)
                {
                    app->scene.showHelp = 1;
                }
                else
                {
                    app->scene.showHelp = 0;
                    glFrustum(
                        -.08, .08,
                        -.06, .06,
                        .1, 6000);
                }
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Eltávolítjuk az is_mouse_down változót
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            // Az egér mozgásának kezelése folyamatosan történik, függetlenül attól, hogy az egér gomb le van-e nyomva
            if (!(app->scene.show_win || app->scene.show_lose))
            {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            // Eltávolítjuk az is_mouse_down változót
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App *app)
{
    SDL_Event event;
    double current_time;
    double elapsed_time;
    double last_time;
    double penguin_x = app->scene.penguin.penguin_x;
    double penguin_y = app->scene.penguin.penguin_y;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;

    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));

    double range = 0.65;

    if (penguin_x - range < app->camera.position.x && app->camera.position.x < penguin_x + range)
    {
        if (penguin_y - range < app->camera.position.y && app->camera.position.y < penguin_y + range)
        {
            app->scene.penguin.score++;
            place_penguin(&(app->scene));
        }
    }

    app->scene.penguin.rotation_x += 1 * 0.065;

    if (app->scene.penguin.rotation_x > 360.0)
    {
        app->scene.penguin.rotation_x -= 360.0;
    }

    app->scene.penguin.position_z = 0;
    last_time = current_time;
}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible)
    {
        show_texture_preview();
    }

    if (app->scene.show_win)
    {
        winAndLose(app->scene.win_texture);
    }

    if (app->scene.show_lose && !app->scene.show_win)
    {
        winAndLose(app->scene.lose_texture);
    }

    if (app->scene.showHelp == 1)
    {
        draw(app->scene.help_texture_id, -2.0, 1.5, 0.7, -1.5);

        if (app->scene.difficulty == 3)
        {
            app->scene.fog_strength = 0.5;
            app->scene.timer.max_time = 46;
            draw(app->scene.medium_off, 0.83, 0.445, 2.03, -0.445);
            draw(app->scene.easy_off, 0.83, 1.5, 2.03, 0.61);
            draw(app->scene.hard_on, 0.83, -0.61, 2.03, -1.5);
        }
        else if (app->scene.difficulty == 2)
        {
            app->scene.fog_strength = 0.2;
            app->scene.timer.max_time = 41;
            draw(app->scene.medium_on, 0.83, 0.445, 2.03, -0.445);
            draw(app->scene.easy_off, 0.83, 1.5, 2.03, 0.61);
            draw(app->scene.hard_off, 0.83, -0.61, 2.03, -1.5);
        }
        else
        {
            app->scene.fog_strength = 0.07;
            app->scene.timer.max_time = 46;
            draw(app->scene.medium_off, 0.83, 0.445, 2.03, -0.445);
            draw(app->scene.easy_on, 0.83, 1.5, 2.03, 0.61);
            draw(app->scene.hard_off, 0.83, -0.61, 2.03, -1.5);
        }
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}