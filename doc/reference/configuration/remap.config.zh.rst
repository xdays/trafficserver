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

============
remap.config（中文）
============

.. configfile:: remap.config

.. toctree:: 
   :maxdepth: 2


The :file:`remap.config` file contains mapping rules that Traffic Server
uses to perform the following actions:

-  Map URL requests for a specific origin server to the appropriate
   location on Traffic Server when Traffic Server acts as a reverse
   proxy for that particular origin server
-  Reverse-map server location headers so that when origin servers
   respond to a request with a location header that redirects the client
   to another location, the clients do not bypass Traffic Server
-  Redirect HTTP requests permanently or temporarily without Traffic
   Server having to contact any origin servers

文件 :file:`remap.config` 包含Traffic Server用于如下动作的映射规则：

-  当Traffic Server用于反向代理时，将请求到特定的源站的URL映射到合适的位置
-  反向映射源站服务器响应中的location字段，服务器中的location报头是用于
   重定向客户端到另一个位置，客户端再请求时就不会经过Traffic Server
-  当Traffic Server无法连接源站时，暂时或者永久重定向HTTP请求。

Refer to  :ref:`reverse-proxy-and-http-redirects`, for information about
redirecting HTTP requests and using reverse proxy.

关于重定向HTTP请求和用于反向代理请参考 :ref:`reverse-proxy-and-http-redirects`

After you modify the :file:`remap.config` run the
:option:`traffic_line -x` to apply the changes. When you apply the
changes to one node in a cluster, Traffic Server automatically applies
the changes to all other nodes in the cluster.

修改了 :file:`remap.config` 文件之后执行 :option:`traffic_line -x` 以让配置
生效，当改变了集群中的一台Traffic Server配置后，集群中的其他节点自动生效。

Format
======

Each line in the :file:`remap.config` file must contain a mapping rule. Empty lines,
or lines starting with ``#`` are ignored. Each line can be broken up into multiple
lines for better readability by using ``\`` as continuation marker.

文件 :file:`remap.config` 中的每一行必须包含一个映射规则。空行或者以 ``#`` 开头的行
会被忽略。较长的行可以用  ``\`` 分隔成多行。

Traffic Server recognizes three space-delimited fields: ``type``,
``target``, and ``replacement``. The following list describes the format of each field.

