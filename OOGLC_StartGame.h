#pragma once
#include <stdio.h>
#include "OOGLC_Game.h"
//#include "OOGLC_Window.h"

#include "glad.h"

void StartGameLoop(struct Game* game);


void StartGame(char** varg)
{

    game.cli_vargs = varg;

    // Initialize GLFW
    if (!glfwInit()) {
        puts("Failed to initialize GLFW");
        return;
    }
    // Create a windowed mode window and its OpenGL context
    game.window = glfwCreateWindow(800, 600, "Shin Megami Tensei", NULL, NULL);
    if (!game.window) {
        puts("Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(game.window);
    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    puts("Loading ...\n");
    if (version == 0) {
        puts("Failed to initialize GLAD\n");

    }
    else {
        printf("Version is %i \n", version);
    }
    game.is_gl_loaded = true;
    StartGameLoop(&game);

}
//GAMELOOOP
void StartGameLoop(struct Game* game)
{

    while (!glfwWindowShouldClose(game->window)) {
        // Input
        if (glfwGetKey(game->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(game->window, 1);

        // Render
        //clear_game_screen();
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        //glUseProgram(This->_shaderProgram);

        // Bind the VAO
        //glBindVertexArray(This->_VAO);

        // Draw the triangle


        // Swap front and back buffers
        glfwSwapBuffers(game->window);

        // Poll for and process events
        glfwPollEvents();  // Ensure This is called to handle window events

        // Optional: Limit the frame rate

        //std::This_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
}
