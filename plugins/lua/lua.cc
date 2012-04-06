/*
  Licensed to the Apache Software Foundation (ASF) under one
  or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <ts/ts.h>
#include <ts/remap.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <unistd.h>

static void *
LuaAllocate(void * ud, void * ptr, size_t osize, size_t nsize)
{
  TSReleaseAssert(ud == NULL);

  if (nsize == 0) {
    TSfree(ptr);
    return NULL;
  }

  return TSrealloc(ptr, nsize);
}

static int
TSLuaDebug(lua_State * lua)
{
  const char * tag = luaL_checkstring(lua, 1);
  const char * message = luaL_checkstring(lua, 2);

  TSDebug(tag, "%s", message);
  return 0;
}

struct LuaExport
{
  lua_CFunction function;
  const char *  name;
};

static const luaL_Reg LUAEXPORTS[] =
{
  { "debug", TSLuaDebug },
  { NULL, NULL}
};

TSReturnCode
TSRemapInit(TSRemapInterface * api_info, char * errbuf, int errbuf_size)
{
  TSDebug("lua", "loading lua plugin");
  return TS_SUCCESS;
}

TSReturnCode
TSRemapNewInstance(int argc, char * argv[], void ** ih, char * errbuf, int errbuf_size)
{
  lua_State * lua;

  lua = lua_newstate(LuaAllocate, NULL);
  if (lua == NULL) {
    return TS_ERROR;
  }

  luaL_openlibs(lua);
  luaL_register(lua, "ts", LUAEXPORTS);

  for (int i = 0; i < argc; ++i) {
    if (access(argv[i], R_OK) == 0) {
      TSDebug("lua", "%s loading lua file %s", __func__, argv[i]);
      if (luaL_dofile(lua, argv[i]) != 0) {
        // If the load failed, it should have pushed an error message.
        TSError("lua load error: %s", lua_tostring(lua, -1));
        lua_pop(lua, 1);
      }
    }
  }

  lua_getglobal(lua, "init");
  if (lua_pcall(lua, 0, 1, 0) != 0) {
    TSDebug("lua", "init failed: %s", lua_tostring(lua, -1));
    lua_pop(lua, 1);
  }

  *ih = lua;
  return TS_SUCCESS;
}

void
TSRemapDeleteInstance(void * ih)
{
  lua_State * lua = (lua_State *)ih;
  lua_close(lua);
}

TSRemapStatus
TSRemapDoRemap(void * ih, TSHttpTxn rh, TSRemapRequestInfo *rri)
{
  return TSREMAP_NO_REMAP;
}