Traffic Server识别以空格分隔的 ``type``，`target`` 和 ``replacement`` 。 下边描述了
每个字段的格式。

.. _remap-config-format-type:

``type``
    Enter one of the following:

    -  ``map`` --translates an incoming request URL to the appropriate
       origin server URL.

    -  ``reverse_map`` --translates the URL in origin server redirect
       responses to point to the Traffic Server.

    -  ``redirect`` --redirects HTTP requests permanently without having
       to contact the origin server. Permanent redirects notify the
       browser of the URL change (by returning an HTTP status code 301)
       so that the browser can update bookmarks.

    -  ``redirect_temporary`` --redirects HTTP requests temporarily
       without having to contact the origin server. Temporary redirects
       notify the browser of the URL change for the current request only
       (by returning an HTTP status code 307).

    -  ``map`` --将请求URL转换成源站URL

    -  ``reverse_map`` --将源站的重定向响应转换为指向Traffic Server的

    -  ``redirect`` --当源站不可达时永久重定向HTTP请求。永久重定向告知浏览器
       URL改变了（通过301响应码），浏览器更新书签。

    -  ``redirect_temporary`` --当源站不可达时临时重定向HTTP请求。临时重定向
       告知浏览器URL对于这次请求来说变更了（通过307响应码）。

       .. note: use the ``regex_`` prefix to indicate that the line has a regular expression (regex).

.. _remap-config-format-target:

``target``
    Enter the origin ("from") URL. You can enter up to four components: ::

        scheme://host:port/path_prefix

    where ``scheme`` is ``http``.

    指定源URL。你最多可以指定四个部分： ::

        scheme://host:port/path_prefix

    这里的 ``scheme`` 是 ``http`` 。


.. _remap-config-format-replacement:

``replacement``
    Enter the origin ("from") URL. You can enter up to four components: ::

        scheme://host:port/path_prefix

    where ``scheme`` can be ``http`` or ``https``.

    指定源URL。你最多可以指定四个部分： ::

        scheme://host:port/path_prefix

    这里的 ``scheme`` 可以是 ``http`` 或者 ``https`` 。

.. _remap-config-precedence:

Precedence
==========

Remap rules are not processed top-down, but based on an internal
priority

1. ``map`` and ``reverse_map``
2. ``regex_map``
3. ``redirect`` and ``redirect_temporary``
4. ``regex_redirect`` and ``regex_redirect_temporary``

映射规则并非自上而下处理，而是有内部的优先级

1. ``map`` 和 ``reverse_map``
2. ``regex_map``
3. ``redirect`` 和 ``redirect_temporary``
4. ``regex_redirect`` 和 ``regex_redirect_temporary``


Match-All
=========

A map rule with a single ``/`` acts as a wildcard, it will match any
request. This should be use with care, and certainly only once at the
end of the remap.config file. E.g.

::

    map / http://all.example.com

只包含一个  ``/`` 字符的映射规则相当于通配符，会匹配所有的请求。所以应该谨慎
使用，而且只在remap.config文件的最后使用

::

    map / http://all.example.com

Examples
--------

The following section shows example mapping rules in the
:file:`remap.config` file.

下边小结示例 :file:`remap.config` 文件中的映射规则。

Reverse Proxy Mapping Rules
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following example shows a map rule that does not specify a path
prefix in the target or replacement: ::

    map http://www.x.com/ http://server.hoster.com/
    reverse_map http://server.hoster.com/ http://www.x.com/

下边的例子展示了在target和replacement中没有使用路径前缀的例子： ::

    map http://www.x.com/ http://server.hoster.com/
    reverse_map http://server.hoster.com/ http://www.x.com/

This rule results in the following translations:

这条规则使用如下转换规则：

================================================ ========================================================
Client Request                                   Translated Request
================================================ ========================================================
``http://www.x.com/Widgets/index.html``          ``http://server.hoster.com/Widgets/index.html``
``http://www.x.com/cgi/form/submit.sh?arg=true`` ``http://server.hoster.com/cgi/form/submit.sh?arg=true``
================================================ ========================================================

The following example shows a map rule with path prefixes specified in
the target: ::

    map http://www.y.com/marketing/ http://marketing.y.com/
    reverse_map http://marketing.y.com/ http://www.y.com/marketing/
    map http://www.y.com/sales/ http://sales.y.com/
    reverse_map http://sales.y.com/ http://www.y.com/sales/
    map http://www.y.com/engineering/ http://engineering.y.com/
    reverse_map http://engineering.y.com/ http://www.y.com/engineering/
    map http://www.y.com/stuff/ http://info.y.com/
    reverse_map http://info.y.com/ http://www.y.com/stuff/

如下的规则示例在target中指定前缀 ::

    map http://www.y.com/marketing/ http://marketing.y.com/
    reverse_map http://marketing.y.com/ http://www.y.com/marketing/
    map http://www.y.com/sales/ http://sales.y.com/
    reverse_map http://sales.y.com/ http://www.y.com/sales/
    map http://www.y.com/engineering/ http://engineering.y.com/
    reverse_map http://engineering.y.com/ http://www.y.com/engineering/
    map http://www.y.com/stuff/ http://info.y.com/
    reverse_map http://info.y.com/ http://www.y.com/stuff/

These rules result in the following translations:

这条规则使用如下转换规则：

=============================================================== ==========================================================
Client Request                                                  Translated Request
=============================================================== ==========================================================
``http://www.y.com/marketing/projects/manhattan/specs.html``    ``http://marketing.y.com/projects/manhattan/specs.html``
``http://www.y.com/stuff/marketing/projects/boston/specs.html`` ``http://info.y.com/marketing/projects/boston/specs.html``
``http://www.y.com/engineering/marketing/requirements.html``    ``http://engineering.y.com/marketing/requirements.html``
=============================================================== ==========================================================

The following example shows that the order of the rules matters: ::

    map http://www.g.com/ http://external.g.com/
    reverse_map http://external.g.com/ http://www.g.com/
    map http://www.g.com/stuff/ http://stuff.g.com/
    reverse_map http://stuff.g.com/ http://www.g.com/stuff/

如下的规则是一个展示映射规则的优先级的例子 ::

    map http://www.g.com/ http://external.g.com/
    reverse_map http://external.g.com/ http://www.g.com/
    map http://www.g.com/stuff/ http://stuff.g.com/
    reverse_map http://stuff.g.com/ http://www.g.com/stuff/

These rules result in the following translation.

这条规则使用如下转换规则：

================================ =====================================
Client Request                   Translated Request
================================ =====================================
``http://www.g.com/stuff/a.gif`` ``http://external.g.com/stuff/a.gif``
================================ =====================================

In the above examples, the second rule is never applied because all URLs
that match the second rule also match the first rule. The first rule
takes precedence because it appears earlier in the :file:`remap.config`
file.

在上面的例子中，因为被第二条匹配到URL都被第一条规则匹配到，所以第二条规则
永远不会生效。第一条规则生效是以为其在文件 :file:`remap.config` 中更早的出现。

The following example shows a mapping with a path prefix specified in
the target and replacement::

    map http://www.h.com/a/b/ http://server.h.com/customers/x/y
    reverse_map http://server.h.com/customers/x/y/ http://www.h.com/a/b/

如下规则展示了在target和replacement中使用路径前缀::

    map http://www.h.com/a/b/ http://server.h.com/customers/x/y
    reverse_map http://server.h.com/customers/x/y/ http://www.h.com/a/b/

This rule results in the following translation.

这条规则使用如下转换规则：

===================================== ==================================================
Client Request                        Translated Request
===================================== ==================================================
``http://www.h.com/a/b/c/d/doc.html`` ``http://server.h.com/customers/x/y/c/d/doc.html``
``http://www.h.com/a/index.html``     ``Translation fails``
===================================== ==================================================

The following example shows reverse-map rules::


    map http://www.x.com/ http://server.hoster.com/x/
    reverse_map http://server.hoster.com/x/ http://www.x.com/

如下规则展示了反向映射的规则::

    map http://www.x.com/ http://server.hoster.com/x/
    reverse_map http://server.hoster.com/x/ http://www.x.com/

These rules result in the following translations.

这条规则使用如下转换规则：

================================ =====================================
Client Request                   Translated Request
================================ =====================================
``http://www.x.com/Widgets``     ``http://server.hoster.com/x/Widgets``
================================ =====================================

 

================================ ======================================= =============================
Client Request                   Origin Server Header                    Translated Request
================================ ======================================= =============================
``http://www.x.com/Widgets``     ``http://server.hoster.com/x/Widgets/`` ``http://www.x.com/Widgets/``
================================ ======================================= =============================

When acting as a reverse proxy for multiple servers, Traffic Server is
unable to route to URLs from older browsers that do not send the
``Host:`` header. As a solution, set the variable :ts:cv:`proxy.config.header.parse.no_host_url_redirect`
in the :file:`records.config` file to the URL to which Traffic Server will redirect
requests without host headers.

当Traffic Server用于多个服务器的反向代理时，有些旧的浏览器不携带 ``Host:`` 报头，Traffic Server就
不能路由这些请求。一个解决办法是在  :file:`records.config` 文件中设置  :ts:cv:`proxy.config.header.parse.no_host_url_redirect`
然后所有没有host报头的的请求都转发给这个host

Redirect Mapping Rules
~~~~~~~~~~~~~~~~~~~~~~

The following rule permanently redirects all HTTP requests for
``www.company.com`` to ``www.company2.com``: ::

    redirect http://www.company.com/ http://www.company2.com/

如下规则永久重定向 ``www.company.com`` 到 ``www.company2.com``: ::

    redirect http://www.company.com/ http://www.company2.com/

The following rule *temporarily* redirects all HTTP requests for
``www.company1.com`` to ``www.company2.com``: ::

    redirect_temporary http://www.company1.com/ http://www.company2.com/

如下规则 *临时重定向* ``www.company1.com`` 到 ``www.company2.com``: ::

    redirect_temporary http://www.company1.com/ http://www.company2.com/

.. _remap-config-regex:

Regular Expression (regex) Remap Support
========================================

Regular expressions can be specified in remapping rules, with the
limitations below:

-  Only the ``host`` field can contain a regex; the ``scheme``,
   ``port``, and other fields cannot. For path manipulation via regexes,
   use the ``regex_remap`` plugin.
-  The number of capturing subpatterns is limited to 9. This means that
   ``$0`` through ``$9`` can be used as subtraction placeholders (``$0``
   will be the entire input string).
-  The number of substitutions in the expansion string is limited to 10.
-  There is no ``regex_`` equivalent to ``reverse_remap``, so when using
   ``regex_remap`` you should make sure the reverse path is clear by
   setting (:ts:cv:`proxy.config.url_remap.pristine_host_hdr`)

正则表达式可用于反向映射规则中，但有如下限制：

-  只有  ``host`` 字段可以包含正则； ``scheme`` ， ``port`` 等其他字段不能。对于
   需要通过正则生成路径的情况可以使用 ``regex_remap`` 插件。
-  最多可以捕捉9个子路径，也就是说从0到9可用于位置替换（ ``$0`` 表示所有的输入）
-  最多可以有10次替换
-  没有  ``reverse_remap`` 对应的 ``regex_`` ，所以在使用 ``regex_remap`` 要
   确定反向路径已经通过 (:ts:cv:`proxy.config.url_remap.pristine_host_hdr`)清除

Examples
--------

::

    regex_map http://x([0-9]+).z.com/ http://real-x$1.z.com/
    regex_redirect http://old.(.*).z.com http://new.$1.z.com

.. _remap-config-plugin-chaining:

Plugin Chaining
===============

Plugins can be configured to be evaluated in a specific order, passing
the results from one in to the next (unless a plugin returns 0, then the
"chain" is broken).

通过一个一个传递返回值（除非插件返回0, 这样链中断），插件可以以特定顺序执行

Examples
--------

::

    map http://url/path http://url/path @plugin=/etc/traffic_server/config/plugins/plugin1.so @pparam=1 @pparam=2 @plugin=/etc/traffic_server/config/plugins/plugin2.so @pparam=3

This will pass "1" and "2" to plugin1.so and "3" to plugin2.so

将会传递 "1" 和 "2" 给plugin1.so， 传递 "3" 给 plugin2.so

.. _remap-config-named-filters:

Named Filters
=============

Named filters can be created and applied to blocks of mappings using
the ``.definefilter``, ``.activatefilter``, and ``.deactivatefilter``
directives. Named filters must be defined using ``.definefilter`` before
being used. Once defined, ``.activatefilter`` can used to activate a
filter for all mappings that follow until deactivated with
``.deactivatefilter``.

命名过滤器可以通过 ``.definefilter``, ``.activatefilter``, 和 ``.deactivatefilter``
被创建并应用于一组映射之上。 命名过滤器在使用前必须通过 ``.definefilter`` 定义。
一旦定义好之后， ``.activatefilter`` 可用于激活对所有映射规则的过滤，直到通过
指令 ``.deactivatefilter`` 关闭。

Examples
--------

::

    .definefilter disable_delete_purge @action=deny @method=delete @method=purge
    .definefilter internal_only @action=allow @src_ip=192.168.0.1-192.168.0.254 @src_ip=10.0.0.1-10.0.0.254

    .activatefilter disable_delete_purge

    map http://foo.example.com/ http://bar.example.com/

    .activatefilter internal_only
    map http://www.example.com/admin http://internal.example.com/admin
    .deactivatefilter internal_only

    map http://www.example.com/ http://internal.example.com/

The filter `disable_delete_purge` will be applied to all of the
mapping rules. (It is activated before any mappings and is never
deactivated.) The filter `internal_only` will only be applied to the
second mapping.

过滤器 `disable_delete_purge` 可以应用到所有的映射。（在所有映射规则定义前被激活并且没有关闭）
过滤器 `internal_only` 只会用于第二个映射规则。
