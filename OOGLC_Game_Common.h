#pragma once

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
