/** @file

  Traffic Server SDK API header file for debug messages

  @section license License

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

  @section developers Developers

 */

#ifndef __TS_DEBUG_H__
#define __TS_DEBUG_H__

#include <ts/ts.h>

/** all of these APIs assume you've defined PLUGIN_NAME first before
 *  including this header file.
 **/

#ifndef PLUGIN_NAME
# error "A plugin must define a PLUGIN_NAME string constant *before* including <ts/ts.h> in order to use TSPlugin(Debug|Info|Warning|Error|Fatal)"
#else

#define TSPluginDebug(fmt, args...) do {                                    \
  TSDebug(PLUGIN_NAME, "DEBUG: [%s:%d] [%s] " fmt, __FILE__, __LINE__, __FUNCTION__ , ##args ); \
  } while (0)

#define TSPluginInfo(fmt, args...) do {                                    \
  TSDebug(PLUGIN_NAME, "INFO: " fmt, ##args ); \
  } while (0)

#define TSPluginWarning(fmt, args...) do {                                    \
  TSDebug(PLUGIN_NAME, "WARNING: " fmt, ##args ); \
} while (0)

#define TSPluginError(fmt, args...) do {                                    \
  TSError("[%s] [%s:%d] [%s] ERROR: " fmt, PLUGIN_NAME, __FILE__, __LINE__, __FUNCTION__ , ##args ); \
  TSDebug(PLUGIN_NAME, "[%s:%d] [%s] ERROR: " fmt, __FILE__, __LINE__, __FUNCTION__ , ##args ); \
} while (0)
#endif

#define TSPluginFatal(fmt, args...) do {                                    \
  TSError("[%s] [%s:%d] [%s] FATAL: " fmt, PLUGIN_NAME, __FILE__, __LINE__, __FUNCTION__ , ##args ); \
  TSDebug(PLUGIN_NAME, "[%s:%d] [%s] FATAL: " fmt, __FILE__, __LINE__, __FUNCTION__ , ##args ); \
  exit(-1); \
} while (0)


# endif /* __TS_DEBUG_H__ */

