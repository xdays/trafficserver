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
parent.config（中文）
=============

.. configfile:: parent.config

The :file:`parent.config` file identifies the parent proxies used in an
cache hierarchy. Use this file to perform the following configuration:

-  Set up parent cache hierarchies, with multiple parents and parent
   failover
-  Configure selected URL requests to bypass parent proxies

文件 :file:`parent.config` 指定了本机在缓存等级中的的父缓存。改配置文件主要
用于:

- 配置父缓存，多个父缓存以及父缓存容灾
- 配置哪些URL走父缓存

Traffic Server uses the :file:`parent.config` file only when the parent
caching option is enabled (refer to :ref:`configuring-traffic-server-to-use-a-parent-cache`).

After you modify the :file:`parent.config` file, run the :option:`traffic_line -x`
command to apply your changes. When you apply the changes to one node in
a cluster, Traffic Server automatically applies the changes to all other
nodes in the cluster.

Format
======

Each line in the :file:`parent.config` file must contain a parent caching
rule. Traffic Server recognizes three space-delimited tags: ::

    primary_destination=value secondary_specifier=value  action=value

文件 :file:`parent.config` 的每一行必须是一条父缓存规则。Traffic Server识别
以空格分隔的标签： ::

    primary_destination=value secondary_specifier=value  action=value

The following list shows the possible primary destinations and their
allowed values.

下边列举了所有的基础目标和允许的值。

.. _parent-config-format-dest-domain:

``dest_domain``
    A requested domain name.

    请求的域名

.. _parent-config-format-dest-host:

``dest_host``
    A requested hostname.

    请求的主机名

.. _parent-config-format-dest-ip:

``dest_ip``
    A requested IP address or range of IP addresses separated by a dash (-).

    请求的IP或者以减号分隔的IP范围

.. _parent-config-format-url-regex:

``url_regex``
    A regular expression (regex) to be found in a URL

    以正则匹配的URL

The secondary specifiers are optional in the :file:`parent.config` file. The
following list shows the possible secondary specifiers and their allowed
values.

文件 :file:`parent.config` 中的第二个标识符是可选的。如下列举了所有的标识符和
允许的值。

.. _parent-config-format-port:

``port``
    A requested URL port.

    请求URL的端口号

.. _parent-config-format-scheme:

``scheme``
    A request URL protocol: ``http`` or ``https``.

    请求协议类型

.. _parent-config-format-prefix:

``prefix``
    A prefix in the path part of a URL.

    URL前缀

.. _parent-config-format-suffix:

``suffix``
    A file suffix in the URL.

    URL后缀

.. _parent-config-format-method:

``method``
    A request URL method. It can be one of the following:

    -  get
    -  post
    -  put
    -  trace

    请求URL的方法。可以是如下几种：

    -  get
    -  post
    -  put
    -  trace

.. _parent-config-format-time:

``time``
    A time range, such as 08:00-14:00, during which the parent cache is
    used to serve requests.

    时间范围，如8:00-14:00，在这个时间段用父缓存来处理请求

.. _parent-config-format-src-ip:

``src_ip``
    A client IP address.

    客户端IP

The following list shows the possible actions and their allowed values.

如下列举了所有可用的动作及其允许的值。

.. _parent-config-format-parent:

``parent``
    An ordered list of parent servers. If the request cannot be handled
    by the last parent server in the list, then it will be routed to the
    origin server. You can specify either a hostname or an IP address,
    but; you must specify the port number.

    父缓存的有序列表。如果请求无法被列表里的最后一个父缓存处理就把请求
    路由给源站。你可以指定主机名或者IP地址，必须要指定端口号。

.. _parent-config-format-round-robin:

``round_robin``
    One of the following values:

    -  ``true`` - Traffic Server goes through the parent cache list in a
       round robin-based on client IP address.
    -  ``strict`` - Traffic Server machines serve requests strictly in
       turn. For example: machine ``proxy1`` serves the first request,
       ``proxy2`` serves the second request, and so on.
    -  ``false`` - Round robin selection does not occur.

    指定如下值中的一个：

    -  ``true`` - Traffic Server基于客户端IP轮训父缓存。
    -  ``strict`` - Traffic Server严格按顺序处理请求，例如： ``proxy1`` 处理
       处理第一个请求，``proxy2``处理第二个请求。
    -  ``false`` - 关闭Round robin选择。

.. _parent-config-format-go-direct:

``go_direct``
    One of the following values:

    -  ``true`` - requests bypass parent hierarchies and go directly to
       the origin server.
    -  ``false`` - requests do not bypass parent hierarchies.

    指定如下值中的一个：

    -  ``true`` - 请求经由父缓存直接到达源站
    -  ``false`` - 请求不经过父缓存

Examples
========

The following rule configures a parent cache hierarchy consisting of
Traffic Server (which is the child) and two parents, ``p1.x.com`` and
``p2.x.com``. Traffic Server forwards the requests it cannot serve to
the parent servers ``p1.x.com`` and ``p2.x.com`` in a round-robin
fashion::

    round_robin=true
    dest_domain=. method=get parent="p1.x.com:8080; p2.y.com:8080" round_robin=true

下边的规则配置了一个包含一个Traffic Server（也就是子缓存）和两个父缓存
``p1.x.com`` 和 ``p2.x.com`` 的缓存层级，Traffic Server把其不能处理的请求
以round-robin算法转发给它的父缓存 ``p1.x.com`` 和 ``p2.x.com`` ::

    round_robin=true
    dest_domain=. method=get parent="p1.x.com:8080; p2.y.com:8080" round_robin=true

The following rule configures Traffic Server to route all requests
containing the regular expression ``politics`` and the path
``/viewpoint`` directly to the origin server (bypassing any parent
hierarchies): ``url_regex=politics prefix=/viewpoint go_direct=true``

下边的规则配置使Traffic Server把所有URL配置 ``politics`` 正则和以
``/viewpoint`` 为前缀的所有请求转发给源站（通过父缓存）: 
``url_regex=politics prefix=/viewpoint go_direct=true``

Every line in the :file:`parent.config` file must contain either a
``parent=`` or ``go_direct=`` directive.

文件 :file:`parent.config` 中的每一行必须包含 ``parent=`` 或者 ``go_direct=`` 中
的一个。
