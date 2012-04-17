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
#include "lapi.h"

LuaRemapRequest *
LuaRemapRequest::get(lua_State * lua, int index)
{
  return (LuaRemapRequest *)luaL_checkudata(lua, index, "ts.meta.rri");
}

LuaRemapRequest *
LuaRemapRequest::alloc(lua_State * lua)
{
  LuaRemapRequest * rq;

  rq = (LuaRemapRequest *)lua_newuserdata(lua, sizeof(LuaRemapRequest));
  luaL_getmetatable(lua, "ts.meta.rri");
  lua_setmetatable(lua, -2);

    return rq;
  }

bool
LuaPushUrl(lua_State * lua, TSMBuffer buffer, TSMLoc url)
{
  int len;
  const char * str;

#define PUSH_URL_COMPONENT(accessor, name) do { \
  str = accessor(buffer, url, &len); \
  if (str) { \
    lua_pushlstring(lua, str, len); \
  }  else { \
    lua_pushnil(lua); \
  } \
  lua_setfield(lua, -2, name); \
} while (0)

  lua_newtable(lua);

  // Set fundamental URL fields.
  // XXX should we be luvit-compatible with these names?
  PUSH_URL_COMPONENT(TSUrlSchemeGet, "scheme");       // luvit: protocol
  PUSH_URL_COMPONENT(TSUrlUserGet, "user");
  PUSH_URL_COMPONENT(TSUrlPasswordGet, "password");
  PUSH_URL_COMPONENT(TSUrlHostGet, "host");
  lua_pushinteger(lua, TSUrlPortGet(buffer, url));
  lua_setfield(lua, -2, "port");
  PUSH_URL_COMPONENT(TSUrlPathGet, "path");           // luvit: pathname
  PUSH_URL_COMPONENT(TSUrlHttpQueryGet, "query");     // luvit: search
  PUSH_URL_COMPONENT(TSUrlHttpFragmentGet, "fragment");

  // It would be cleaner to add a __tostring metamethod, but to do that we would have to keep the
  // buffer and url around indefinitely. Better to make a straight copy now; use the 'href' key
  // just like luvit does.
  str = TSUrlStringGet(buffer, url, &len);
  if (str) {
    lua_pushlstring(lua, str, len);
    lua_setfield(lua, -2, "href");
    TSfree((void *)str);
  }

  TSReleaseAssert(lua_istable(lua, -1) == 1);
  return true;

#undef PUSH_URL_COMPONENT
}

static int
LuaRemapRedirect(lua_State * lua)
{
  LuaRemapRequest * rq;

  rq = LuaRemapRequest::get(lua, 1);
  luaL_checktype(lua, 2, LUA_TTABLE);

  TSDebug("lua", "redirecting request %p", rq->rri);

  // XXX take the URL table argument and use it to rewrite rri->requestUrl ...

  // A redirect always terminates plugin chain evaluation.
  rq->rri->redirect = 1;
  rq->status = TSREMAP_DID_REMAP_STOP;

  // Return true back to Lua-space.
  lua_pushboolean(lua, 1);
  return 1;
}

static const luaL_Reg RRI[] =
{
  { "redirect", LuaRemapRedirect },
  { NULL, NULL}
};

LuaRemapRequest *
LuaPushRemapRequestInfo(lua_State * lua, TSRemapRequestInfo * rri)
{
  LuaRemapRequest * rq;

  rq = LuaRemapRequest::alloc(lua);
  rq->rri = rri;
  rq->status = TSREMAP_NO_REMAP;

  TSReleaseAssert(lua_isuserdata(lua, -1) == 1);
  return rq;
}

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
  lua_pushstring(lua, TSTrafficServerVersionGet());
  lua_setfield(lua, -2, "VERSION");

  lua_pushinteger(lua, TSTrafficServerVersionGetMajor());
  lua_setfield(lua, -2, "MAJOR_VERSION");

  lua_pushinteger(lua, TSTrafficServerVersionGetMinor());
  lua_setfield(lua, -2, "MINOR_VERSION");

  lua_pushinteger(lua, TSTrafficServerVersionGetPatch());
  lua_setfield(lua, -2, "PATCH_VERSION");

  lua_pushinteger(lua, TSREMAP_DID_REMAP_STOP);
  lua_setfield(lua, -2, "REMAP_COMPLETE");

  lua_pushinteger(lua, TSREMAP_DID_REMAP);
  lua_setfield(lua, -2, "REMAP_CONTINUE");

  // Register TSRemapRequestInfo metatable.
  luaL_newmetatable(lua, "ts.meta.rri");
  lua_pushvalue(lua, -1);
  lua_setfield(lua, -2, "__index");

  luaL_register(lua, NULL, RRI);

  // Pop the metatable.
  lua_pop(lua, 1);

  TSReleaseAssert(lua_istable(lua, -1) == 1);
  return 1;
}
