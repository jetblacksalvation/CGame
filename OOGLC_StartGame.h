#pragma once
#include <stdio.h>
#include "OOGLC_Game.h"
//#include "OOGLC_Window.h"

#include "glad.h"

void StartGameLoop(struct Game* game);
void initAndRenderSquares(void* mem)
{
    //Check allocated memory.
    uint64_t allocatd_mem = *((uint64_t*)mem);

    mem = &((uint64_t*)mem)[1];
    if (*(char*)mem != 'c')
    {
        printf("Not initialized, initializing data for all squares.\n");
        *(char*)mem = 'c';
        float vertices[12];
        //*((char*)mem + sizeof(char)) = 0;

    }
    else 
    {
        /*
            evaluation stage.
        */
        mem = &((char*)mem)[1];
        //offset the memcheck.


        //*((char*)mem + sizeof(char)) += 1;

    }
    printf("called initAndRenderSquares!\n");
    printf("Alloced memory is %i\n", allocatd_mem);
};
void InitializeGloabls()
{
    init_RenderFuncMemoryVecMap();
    AddRenderFuncEntry(&initAndRenderSquares, 32);
}
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
    InitializeGloabls();
    StartGameLoop(&game);

}
//GAMELOOOP
void StartGameLoop(struct Game* game)
{
    uint32_t start = 0;
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
        start = 0;
        for (start; start < render_function_map.func_funcs.size; start++)
        {
            
            CallRenderEntry(start);

        }
        // Draw the triangle


        // Swap front and back buffers
        glfwSwapBuffers(game->window);

        // Poll for and process events
        glfwPollEvents();  // Ensure This is called to handle window events

        // Optional: Limit the frame rate

        //std::This_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
}
