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

=================
congestion.config(中文)
=================

.. configfile:: congestion.config

The :file:`congestion.config` file enables you to configure Traffic Server
to stop forwarding HTTP requests to origin servers when they become
congested, and then send the client a message to retry the congested
origin server later. After you modify the :file:`congestion.config` file,
navigate to the Traffic Server bin directory; then run the
:option:`traffic_line -x` command to apply changes. When you apply the changes
to a node in a cluster, Traffic Server automatically applies the changes
to all other nodes in the cluster. Traffic Server uses the
:file:`congestion.config` file only if you enable the `Congestion
Control <http#UsingCongestionControl>`_ option.

文件 :file:`congestion.config` 可以控制在Traffice Server拥塞的时候停止把请求
转发给源站，然后发送给客户端一个稍后重新请求拥塞服务器的信息。在修改了
 :file:`congestion.config` 文件后，进入bin目录，然后执行 `traffic_line -x` 使
配置生效。当你把配置应用到集群中的一个节点后，集群内的其他节点会自动更新配置。
只有打开了 `Congestion Control <http#UsingCongestionControl>`_ 选项后，
Traffic Server才会使用配置文件 :file:`congestion.config`


You can create rules in the congestion.config file to specify:

-  Which origin servers Traffic Server tracks for congestion.
-  The timeouts Traffic Server uses, depending on whether a server is
   congested.
-  The page Traffic Server sends to the client when a server becomes
   congested.
-  If Traffic Server tracks the origin servers per IP address or per
   hostname.

你可以在congestion.config下配置如下规则：

- 对哪些源站使用拥塞控制
- 超时时间，用来判断源站拥塞
- 当源站拥塞时返回给客户端的页面
- 是否跟踪源站的每个IP或者每个主机名

Format
======

Each line in :file:`congestion.config` must follow the format below. Traffic
Server applies the rules in the order listed, starting at the top of the
file. Traffic Server recognizes three space-delimited tags::

    primary_destination=value secondary_specifier=value action=value

文件 :file:`congestion.config` 的每一行必须遵循如下格式。Traffic Server从文件
开始按照配置顺序应用规则，Traffic Server识别的格式为 空格分割的三个标签::

    primary_destination=value secondary_specifier=value action=value

The following list shows possible primary destinations with allowed
values.

下面列表列出了所有的基础目标和允许的值。

