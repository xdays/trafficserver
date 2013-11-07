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

.. configfile:: cache.config

============
cache.config(中文)
============

The :file:`cache.config` file defines how Traffic Server caches web objects. You
can add caching rules to specify the following: - Not to cache objects
from specific IP addresses - How long to pin particular objects in the
cache - How long to consider cached objects as fresh - Whether to ignore
no-cache directives from the server

:file:`cache.cofnig` 用于配置Traffic Server如何来缓存web对象。你可以像下面这样添加
缓存规则：

- 从指定IP过来的请求一律不缓存
- 指定对象保存多久
- 对象多长时间过期
- 是否忽略源站的no-cache指令

.. important::

   After you modify the :file:`cache.config` file, navigate to
   the Traffic Server bin directory; then run the :option:`traffic_line -x`
   command to apply changes. When you apply the changes to a node in a
   cluster, Traffic Server automatically applies the changes to all other
   nodes in the cluster.

.. important::

   当你修改了 :file:`cache.config` 之后，切换到Traffic Server的bin目录，然后
   执行 :option:`traffic_line -x` 命令使配置生效，当你在集群中的一个节点使配置
   生效后，其他节点自动更新配置。

Format
======

Each line in the :file:`cache.config` file contains a caching rule. Traffic
Server recognizes three space-delimited tags::

   primary_destination=value secondary_specifier=value action=value

 :file:`cache.config` 文件的每一行包含一条缓存规则，Traffic Server识别的格式为
空格分割的三个标签::

   primary_destination=value secondary_specifier=value action=value

You can use more than one secondary specifier in a rule. However, you
cannot repeat a secondary specifier. The following list shows the
possible primary destinations with allowed values.

你可以在一个规则中使用多个二级标识符，但是不能重复使用，下面的列表是所有一级
标识符和可选的值。

.. _cache-config-format-dest-domain:

``dest_domain``
   A requested domain name. Traffic Server matches the domain name of
   the destination from the URL in the request.

   请求域名，Traffic Server匹配请求URL中的的域名。

.. _cache-config-format-dest-host:

``dest_host``
   A requested hostname. Traffic Server matches the hostname of the
   destination from the URL in the request.

   请求主机名。Traffic Server匹配请求URL中的主机名。

.. _cache-config-format-dest-ip:

``dest_ip``
   A requested IP address. Traffic Server matches the IP address of the
   destination in the request.

   请求IP地址。Traffic Server匹配请求中的目的IP地址。

.. _cache-config-format-url-regex:

``url_regex``
   A regular expression (regex) to be found in a URL.

   正则匹配请求URL

The secondary specifiers are optional in the :file:`cache.config` file. The
following list shows possible secondary specifiers with allowed values.

在 :file:`cache.config` 二级标识符是可选的。下面是所有二级标识符和可选的值。

.. _cache-config-format-port:

``port``
   A requested URL port.

   请求URL中的端口号

.. _cache-config-format-scheme:

``scheme``
   A request URL protocol: http or https.

   请求URL的协议：http或者https

.. _cache-config-format-prefix:

``prefix``
   A prefix in the path part of a URL.

   URL前缀

.. _cache-config-format-suffix:

``suffix``
   A file suffix in the URL.

   URL后缀

.. _cache-config-format-method:

``method``
   A request URL method: get, put, post, trace.

   请求URL的方法：get, put, post, trace

.. _cache-config-format-time:

``time``
   A time range, such as 08:00-14:00.

   时间范围，比如8:00-14:00

.. _cache-config-format-src-ip:

``src_ip``
   A client IP address.

   客户端IP地址

The following list shows possible actions and their allowed values.

下边列表列出了所有规则和对应的值。


.. _cache-config-format-action:

``action``
   One of the following values:

   -  ``never-cache`` configures Traffic Server to never cache
      specified objects.
   -  ``ignore-no-cache`` configures Traffic Server to ignore all
      ``Cache-Control: no-cache`` headers.
   -  ``ignore-client-no-cache`` configures Traffic Server to ignore
      ``Cache-Control: no-cache`` headers from client requests.
   -  ``ignore-server-no-cache`` configures Traffic Server to ignore
      ``Cache-Control: no-cache`` headers from origin server responses.
   -  ``cluster-cache-local`` configures the cluster cache to allow for
      this content to be stored locally on every cluster node.

   可选的值如下:

   - ``never-cache`` 永远不存
   - ``ignore-no-cache`` 忽略所有 ``Cache-Control: nocache`` 的报头
   - ``ignore-client-no-cache`` 忽略客户端的 ``nocahe`` 报头
   - ``ignore-server-no-cache`` 忽略服务端的 ``nocache`` 报头
   -  ``cluster-cache-local`` 允许集群在每个节点缓存内容



.. _cache-config-format-pin-in-cache:

``pin-in-cache``
   The amount of time you want to keep the object(s) in the cache. The
   following time formats are allowed:

   -  ``d`` for days; for example: 2d
   -  ``h`` for hours; for example: 10h
   -  ``m`` for minutes; for example: 5m
   -  ``s`` for seconds; for example: 20s
   -  mixed units; for example: 1h15m20s

   在缓存中保持资源的时间，有以下几种表示格式：

   -  ``d`` 天
   -  ``h`` 时
   -  ``m`` 分
   -  ``s`` 秒
   -  mixed 混合

.. _cache-config-format-revalidate:

``revalidate``
   The amount of time object(s) are to be considered fresh. Use the
   same time formats as ``pin-in-cache``.

   资源在缓存中的寿命。格式和 ``pin-in-cache`` 一致

.. _cache-config-format-ttl-in-cache:

``ttl-in-cache``
   The amount of time object(s) are to be kept in the cache, regardless
   of Cache-Control response headers. Use the same time formats as
   pin-in-cache and revalidate .

   不管Cache-Control是什么样的，该配置控制对象保存时间，格式与 ``pin-in-cache``
   一样

Examples
========

The following example configures Traffic Server to revalidate ``gif``
and ``jpeg`` objects in the domain ``mydomain.com`` every 6 hours, and
all other objects in ``mydomain.com`` every hour. The rules are applied
in the order listed. ::

   dest_domain=mydomain.com suffix=gif revalidate=6h
   dest_domain=mydomain.com suffix=jpeg revalidate=6h
   dest_domain=mydomain.com revalidate=1h

下面的配置可以让 ``mydomain.com`` 域名下的 ``gif`` 和 ``jpeg``
资源每6个小时重新刷新校验一次，而且该域名下的的其他资源每小时刷新校验一次。
规则会以如下规则应用::

   dest_domain=mydomain.com suffix=gif revalidate=6h
   dest_domain=mydomain.com suffix=jpeg revalidate=6h
   dest_domain=mydomain.com revalidate=1h

