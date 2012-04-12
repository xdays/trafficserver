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

static int
TSLuaDebug(lua_State * lua)
{
  const char * tag = luaL_checkstring(lua, 1);
  const char * message = luaL_checkstring(lua, 2);

  TSDebug(tag, "%s", message);
  return 0;
}

static const luaL_Reg LUAEXPORTS[] =
{
  { "debug", TSLuaDebug },
  { NULL, NULL}
};

int
LuaApiInit(lua_State * lua)
{
  TSDebug("lua", "initializing Lua API");

  lua_newtable(lua);

  // Register functions in the "ts" module.
  luaL_register(lua, NULL, LUAEXPORTS);

  // Push constants into the "ts" module.
  lua_pushinteger(lua, TSREMAP_DID_REMAP_STOP);
  lua_setfield(lua, -2, "REMAP_COMPLETE");

  lua_pushinteger(lua, TSREMAP_DID_REMAP);
  lua_setfield(lua, -2, "REMAP_CONTINUE");

  TSReleaseAssert(lua_istable(lua, -1) == 1);
  return 1;
}
