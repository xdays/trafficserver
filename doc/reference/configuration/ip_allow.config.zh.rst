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

===============
ip_allow.config（中文）
===============

.. configfile:: ip_allow.config

The :file:`ip_allow.config` file controls client access to the Traffic
Server proxy cache. You can specify ranges of IP addresses that are
allowed to use the Traffic Server as a web proxy cache. After you modify
the :file:`ip_allow.config` file, navigate to the Traffic Server bin
directory and run the :option:`traffic_line -x` command to apply changes. When
you apply the changes to a node in a cluster, Traffic Server
automatically applies the changes to all other nodes in the cluster.

:file: `ip_allow.config` 文件用于对客户端做访问控制。你可以指定允许请求的
客户端IP地址范围。当你修改了 :file:`ip_allow.config` 之后，切换到
Traffic Server的bin目录，然后 执行 :option:`traffic_line -x` 命令使配置生效，
当你在集群中的一个节点使配置生效后，其他节点自动更新配置。

Format
======

Each line in the :file:`ip_allow.config` file must have the following
format::

    src_ip=<range of IP addresses> action=<action> [method=<list of methods separated by '|'>]

:file:`ip_allow.config` 文件的每行格式如下::

    src_ip=<range of IP addresses> action=<action> [method=<list of methods separated by '|'>]

where src_ip is the IP address or range of IP addresses of the
client(s). The action ``ip_allow`` enables the specified client(s) to
access the Traffic Server proxy cache, and ``ip_deny`` denies the
specified client(s) to access the Traffic Server proxy cache. Multiple
method keywords can be specified (method=GET method=HEAD), or multiple
methods can be separated by an '\|' (method=GET\|HEAD). The method
keyword is optional and it is defaulted to ALL. Available methods: ALL,
GET, CONNECT, DELETE, HEAD, ICP_QUERY, OPTIONS, POST, PURGE, PUT,
TRACE, PUSH

这里的src_ip是客户端的IP地址。动作 ``ip_allow`` 为允许客户端通过缓存代理，
动作 ``ip_deny`` 为拒绝通过缓存代理。 可以指定多个方法关键字（method=GET
method=HEAD），或者多个通过'\|'分隔（method=GET\|HEAD），方法关键字可选
默认是ALL。允许的方法包括：ALL, GET, CONNECT, DELETE, HEAD, ICP_QUERY, OPTIONS,
POST, PURGE, PUT, TRACE, PUSH

By default, the :file:`ip_allow.config` file contains the following lines,
which allows all methods to localhost to access the Traffic Server proxy
cache and denies PUSH, PURGE and DELETE to all IPs (note this allows all
other methods to all IPs)::

    src_ip=127.0.0.1                                  action=ip_allow method=ALL
    src_ip=::1                                        action=ip_allow method=ALL
    src_ip=0.0.0.0-255.255.255.255                    action=ip_deny  method=PUSH|PURGE|DELETE
    src_ip=::-ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff action=ip_deny  method=PUSH|PURGE|DELETE

默认情况下 :file:`ip_allow.config`
文件包含如下行，允许所有到localhost的缓存访问请求，拒绝所有客户端的PUSH，
PURGE请求（注意这样允许所有IP的其他方法请求）::

    src_ip=127.0.0.1                                  action=ip_allow method=ALL
    src_ip=::1                                        action=ip_allow method=ALL
    src_ip=0.0.0.0-255.255.255.255                    action=ip_deny  method=PUSH|PURGE|DELETE
    src_ip=::-ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff action=ip_deny  method=PUSH|PURGE|DELETE

Examples
========

The following example enables all clients to access the Traffic Server
proxy cache::

    src_ip=0.0.0.0-255.255.255.255 action=ip_allow

下边的例子允许所有客户端的所有请求::

    src_ip=0.0.0.0-255.255.255.255 action=ip_allow

The following example allows all clients on a specific subnet to access
the Traffic Server proxy cache::

    src_ip=123.12.3.000-123.12.3.123 action=ip_allow

下边的例子允许特定的网段所有请求::

    src_ip=123.12.3.000-123.12.3.123 action=ip_allow

The following example denies all clients on a specific subnet to access
the Traffic Server proxy cache::

    src_ip=123.45.6.0-123.45.6.123 action=ip_deny

下边的例子拒绝特定网段的所有请求::

    src_ip=123.45.6.0-123.45.6.123 action=ip_deny
