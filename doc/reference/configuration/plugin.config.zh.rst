.. Licensed to the Apache Software Foundation (ASF) under one
   or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at
 
   http://www.apache.org/licenses/LICENSE-2.0
 
  Unless required by applicable law or agreed to in writing,
  software distributed under the License is distributed on an
  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
  KIND, either express or implied.  See the License for the
  specific language governing permissions and limitations
  under the License.

=============
plugin.config（中文）
=============

.. configfile:: plugin.config

The :file:`plugin.config` file controls run-time loadable plugins available
to the Traffic Server, as well as their configuration.

文件 :file:`plugin.config` 包含了Traffic Server在运行时可加载的插件及其配置文件。

Example
=======

::

     # Comments start with a '#' and continue to the end of the line
     # Blank lines are ignored
     #
     # test-plugin.so arg1 arg2 arg3
     #
     plugins/iwx/iwx.so
     plugins/abuse/abuse.so etc/trafficserver/abuse.config
     plugins/icx/icx.so etc/trafficserver/icx.config

Each configuration line consists of a path to an ``.so`` file. This path
can either be absolute, or relative to the plugin-directory (usually
``/usr/local/libexec/trafficserver``). Such a line tells Traffic Server
to load said plugin.

配置文件的每一行包含一个到 ``.so`` 文件的路径，路径可以是绝对路径，也
可以是相对插件目录的路径（通常是 ``/usr/local/libexec/trafficserver`` ）
这样一行配置告诉Traffic Server加载对应的插件。

A plugin can have any number of configuration parameters listed. Please
refer to our `plugins' documentation <../plugins>`_ for their reference.

一个插件可以包含任意多个参数。具体请参考  `plugins' documentation <../plugins>`_ 

Plugins should only be listed *once*. The order in which the plugins are
listed is also the order in which they are chained for the processing.

插件应该只被列举一次。配置顺序即是加载顺序。
