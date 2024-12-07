#ifndef GLGAME 
#define GLGAME 

#include "OOGLC_Game_Common.h"

void init_RenderFuncMemoryVec()
{
    render_function_map.func_memory.size_binary = 10;
    //render_function_map.func_memory.size        = 0; 
    render_function_map.func_memory.func_memory_list = malloc(sizeof(struct WideVoidptr*) * render_function_map.func_memory.size_binary);

}
void init_RenderFuncFuncVec()
{
    render_function_map.func_funcs.size_binary = 10;
    render_function_map.func_funcs.size = 0;
    render_function_map.func_funcs.func_funcs = malloc(sizeof(render_func_ptr) * render_function_map.func_funcs.size_binary);
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
    render_function_map.func_funcs.func_funcs[render_function_map.func_funcs.size] = func;

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
uint64_t GetIndexFromFuncKey(render_func_ptr func)
{
    /*
        Make 0 an invalid index for this, i dont want functions accessing it, -1 cant work as a return. its unsigned.
    */
    for (uint64_t x = 0; x < render_function_map.func_funcs.size; x++)
    {
        if (render_function_map.func_funcs.func_funcs[x] == func)
        {
            return x;
        }

    }
    return 0;
}
bool is_gl_loaded()
{
    return game.is_gl_loaded;
};
#endif