*``dest_domain``* {#dest_domain}
    A requested domain name.

    请求域名

*``dest_host``* {#dest_host}
    A requested hostname.

    请求主机名

*``dest_ip``* {#dest_ip}
    A requested IP address.

    请求目的IP地址

*``url_regex``* {#url_regex}
    A regular expression (regex) to be found in a URL.

    正则匹配URL

The secondary specifiers are optional in the congestion.config file. The
following list shows possible secondary specifiers with allowed values.
You can use more than one secondary specifier in a rule; however, you
cannot repeat a secondary specifier.

congestion.conf文件的第二个标识符是可选的。下面列表列出了所有的二级标识符和允许的值。
你可以在一个规则中写多个二级标识符，但是不能重复。

*``port``* {#port}
    A requested URL port or range of ports.

    请求URL的端口号或者其范围

*``prefix``* {#prefix}
    A prefix in the path part of a URL.

    URL前缀

The following list shows the possible tags and their allowed values.

下面列表列出了所有的标签和允许的值。

*``max_connection_failures``* {#max_connection_failures}
    Default: ``5``
    The maximum number of connection failures allowed within the fail
    window described below before Traffic Server marks the origin server
    as congested.

    默认： ``5``
    下面描述的失败窗口的最大值，超过这个值Traffic Server就会把源站标记为拥塞。

*``fail_window``* {#fail_window}
    Default: ``120`` seconds.
    The time period during which the maximum number of connection
    failures can occur before Traffic Server marks the origin server as
    congested.

    默认： ``120`` 秒
    连接失败时间，超过这个时间Traffic Server就会把源站标记为拥塞。

*``proxy_retry_interval``* {#proxy_retry_interval}
    Default: ``10`` seconds.
    The number of seconds that Traffic Server waits before contacting a
    congested origin server again.

    默认： ``10`` 秒
    Traffic Server重新连接拥塞服务器的时间间隔。

*``client_wait_interval``* {#client_wait_interval}
    Default: ``300`` seconds.
    The number of seconds that the client is advised to wait before
    retrying the congested origin server.

    默认： ``300`` 秒
    告诉客户端多久之后连接拥塞源站的时间。

*``wait_interval_alpha``* {#wait_interval_alpha}
    Default: ``30`` seconds
    The upper limit for a random number that is added to the wait
    interval.

    默认： ``30`` 秒
    等待间隔的随机抖动时间。

*``live_os_conn_timeout``* {#live_os_conn_timeout}
    Default: ``60`` seconds.
    The connection timeout to the live (uncongested) origin server. If a
    client stops a request before the timeout occurs, then Traffic
    Server does not record a connection failure.

    默认： ``60`` 秒
    连接源站的超时时间，如果在超时时间内客户端断开连接，则不计入连接失败数。

*``live_os_conn_retries``* {#live_os_conn_retries}
    Default: ``2``
    The maximum number of retries allowed to the live (uncongested)
    origin server.

    默认： ``2``
    向不阻塞的源站发起的请求尝试数

*``dead_os_conn_timeout``* {#dead_os_conn_timeout}
    Default: ``15`` secondsj
    The connection timeout to the congested origin server.

    默认： ``15`` 秒
    向拥塞服务器发起连接的超时时间

*``dead_os_conn_retries``* {#dead_os_conn_retries}
    Default: ``1``
    The maximum number of retries allowed to the congested origin
    server.

    默认： ``1``
    允许向拥塞服务器发起的最大尝试数目

*``max_connection``* {#max_connection}
    Default: ``-1``
    The maximum number of connections allowed from Traffic Server to the
    origin server.

    默认： ``-1``
    允许向源站发起的最多连接数

*``error_page``* {#error_page}
    Default: ``"congestion#retryAfter"``
    The error page sent to the client when a server is congested. You
    must enclose the value in quotes;

    默认： ``"congestion#retryAfter"``
    当源站拥塞时向客户端发送的错误页面，必须拥引号引起来

*:file:`congestion.config`* {#congestion_scheme}
    Default: ``"per_ip"``
    Specifies if Traffic Server applies the rule on a per-host
    (``"per_host"``) or per-IP basis (``"per_ip"``). You must enclose
    the value in quotes.

    默认： ``"per_ip"``
    指定Traffic Server是基于host还是基于ip来应用规则，值必须以引号引起来


    For example: if the server ``www.host1.com`` has two IP addresses
    and you use the tag value ``"per_ip"``, then each IP address has its
    own number of connection failures and is marked as congested
    independently. If you use the tag value ``"per_host"`` and the
    server ``www.host1.com`` is marked as congested, then both IP
    addresses are marked as congested.

    举个例子：如果 ``www.host1.com`` 这个服务器由两个地址， 而你使用
    ``"per_ip"`` 方式，那么每个IP都有它自己的连接失败数，各自独立地被标记
    为拥塞。如果你拥 ``"per_ip"`` 的方式， 如果服务器 ``www.host1.com`` 标记
    为拥塞，那么每个IP都被标记为拥塞。

Examples
========

The following :file:`congestion.config` rule configures Traffic Server to
stop forwarding requests to the server ``www.host.com`` on port 80 (HTTP
traffic) if the server is congested, according to the timeouts
specified. Traffic Server uses the default tag values because no tag has
been specified.

下边的 :file:`congestion.config` 配置规则可使Traffic Server依据超时时间
来判断服务器是否拥塞，如果拥塞则不再向 ``www.host.com`` 的80端口转发请求。
由于没有配置标签，Traffic Server使用默认的标签。

::

    dest_host=www.host.com port=80

You can use one or more tags in a rule, but each tag must have one value
only. If you specify no tags in the rule, then Traffic Server uses the
default values.

你可以在一个规则中使用一个或者多个标签，但是每个标签只能由一个之。如果你没有指定
标签，Traffic Server使用默认的值。

You can override any of the default tag values by adding configuration
variables at the end of :file:`records.config` as follows:

在 :file:`records.config` 中你可以重新定义任意的标签：

::

    CONFIG proxy.config.http.congestion_control.default.tag INT|STRING value

where tag is one of the tags described in the list under
:file:`congestion.config` and value is the value you
want to use.

这里的tag就是下边 :file:`congestion.confg` 里的所列出的tag，还有其对应的值。

For example::

    CONFIG proxy.config.http.congestion_control.default.congestion_scheme STRING per_host

例如::

    CONFIG proxy.config.http.congestion_control.default.congestion_scheme STRING per_host

.. important::

    Rules in the :file:`congestion.config` file override the
    following variables in the :file:`records.config` file:

    在 :file:`congestion.config` 文件里定义的规则会覆盖在 :file:`records.config` 里
    定义的变量

::

    proxy.config.http.connect_attempts_max_retries
    proxy.config.http.connect_attempts_max_retries_dead_server
    proxy.config.http.connect_attempts_rr_retries
    proxy.config.http.connect_attempts_timeout
    proxy.config.http.down_server.cache_time
    proxy.config.http.down_server.abort_threshold

