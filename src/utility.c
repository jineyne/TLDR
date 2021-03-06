#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int clamp(int x, int low, int high) {
    if(x<low) return low;
    else if(x>high) return high;
    else return x;
}

int typerror(lua_State *L, int arg, const char *name) {
    return luaL_typerror(L, arg, name);
}

void check_userdata_type(lua_State *L, int argn, const char *name) {
    if(lua_gettop(L)<argn) typerror(L, argn, name);
    if(!lua_isuserdata(L, argn)) typerror(L, argn, name);
    lua_getmetatable(L, argn);
    lua_getfield(L, -1, "__type");
    lua_pushstring(L, name);
    if(!lua_equal(L, -1, -2)) typerror(L, argn, name);
    lua_pop(L, 3);
}
