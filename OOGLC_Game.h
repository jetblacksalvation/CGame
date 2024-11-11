#ifndef GLGAME 
#define GLGAME 

#include<Windows.h>

#include <GLFW/glfw3.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>



typedef  void (*render_func_ptr)(void*);
/*
    void* mem, uint64_t size
    this is the intended arguements for functions that are passed to this.
*/

struct Game {
    char** cli_vargs; //populated from cli commands.
    GLFWwindow* window;
    float window_color[4];
    bool is_gl_loaded;
};

struct WideVoidptr
{
    void* data;
    uint64_t size;
};

struct RenderFuncMemoryVec
{
    uint64_t size_binary;// how much memory has been allocated.
    //uint32_t size;// how many entries.

    struct WideVoidptr* func_memory_list;
    //iterate through index 0 -> size, for each index free its memory when needed.
    //this should work until the function decides it doesn't need to be in memory anymore. 

};
struct RenderFuncFuncVec
{
    uint64_t size_binary;// how much memory has been allocated.
    uint32_t size;// how many entries.

    render_func_ptr* func_funcs;
    //iterate through index 0 -> size, for each index free its memory when needed.
    //this should work until the function decides it doesn't need to be in memory anymore.
};

struct RenderFuncMemoryMap
{
    //contains all the keys to all the sections of allocated memory.
    struct RenderFuncMemoryVec func_memory;
    struct RenderFuncFuncVec   func_funcs;

};
//data is encoded as binary. no human readable format, just use offset from 0 addresses, and do some book keeping ig. 


struct Game game = { NULL, NULL, {0.2f, 0.3f, 0.3f, 1.0f},false };
struct RenderFuncMemoryMap render_function_map = { NULL,NULL };


void init_RenderFuncMemoryVec()
{
    render_function_map.func_memory.size_binary = 10;
    //render_function_map.func_memory.size        = 0; 
    render_function_map.func_memory.func_memory_list = malloc(sizeof(struct WideVoidptr*) * render_function_map.func_memory.size_binary);

}
void init_RenderFuncFuncVec()
{
    render_function_map.func_funcs.size_binary  = 10;
    render_function_map.func_funcs.size         = 0;
    render_function_map.func_funcs.func_funcs   = malloc(sizeof(render_func_ptr) * render_function_map.func_funcs.size_binary);
};
void init_RenderFuncMemoryVecMap()
{
    //render_function_map.func_funcs = malloc(sizeof(render_func_ptr) * 10);
    init_RenderFuncFuncVec();
    init_RenderFuncMemoryVec();

    //ten entries
}
void AddRenderFuncEntry(render_func_ptr func, uint64_t amount_to_alloc)
{
    /*
        this shit i need to be careful at. make sure the function and the key both know what address each other are. that way they both can make sure they are correct
    */
    render_function_map.func_funcs.func_funcs[render_function_map.func_funcs.size]   = func; 
    
    render_function_map.func_memory.func_memory_list[render_function_map.func_funcs.size].data = malloc(amount_to_alloc);
    render_function_map.func_memory.func_memory_list[render_function_map.func_funcs.size].size = amount_to_alloc;

    if (amount_to_alloc < 0)
    {
        printf("AddRenderFuncEntry got %i, which is less than zero", amount_to_alloc);
        exit(0);
        amount_to_alloc = 0;
    }
    amount_to_alloc += sizeof(uint64_t);
    //func(render_function_map.func_memory.func_memory[render_function_map.func_funcs.size].data, amount_to_alloc);
    //render_function_map.func_memory.func_memory[render_function_map.func_funcs.size].size;
    *((uint64_t*)render_function_map.func_memory.func_memory_list[render_function_map.func_funcs.size].data) = render_function_map.func_memory.func_memory_list[render_function_map.func_funcs.size].size;
    /*
        anything beyond uint64_t is reserved for the funciton that needs the memory.
    */

    render_function_map.func_funcs.size += 1;

}
void RemoveRenderFuncEntry(render_func_ptr func)
{

}
void CallRenderEntry(uint32_t index)
{
    render_function_map.func_funcs.func_funcs[index](render_function_map.func_memory.func_memory_list[index].data);
    
}
bool is_gl_loaded()
{
    return game.is_gl_loaded;
};
#endif