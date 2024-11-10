#ifndef GLGAME 
#define GLGAME 

#include<Windows.h>

#include <GLFW/glfw3.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
void (*render_func_ptr)(void*);

struct Game {
    char** cli_vargs; //populated from cli commands.
    GLFWwindow* window;
    float window_color[4];
    bool is_gl_loaded;
};
struct RenderFuncNames 
{
      uint32_t size;
      uint64_t binary_size;
      char** names;

};
struct RenderFuncMemory
{
    uint32_t size;
    uint64_t binary_size;
    void** data;

};

struct RenderFuncMemoryMap
{
    struct RenderFuncNames func_names;
    //contains all the keys to all the sections of allocated memory.
    void** func_memory;

    struct render_func_ptr* func_funcs;

};
//data is encoded as binary. no human readable format, just use offset from 0 addresses, and do some book keeping ig. 

void init_RenderFuncMemoryMap() 
{
    render_function_map.func_funcs = malloc(sizeof(render_func_ptr) * 10);
}
bool is_gl_loaded()
{
    return game.is_gl_loaded;
};

struct Game game = { NULL, NULL, {0.2f, 0.3f, 0.3f, 1.0f},false };
struct RenderFuncMemoryMap render_function_map = { NULL,NULL };

#endif