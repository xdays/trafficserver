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

==============
records.config（中文）
==============

.. configfile:: records.config

The :file:`records.config` file is a list of configurable variables used by
the Traffic Server software. Many of the variables in the
:file:`records.config` file are set automatically when you set configuration
options in Traffic Line or Traffic Shell. After you modify the
:file:`records.config` file,
run the command :option:`traffic_line -x` to apply the changes.
When you apply changes to one node in a cluster, Traffic Server
automatically applies the changes to all other nodes in the cluster.

文件 :file:`records.config` 包含了Traffic Server试用的可配置的变量。这个文件里
好多的变量会在通过Traffic Line或者Traffic Shell设置时自动设置。在修改
:file:`records.config` 文件之后，执行  :option:`traffic_line -x` 可让配置生效
当你修改了集群中的一个节点后，集群中的其他节点自动生效。

Format
======

Each variable has the following format::

   SCOPE variable_name DATATYPE variable_value

每个变量有如下格式::

   SCOPE variable_name DATATYPE variable_value

where

这里

``SCOPE`` is related to clustering and is either ``CONFIG`` (all members of
the cluster) or ``LOCAL`` (only the local machine)

``SCOPE`` 和集群有关，要么是 ``CONFIG`` （集群所有的成员）或者 ``LOCAL`` 
（仅本机）

``DATATYPE`` is one of ``INT`` (integer), ``STRING`` (string), ``FLOAT``
(floating point).

``DATATYPE`` 是 ``INT`` （整数）， ``STRING`` （字符串）， ``FLOAT`` （浮点数）
之一

:
A variable marked as ``Deprecated`` is still functional but should be avoided
as it may be removed in a future release without warning.

一个标记为 ``Deprecated`` 的变量依然有效但是应该避免使用，因为将来的版本中很
可能会被删除，没有提示说明。

A variable marked as ``Reloadable`` can be updated via the command::

   traffic_line -x

一个标记为 ``Reloadable`` 的变量可以通过如下命令更新::

   traffic_line -x

``INT`` type configurations are expressed as any normal integer,
e.g. *32768*. They can also be expressed using more human readable values
using standard prefixes, e.g. *32K*. The following prefixes are supported
for all ``INT`` type configurations

   - ``K`` Kilobytes (1024 bytes)
   - ``M`` Megabytes (1024^2 or 1,048,576 bytes)
   - ``G`` Gigabytes (1024^3 or 1,073,741,824 bytes
   - ``T`` Terabytes (1024^4 or 1,099,511,627,776 bytes)

``INT`` 类型配置可以是正常的整数，例如 *32768* 。也可是可读性好的值加上标准
后缀。 例如 *32K* 。如下的后缀支持 ``INT`` 类型的配置

   - ``K`` Kilobytes (1024 bytes)
   - ``M`` Megabytes (1024^2 or 1,048,576 bytes)
   - ``G`` Gigabytes (1024^3 or 1,073,741,824 bytes
   - ``T`` Terabytes (1024^4 or 1,099,511,627,776 bytes)

.. note::

    Traffic Server currently writes back configurations to disk periodically,
    and when doing so, will not preserve the prefixes.

    Traffic Server 目前自动把磁盘写回磁盘，当执行这种操作时，后缀不会保留。

Examples
========

In the following example, the variable `proxy.config.proxy_name`_ is
a ``STRING`` datatype with the value ``my_server``. This means that the
name of the Traffic Server proxy is ``my_server``. ::

   CONFIG proxy.config.proxy_name STRING my_server

下边的例子，变量 `proxy.config.proxy_name`_ 是一个 ``STRING`` 类型，值为
``my_server`` 。 意思是Traffic Server代理的名称为 ``my_server`` ::

   CONFIG proxy.config.proxy_name STRING my_server

If the server name should be ``that_server`` the line would be ::

   CONFIG proxy.config.proxy_name STRING that_server

如果服务器名称应该为 ``that_server`` 那么一行应该是::

   CONFIG proxy.config.proxy_name STRING that_server

In the following example, the variable ``proxy.config.arm.enabled`` is
a yes/no flag. A value of ``0`` (zero) disables the option; a value of
``1`` enables the option. ::

   CONFIG proxy.config.arm.enabled INT 0

下边的例子， 变量 ``proxy.config.arm.enabled`` 是一个是非标志。如果值是
``0`` 就关闭选项，如果值是 ``1`` 就开启选项。::

   CONFIG proxy.config.arm.enabled INT 0

In the following example, the variable sets the cluster startup timeout
to 10 seconds. ::

   CONFIG proxy.config.cluster.startup_timeout INT 10

如下的例子， 变量设置集群启动的超时时间为10s::

   CONFIG proxy.config.cluster.startup_timeout INT 10

The last examples configures a 64GB RAM cache, using a human readable
prefix. ::

   CONFIG proxy.config.cache.ram_cache.size INT 64G

最后一个例子，通过制定一个单位配置64G的内存缓存::

   CONFIG proxy.config.cache.ram_cache.size INT 64G

Environment Overrides
=====================

Every :file:`records.config` configuration variable can be overridden
by a corresponding environment variable. This can be useful in
situations where you need a static :file:`records.config` but still
want to tweak one or two settings. The override variable is formed
by converting the :file:`records.config` variable name to upper
case, and replacing any dot separators with an underscore.

文件 :file:`records.config` 中的每个变量都可以被对应的环境变量覆盖。这样
当你需要一个静态的 :file:`records.config` 文件，但是又想改变一两个参数的时候
就很有用。覆盖的环境变量格式是以对应变量的大写，然后将点替换成下划线。

Overriding a variable from the environment is permanent and will
not be affected by future configuration changes made in
:file:`records.config` or applied with :program:`traffic_line`.

从环境变量覆盖一个变量是永久性的，不受将来对 :file:`records.config` 文件的
改变或者执行 :program:`traffic_line` 的影响。

For example, we could override the `proxy.config.product_company`_ variable
like this::

   $ PROXY_CONFIG_PRODUCT_COMPANY=example traffic_cop &
   $ traffic_line -r proxy.config.product_company

例如，我们可以这样覆盖 `proxy.config.product_company`_ 文件::

   $ PROXY_CONFIG_PRODUCT_COMPANY=example traffic_cop &
   $ traffic_line -r proxy.config.product_company

.. _configuration-variables:

Configuration Variables
=======================

The following list describes the configuration variables available in
the :file:`records.config` file.

如下列表描述了在 :file:`records.config` 文件中的配置变量。

System Variables
----------------

.. ts:cv:: CONFIG proxy.config.product_company STRING Apache Software Foundation

   The name of the organization developing Traffic Server.

   开发 Traffic Server 的公司

.. ts:cv:: CONFIG proxy.config.product_vendor STRING Apache

   The name of the vendor providing Traffic Server.

   提供Traffic Server的供应商

.. ts:cv:: CONFIG proxy.config.product_name STRING Traffic Server

   The name of the product.

   产品的名称

.. ts:cv:: CONFIG proxy.config.proxy_name STRING ``build_machine``
   :reloadable:

   The name of the Traffic Server node.

   Traffic Server节点名称

.. ts:cv:: CONFIG proxy.config.bin_path STRING bin

   The location of the Traffic Server ``bin`` directory.

   Traffic Server的 ``bin`` 目录路径

.. ts:cv:: CONFIG proxy.config.proxy_binary STRING traffic_server

   The name of the executable that runs the :program:`traffic_server` process.

   程序  :program:`traffic_server` 对应的可执行文件名称

.. ts:cv:: CONFIG proxy.config.proxy_binary_opts STRING -M

   The command-line options for starting Traffic Server.

   启动Traffic Server的命令行选项

.. ts:cv:: CONFIG proxy.config.manager_binary STRING traffic_manager

   The name of the executable that runs the :program:`traffic_manager` process.

   程序 :program:`traffic_manager` 对应的可执行文件名称

.. ts:cv:: CONFIG proxy.config.env_prep STRING

   The script executed before the :program:`traffic_manager` process spawns
   the :program:`traffic_server` process.

   在 :program:`traffic_manager` 启动 :program:`traffic_server` 之前执行的脚本

.. ts:cv:: CONFIG proxy.config.config_dir STRING config

   The directory that contains Traffic Server configuration files.

   包含Traffic Server的配置文件的目录

.. ts:cv:: CONFIG proxy.config.alarm_email STRING
   :reloadable:

   The email address to which Traffic Server sends alarm messages.

   Traffic Server发送告警邮件的邮箱

During a custom Traffic Server installation, you can specify the email address;
otherwise, Traffic Server uses the Traffic Server user account name as the default value for this variable.

在自定义安装Traffic Server时，你可以指定邮箱地址；否则， Traffic Server使用启动程序的用户

.. ts:cv:: CONFIG proxy.config.syslog_facility STRING LOG_DAEMON

   The facility used to record system log files. Refer to :ref:`understanding-traffic-server-log-files`.

   记录系统日志的设备，参考 :ref:`understanding-traffic-server-log-files`

.. ts:cv:: CONFIG proxy.config.cop.core_signal INT 0

   The signal sent to :program:`traffic_cop`'s managed processes to stop them.

   发送给 :program:`traffic_cop` 管理程序的终止信号

A value of ``0`` means no signal will be sent.

``0`` 表示不发送信号。

.. ts:cv:: CONFIG proxy.config.cop.linux_min_swapfree_kb INT 10240

   The minimum amount of free swap space allowed before Traffic Server stops the :program:`traffic_server` and :program:`traffic_manager` processes to
   prevent the system from hanging. This configuration variable applies if swap is enabled in Linux 2.2 only.

   在Traffic Server停止 :program:`traffic_server` 和 :program:`traffic_manager`
   进程之前，可以使用的最小swap空间大小。这样可以避免系统挂起。这个配置变量
   只有当Linux 2.2系统开启swap才生效。

.. ts:cv:: CONFIG proxy.config.output.logfile  STRING traffic.out

   The name and location of the file that contains warnings, status messages, and error messages produced by the Traffic Server
   processes. If no path is specified, then Traffic Server creates the file in its logging directory.

   保存告警，状态信息和由Traffic Server产生的错误日志的文件路径名，
   如果没有制定路径，Traffic Server会在其日志目录创建文件。

.. ts:cv:: CONFIG proxy.config.snapshot_dir STRING snapshots

   The directory in which Traffic Server stores configuration snapshots on the local system. Unless you specify an absolute path, this
   directory is located in the Traffic Server ``config`` directory.

   Traffic Server保存配置镜像的目录，除非你指定绝对路径，否则这个路径就是
   Traffic Server的 ``config`` 目录

.. ts:cv:: CONFIG proxy.config.exec_thread.autoconfig INT 1

   When enabled (the default, ``1``), Traffic Server scales threads according to the available CPU cores. See the config option below.

   当开启是（默认开启），Traffic Server根据CPU核数来自动增加县城，具体看下面配置

.. ts:cv:: CONFIG proxy.config.exec_thread.autoconfig.scale FLOAT 1.5

   Factor by which Traffic Server scales the number of threads. The multiplier is usually the number of available CPU cores. By default
   this is scaling factor is ``1.5``.

   Traffic Server增加线程的系数，因数通常是CPU的核数，默认系数是 ``1.5``

.. ts:cv:: CONFIG proxy.config.exec_thread.limit INT 2

   *XXX* What does this do?

   *XXX* 这个是干啥的？

.. ts:cv:: CONFIG proxy.config.accept_threads INT 0

   When enabled (``1``), runs a separate thread for accept processing. If disabled (``0``), then only 1 thread can be created.

   当开启时( ``1`` )，给接受进程单独开一个独立的线程，如果关闭(``0``)，只创建一个线程。

.. ts:cv:: CONFIG proxy.config.thread.default.stacksize  INT 1096908

   The new default thread stack size, for all threads. The original default is set at 1 MB.

   新的线程栈大小，对于所有县城，最初默认大小是1MB

.. ts:cv: CONFIG proxy.config.exec_thread.affinity INT 0

   Bind threads to specific CPUs or CPU cores.

   将线程绑定到特定的CPU和CPU核上

===== ====================
Value Effect
===== ====================
1     assign threads to sockets
2     assign threads to real cores
3     assign threads to logical cores
0     don't assign threads to any cores
===== ====================

===== ====================
值    效果
===== ====================
1     将线程分配到槽上
2     将线程分配到真实的核上
3     将线程分配到逻辑核上
0     不将线程分配到任何核上
===== ====================

.. note::

   This option only has an affect when Traffic Server has been compiled with ``--enable-hwloc``.

   这个选项只有在编译Traffic Server的时候开启 ``--enable-hwloc`` 才有效

Network
=======

.. ts:cv:: LOCAL proxy.local.incoming_ip_to_bind STRING 0.0.0.0 ::

   Controls the global default IP addresses to which to bind proxy server ports. The value is a space separated list of IP addresses, one per supported IP address family (currently IPv4 and IPv6).

   指定绑定地址，每个IP用空格分隔，目前支持IPv4和IPv6

Unless explicitly specified in `proxy.config.http.server_ports`_ the server port will be bound to one of these addresses, selected by IP address family. The built in default is any address. This is used if no address for a family is specified. This setting is useful if most or all server ports should be bound to the same address.

除非特殊指定 `proxy.config.http.server_ports`_ 指定的端口会被绑定到所有这里指定的地址上。如果指定的IP类型的IP没有有指定，默认是被绑定到所有的地址上。这点很在所有服务器的端口要被绑定到同一个IP地址上时很有帮助。

.. note::

   This is ignored for inbound transparent server ports because they must be able to accept connections on arbitrary IP addresses.

   对于流入事务这个配置会被忽略，因为所有端口都应该能接受连接。

.. topic:: Example

   Set the global default for IPv4 to ``192.168.101.18`` and leave the global default for IPv6 as any address.::

      LOCAL proxy.local.incoming_ip_to_bind STRING 192.168.101.18

   配置全局的IPv4地址 ``192.168.101.18`` 然后保持IPv6为默认。::

      LOCAL proxy.local.incoming_ip_to_bind STRING 192.168.101.18

.. topic:: Example

   Set the global default for IPv4 to ``191.68.101.18`` and the global default for IPv6 to ``fc07:192:168:101::17``.::

      LOCAL proxy.local.incoming_ip_to_bind STRING 192.168.101.18 fc07:192:168:101::17

   配置IPv4默认地址  ``191.68.101.18`` 和IPv6默认地址 ``fc07:192:168:101::17``.::

      LOCAL proxy.local.incoming_ip_to_bind STRING 192.168.101.18 fc07:192:168:101::17

.. ts:cv:: LOCAL proxy.local.outgoing_ip_to_bind STRING 0.0.0.0 ::

   This controls the global default for the local IP address for outbound connections to origin servers. The value is a list of space separated IP addresses, one per supported IP address family (currently IPv4 and IPv6).

   指定到源站的出口流量的绑定地址。每个IP用空格分隔，目前支持IPv和IPv6。

   Unless explicitly specified in `proxy.config.http.server_ports`_ one of these addresses, selected by IP address family, will be used as the local address for outbound connections. This setting is useful if most or all of the server ports should use the same outbound IP addresses.

   除非特殊指定 `proxy.config.http.server_ports`_ 指定的端口会被绑定到所有这里指定的地址上。如果指定的IP类型的IP没有有指定，默认是被绑定到所有的地址上。这点很在所有服务器的出口流量要被绑定到同一个IP地址上时很有帮助。

.. note::

   This is ignored for outbound transparent ports as the local outbound address will be the same as the client local address.

   这个配置对于返回给客户端的本地地址不起作用。

.. topic:: Example

   Set the default local outbound IP address for IPv4 connectionsn to ``192.168.101.18``.::

      LOCAL proxy.local.outgoing_ip_to_bind STRING 192.168.101.18

    默认的出口流量地址配置为 ``192.168.101.18``.::

      LOCAL proxy.local.outgoing_ip_to_bind STRING 192.168.101.18

.. topic:: Example

   Set the default local outbound IP address to ``192.168.101.17`` for IPv4 and ``fc07:192:168:101::17`` for IPv6.::

      LOCAL proxy.local.outgoing_ip_to_bind STRING 192.168.101.17 fc07:192:168:101::17

   默认的出口流量地址配置为 ``192.168.101.17`` 和 ``fc07:192:168:101::17``。::

      LOCAL proxy.local.outgoing_ip_to_bind STRING 192.168.101.17 fc07:192:168:101::17

Cluster
=======

.. ts:cv:: LOCAL proxy.local.cluster.type INT 3

   Sets the clustering mode:

===== ====================
Value Effect
===== ====================
1     full-clustering mode
2     management-only mode
3     no clustering
===== ====================

   配置集群模式：

===== ====================
Value Effect
===== ====================
1     完全集群模式
2     仅管理集群模式
3     关闭集群
===== ====================

.. ts:cv:: CONFIG proxy.config.cluster.rsport INT 8088

   The reliable service port. The reliable service port is used to send configuration information between the nodes in a cluster. All nodes
   in a cluster must use the same reliable service port.

   可靠服务端口。该端口用于在集群的节点之间传递配置信息，集群中所有的节点必须使用相同的服务端口。

.. ts:cv:: CONFIG proxy.config.cluster.threads INT 1

   The number of threads for cluster communication. On heavy cluster, the number should be adjusted. It is recommend that take the thread
   CPU usage as a reference when adjusting.

   集群通信的线程数目。在高负荷的集群中，该值需要调整，建议参考CPU使用率来调整这个值。

.. ts:cv:: CONFIG proxy.config.clustger.ethernet_interface STRING

   Set the interface to use for cluster communications.

   设置用于集群通信的接口

.. ts:cv:: CONFIG proxy.config.http.cache.cluster_cache_local INT 0

   This turns on the local caching of objects in cluster mode. The point of
   this is to allow for popular or **hot** content to be cached on all nodes
   in a cluster. Be aware that the primary way to configure this behavior is
   via the :file:`cache.config` configuration file using
   ``action=cluster-cache-local`` directives.

   开启集群模式的本地缓存。这样做是因为可以把热的资源缓存在集群的所有节点上，
   注意配置该功能的基本方法是在 :file:`cache.config`  文件中指定 ``action=cluster-cache-local`` 指令

   This particular :file:`records.config` configuration can be controlled per
   transaction or per remap rule. As such, it augments the
   :file:`cache.config` directives, since you can turn on the local caching
   feature without complex regular expression matching.

   这个  :file:`records.config` 特殊配置可以给予请求或者remap规则来配置。
   因此该指定会增加 :file:`cache.config` 文件中的指令，
   这样你就不需要添加复杂的正则规则来实现本地缓存

   This implies that turning this on in your global :file:`records.config` is
   almost never what you want; instead, you want to use this either via
   e.g. ``conf_remap.so`` overrides for a certain remap rule, or through a
   custom plugin using the appropriate APIs.

   也就是说你几乎永远不需要在你的全局配置文件  :file:`records.config` 添加此配置：
   你可以通过  ``conf_remap.so`` 来覆盖一个特定的remap规则，或者通过合适的API来实现


Local Manager
=============

.. ts:cv:: CONFIG proxy.config.lm.sem_id INT 11452

   The semaphore ID for the local manager.

   本地管理进程的信号ID

.. ts:cv:: CONFIG proxy.config.admin.autoconf_port INT 8083

   The autoconfiguration port.

   自动配置端口

.. ts:cv:: CONFIG proxy.config.admin.number_config_bak INT 3

   The maximum number of copies of rolled configuration files to keep.

   保存备份配置文件的份数

.. ts:cv:: CONFIG proxy.config.admin.user_id STRING nobody

   Option used to specify who to run the :program:`traffic_server` process as; also used to specify ownership of config and log files.

   运行  :program:`traffic_server` 进程的用户， 也用于指定配置文件和日志文件的所有泽。

The nonprivileged user account designated to Traffic Server.

指定给Traffic Server的非特权用户

As of version 2.1.1 if the user_id is prefixed with pound character (#) the remaining of the string is considered to be
a `numeric user identifier <http://en.wikipedia.org/wiki/User_identifier>`_. If the value is set to ``#-1`` Traffic
Server will not change the user during startup.

在2.1.1版本，可以用 (#) 前缀来指定用户id。如果值为  ``#-1``
程序在启动的时候不会切换用户

Setting ``user_id`` to ``root`` or ``#0`` is now forbidden to
increase security. Trying to do so, will cause the
:program:`traffic_server` fatal failure. However there are two ways to
bypass that restriction

* Specify ``-DBIG_SECURITY_HOLE`` in ``CXXFLAGS`` during compilation.
* Set the ``user_id=#-1`` and start trafficserver as root.

考虑到安全，配置成 ``root`` 或者  ``#0`` 是禁止的。会导致
:program:`traffic_server` 启动失败，但是有两种方式来跳过这个限制

* 编译的时候在 ``CXXFLAGS`` 里指定 ``-DBIG_SECURITY_HOLE``
* 配置成 ``user_id=#-1`` 然后通过root启动

Process Manager
===============

.. ts:cv:: CONFIG proxy.config.process_manager.mgmt_port  INT 8084

   The port used for internal communication between the :program:`traffic_manager` and :program:`traffic_server` processes.

   用于 :program:`traffic_manager` 和 :program:`traffic_server` 进程通信的端口

Alarm Configuration
===================

.. ts:cv:: CONFIG proxy.config.alarm.bin STRING example_alarm_bin.sh

   Name of the script file that can execute certain actions when an alarm is signaled. The default file is a sample script named
   ``example_alarm_bin.sh`` located in the ``bin`` directory. You must dit the script to suit your needs.

   告警触发的时候执行的脚本文件名称，默认是在 ``bin`` 目录下的 ``example_alarm_bin.sh`` 
   你需要定制此脚本来满足你的需求。

.. ts:cv:: CONFIG proxy.config.alarm.abs_path STRING NULL

   The full path to the script file that sends email to alert someone bout Traffic Server problems.

   当Traffic Server故障时发邮件来通知的脚本的绝对路径。

HTTP Engine
===========

.. ts:cv:: CONFIG proxy.config.http.server_ports STRING 8080

   Ports used for proxying HTTP traffic.

   代理HTTP流量的端口

This is a list, separated by space or comma, of :index:`port descriptors`. Each descriptor is a sequence of keywords and values separated by colons. Not all keywords have values, those that do are specifically noted. Keywords with values can have an optional '=' character separating the keyword and value. The case of keywords is ignored. The order of keywords is irrelevant but unspecified results may occur if incompatible options are used (noted below). Options without values are idempotent. Options with values use the last (right most) value specified, except for ``ip-out`` as detailed later.

这是一个空格或者逗号分隔的 :index:`port descriptors` 列表，每个描述符是由分号分隔的
关键字和值序列，并不是所有的关键字都有值，这些会特别指出。有值的关键字可以用 '='
分隔。关键字大小写不敏感。关键字的顺序没有关系，但是如果不兼容的选项同时出现会发生
不可预知的结果（详见下表）。没有值的关键字是幂等的，带有值的关键值用最后一个值，
除了 ``ip-out`` ，后文有详细说明。

Quick reference chart.

=========== =============== ========================================
Name        Note            Definition
=========== =============== ========================================
*number*    **Required**    The local port.
ipv4        **Default**     Bind to IPv4 address family.
ipv6                        Bind to IPv6 address family.
tr-in                       Inbound transparent.
tr-out                      Outbound transparent.
tr-full                     Fully transparent (inbound and outbound)
tr-pass                     Pass through enabled.
ssl                         SSL terminated.
ip-in       **Value**       Local inbound IP address.
ip-out      **Value**       Local outbound IP address.
ip-resolve  **Value**       IP address resolution style.
blind                       Blind (``CONNECT``) port.
compress    **N/I**         Compressed. Not implemented.
=========== =============== ========================================

快速参考卡片

=========== =============== ========================================
Name        Note            Definition
=========== =============== ========================================
*number*    **Required**    本地端口
ipv4        **Default**     IPv4
ipv6                        IPv6
tr-in                       入口流量
tr-out                      出口流量
tr-full                     双向流量
tr-pass                     允许流经
ssl                         终止SSL
ip-in       **Value**       本地入口地址
ip-out      **Value**       本地出口地址
ip-resolve  **Value**       IP地址解析风格
blind                       黑洞端口(``CONNECT``)
compress    **N/I**         压缩，尚未实现
=========== =============== ========================================

*number*
   Local IP port to bind. This is the port to which ATS clients will connect.

   本地绑定的端口，这是所有ATS客户端要连接的端口

ipv4
   Use IPv4. This is the default and is included primarily for completeness. This forced if the ``ip-in`` option is used with an IPv4 address.

   使用IPv4

ipv6
   Use IPv6. This is forced if the ``ip-in`` option is used with an IPv6 address.

   使用IPv4

tr-in
   Inbound transparent. The proxy port will accept connections to any IP address on the port. To have IPv6 inbound transparent you must use this and the ``ipv6`` option. This overrides :ts:cv:`proxy.local.incoming_ip_to_bind`.

   Not compatible with: ``ip-in``, ``ssl``, ``blind``

   入口流量，代理会接受到所有IP的连接， 要接受IPv6请求要指定 ``ipv6`` 选项。改配置会覆盖  :ts:cv:`proxy.local.incoming_ip_to_bind`.

   与 ``ip-in``, ``ssl``, ``blind`` 不兼容

tr-out
   Outbound transparent. If ATS connects to an origin server for a transaction on this port, it will use the client's address as its local address. This overrides :ts:cv:`proxy.local.outgoing_ip_to_bind`.

   Not compatible with: ``ip-out``, ``ssl``, ``ip-resolve``

   出口流量，如果ATS在此端口为一个请求连接源站， 它会使用客户端IP作为本地地址。 这个覆盖  :ts:cv:`proxy.local.outgoing_ip_to_bind`.

   与 ``ip-out``, ``ssl``, ``ip-resolve`` 不兼容

tr-full
   Fully transparent. This is a convenience option and is identical to specifying both ``tr-in`` and ``tr-out``.

   Not compatible with: Any option not compatible with ``tr-in`` or ``tr-out``.

   双向流量。 等同于 ``tr-in`` 和 ``tr-out``.

tr-pass
   Transparent pass through. This option is useful only for inbound transparent proxy ports. If the parsing of the expected HTTP header fails, then the transaction is switched to a blind tunnel instead of generating an error response to the client. It effectively enables :ts:cv:`proxy.config.http.use_client_target_addr` for the transaction as there is no other place to obtain the origin server address.

   透明传输。用于指定入口方向的透明传输代理端口。如果解析HTTP报头失败， 会转换成一个隧道而不是返回错误信息给客户端。 :ts:cv:`proxy.config.http.use_client_target_addr` 会被开启，因为因为没有获取源站IP的方式。

ip-in
   Set the local IP address for the port. This is the address to which clients will connect. This forces the IP address family for the port. The ``ipv4`` or ``ipv6`` can be used but it is optional and is an error for it to disagree with the IP address family of this value. An IPv6 address **must** be enclosed in square brackets. If this options is omitted :ts:cv:`proxy.local.incoming_ip_to_bind` is used.

   Not compatible with: ``tr-in``.

  指定本地IP地址。所有客户端连接的地址。这个配置限制端口对应的协议类型。可以指定 ``ipv4`` or ``ipv6`` , 但是是可选的，如果值与类型不匹配会报错。 IPv6地址必须用方括号括起来。如果不指定该选项， :ts:cv:`proxy.local.incoming_ip_to_bind` 会生效。

  与``tr-in`` 不兼容

ip-out
   Set the local IP address for outbound connections. This is the address used by ATS locally when it connects to an origin server for transactions on this port. If this is omitted :ts:cv:`proxy.local.outgoing_ip_to_bind` is used.

   This option can used multiple times, once for each IP address family. The address used is selected by the IP address family of the origin server address.

   Not compatible with: ``tr-out``.

   出口连接的IP，也就是连接源站时使用的IP地址。如果不指定 :ts:cv:`proxy.local.outgoing_ip_to_bind` 会生效。

   这个选项可以使用多次，每个协议类型都可以使用，ATS根据源站的地址选择。

   与 ``tr-out`` 不兼容。

ip-resolve
   Set the :ts:cv:`host resolution style <proxy.config.hostdb.ip_resolve>` for transactions on this proxy port.

   Not compatible with: ``tr-out``.

   配置解析代理端口的  :ts:cv:`host resolution style <proxy.config.hostdb.ip_resolve>` 

   与  ``tr-out`` 不兼容

ssl
   Require SSL termination for inbound connections. SSL :ref:`must be configured <configuring-ssl-termination>` for this option to provide a functional server port.

   Not compatible with: ``tr-in``, ``tr-out``, ``blind``.

   要求入口连接终止SSL。 SSL  :ref:`must be configured <configuring-ssl-termination>`  来提供一个功能端口

   与 ``tr-in``, ``tr-out``, ``blind`` 不兼容

blind
   Accept only ``CONNECT`` transactions on this port.

   Not compatible with: ``tr-in``, ``ssl``.

   只接受 ``CONNECT`` 连接

   与 ``tr-in``, ``ssl`` 不兼容

compress
   Compress the connection. Retained only by inertia, should be considered "not implemented".

   压缩连接

.. topic:: Example

   Listen on port 80 on any address for IPv4 and IPv6.::

      80 80:ipv6

   在80上监听IPv4和IPv6请求::

      80 80:ipv6

.. topic:: Example

   Listen transparently on any IPv4 address on port 8080, and
   transparently on port 8080 on local address ``fc01:10:10:1::1``
   (which implies ``ipv6``).::

      IPv4:tr-FULL:8080 TR-full:IP-in=[fc02:10:10:1::1]:8080

   在IPv的8080端口监听透明传输，在``fc01:10:10:1::1``的
   8080接受透明传输

      IPv4:tr-FULL:8080 TR-full:IP-in=[fc02:10:10:1::1]:8080

.. topic:: Example

   Listen on port 8080 for IPv6, fully transparent. Set up an SSL port on 443. These ports will use the IP address from :ts:cv:`proxy.local.incoming_ip_to_bind`.  Listen on IP address ``192.168.17.1``, port 80, IPv4, and connect to origin servers using the local address ``10.10.10.1`` for IPv4 and ``fc01:10:10:1::1`` for IPv6.::

      8080:ipv6:tr-full 443:ssl ip-in=192.168.17.1:80:ip-out=[fc01:10:10:1::1]:ip-out=10.10.10.1

   监听IPv6的8080，双向传输。在443上监听SSL。这些端口会使用 :ts:cv:`proxy.local.incoming_ip_to_bind` 指定的IP
   在 ``192.168.17.1`` 监听，端口为80， IPv4， 用 ``10.10.10.1`` 和 ``fc01:10:10:1::1`` 连接源站.

      8080:ipv6:tr-full 443:ssl ip-in=192.168.17.1:80:ip-out=[fc01:10:10:1::1]:ip-out=10.10.10.1

.. ts:cv:: CONFIG proxy.config.http.connect_ports STRING 443 563

   The range of origin server ports that can be used for tunneling via ``CONNECT``.

Traffic Server allows tunnels only to the specified ports.
Supports both wildcards ('\*') and ranges ("0-1023").

   用于 ``CONNECT`` 隧道连接的服务端口。

Traffic Server只允许到特定端口的隧道。既支持通配符 ('\*') 又支持("0-1023")

.. note::

   These are the ports on the *origin server*, not Traffic Server :ts:cv:`proxy ports <proxy.config.http.server_ports>`.

   这些都是源站的端口，不是ATS的端口 :ts:cv:`proxy ports <proxy.config.http.server_ports>`

.. ts:cv:: CONFIG proxy.config.http.insert_request_via_str INT 1
   :reloadable:

   Set how the ``Via`` field is handled on a request to the origin server.

   配置via字段的处理方式

===== ============================================
Value Effect
===== ============================================
0     Do not modify / set this via header
1     Update the via, with normal verbosity
2     Update the via, with higher verbosity
3     Update the via, with highest verbosity
===== ============================================

===== ============================================
Value Effect
===== ============================================
0     不做修改
1     用正常的信息来更新via
2     用详细信息来更新via
3     用最详细信息来更新via
===== ============================================

.. note::

   The ``Via`` header string interpretation can be `decoded here. </tools/via>`_

   via报头可以用这个工具解析 `decoded here. </tools/via>`_

.. ts:cv:: CONFIG proxy.config.http.insert_response_via_str INT 0
   :reloadable:

   Set how the ``Via`` field is handled on the response to the client.

   配置如何处理响应到客户端的via字段

===== ============================================
Value Effect
===== ============================================
0     Do not modify / set this via header
1     Update the via, with normal verbosity
2     Update the via, with higher verbosity
3     Update the via, with highest verbosity
===== ============================================

===== ============================================
Value Effect
===== ============================================
0     不做修改
1     用正常的信息来更新via
2     用详细信息来更新via
3     用最详细信息来更新via
===== ============================================

.. note::

   The ``Via`` header string interpretation can be `decoded here. </tools/via>`_

   via报头可以用这个工具解析 `decoded here. </tools/via>`_

.. ts:cv:: CONFIG proxy.config.http.response_server_enabled INT 1
   :reloadable:

   You can specify one of the following:

   -  ``0`` no Server: header is added to the response.
   -  ``1`` the Server: header is added (see string below).
   -  ``2`` the Server: header is added only if the response from rigin does not have one already.

   你可以指定如下配置：

   -  ``0`` 不添加Server报头
   -  ``1`` 添加Server报头 (see string below).
   -  ``2`` 如果源站没有则添加一个Server报头

.. ts:cv:: CONFIG proxy.config.http.insert_age_in_response INT 1
   :reloadable:

   This option specifies whether Traffic Server should insert an ``Age`` header in the response. The Age field value is the cache's
   estimate of the amount of time since the response was generated or revalidated by the origin server.

   -  ``0`` no ``Age`` header is added
   -  ``1`` the ``Age`` header is added

   配置是否插入 ``Age`` 报头, 该报头用于指定缓存的自对象生成或者校验后的寿命.

   -  ``0`` 不添加
   -  ``1`` 添加

.. ts:cv:: CONFIG proxy.config.http.response_server_str STRING ATS/
   :reloadable:

   The Server: string that ATS will insert in a response header (if requested, see above). Note that the current version number is
   always appended to this string.

   Server报头的内容，注意当前的版本号始终会追加到最后。

.. ts:cv:: CONFIG proxy.config.http.enable_url_expandomatic INT 1
   :reloadable:

   Enables (``1``) or disables (``0``) ``.com`` domain expansion. This configures the Traffic Server to resolve unqualified hostnames by
   prepending with ``www.`` and appending with ``.com`` before redirecting to the expanded address. For example: if a client makes
   a request to ``host``, then Traffic Server redirects the request to ``www.host.com``.

   是否允许域名扩展，就是在前边追加 ``www.`` 在后边追加 ``.com`` 来回源

.. ts:cv:: CONFIG proxy.config.http.chunking_enabled INT 1
   :reloadable:

   Specifies whether Traffic Sever can generate a chunked response:

   -  ``0`` Never
   -  ``1`` Always
   -  ``2`` Generate a chunked response if the server has returned HTTP/1.1 before
   -  ``3`` = Generate a chunked response if the client request is HTTP/1.1 and the origin server has returned HTTP/1.1 before

   指定ATS是否能返回分块响应:

   -  ``0`` 永远不
   -  ``1`` 一直可以
   -  ``2`` 如果源站返回过HTTP/1.1，则可以分片
   -  ``3`` 如果客户端发起过HTTP/1.1， 源站返回过HTTP/1.1，则可以分片

   .. note::

       If HTTP/1.1 is used, then Traffic Server can use
       keep-alive connections with pipelining to origin servers. If
       HTTP/0.9 is used, then Traffic Server does not use ``keep-alive``
       connections to origin servers. If HTTP/1.0 is used, then Traffic
       Server can use ``keep-alive`` connections without pipelining to
       origin servers.

       如果使用的是HTTP/1.1，ATS可以使用长连接来和源站保持管道。
       如果使用的是HTTP/0.9，ATS不会使用长连接。
       如果使用的是HTTP/1.0，ATS可是使用长连接但是没有管道。

.. ts:cv:: CONFIG proxy.config.http.share_server_sessions INT 1

   Enables (``1``) or disables (``0``) the reuse of server sessions.

   是否允许复用服务器会话

.. ts:cv:: CONFIG proxy.config.http.record_heartbeat INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) :program:`traffic_cop` heartbeat ogging.

   是否开启 :program:`traffic_cop` 的心跳

.. ts:cv:: CONFIG proxy.config.http.use_client_target_addr  INT 0

   For fully transparent ports use the same origin server address as the client.

   对于双向通信，使用客户端相同的源站地址

This option causes Traffic Server to avoid where possible doing DNS
lookups in forward transparent proxy mode. The option is only
effective if the following three conditions are true -

*  Traffic Server is in forward proxy mode.
*  The proxy port is inbound transparent.
*  The target URL has not been modified by either remapping or a plugin.

这个选项可以控制ATS在透明代理模式下避免再次DNS查询，只有满足如下条件才剩下 -

*  ATS工作在转发代理模式
*  代理端口是入口流量
* 目标URL没有被remap规则修改

If any of these conditions are not true, then normal DNS processing
is done for the connection.

如果任何一个条件不满足的话，还是要DNS查询。

If all of these conditions are met, then the origin server IP
address is retrieved from the original client connection, rather
than through HostDB or DNS lookup. In effect, client DNS resolution
is used instead of Traffic Server DNS.

如果所有条件都满足，那么源站IP地址会从原始的客户端连接里获取，而不是通过
HostDB或者DNS查询，效果上说就是用客户端的DNS解析而不是ATS的。

This can be used to be a little more efficient (looking up the
target once by the client rather than by both the client and Traffic
Server) but the primary use is when client DNS resolution can differ
from that of Traffic Server. Two known uses cases are:

#. Embedded IP addresses in a protocol with DNS load sharing. In
   this case, even though Traffic Server and the client both make
   the same request to the same DNS resolver chain, they may get
   different origin server addresses. If the address is embedded in
   the protocol then the overall exchange will fail. One current
   example is Microsoft Windows update, which presumably embeds the
   address as a security measure.

#. The client has access to local DNS zone information which is not
   available to Traffic Server. There are corporate nets with local
   DNS information for internal servers which, by design, is not
   propagated outside the core corporate network. Depending a
   network topology it can be the case that Traffic Server can
   access the servers by IP address but cannot resolve such
   addresses by name. In such as case the client supplied target
   address must be used.

这个配置可以用的更高效些（根据客户端来查询而不是根据客户端加源站来查询）
但是如果客户端使用的DNS解析和ATS的不一样，那么还是基本的用法，有以下两种
应用场景:

#. 在协议里通过DNS负载据恒嵌入IP地址。这个情况下尽管ATS和客户端发起同样的
   请求，他们可能获取不同的结果。如果嵌入IP地址整个传输会失败。目前的一个
   例子是微软的更新，嵌入IP作为一个安全标准。

#. 客户端拥有本地域名解析zone的权限，而ATS没有。有些公司网络只给内部网络
   提供DNS信息，这样外部网络无法获取。这样ATS只能到达服务器但是不能通过
   域名解析到该服务器地址，这种情况下只能用客户端提供的目标地址。

This solution must be considered interim. In the longer term, it
should be possible to arrange for much finer grained control of DNS
lookup so that wildcard domain can be set to use Traffic Server or
client resolution. In both known use cases, marking specific domains
as client determined (rather than a single global switch) would
suffice. It is possible to do this crudely with this flag by
enabling it and then use identity URL mappings to re-disable it for
specific domains.

这个解决办法可能是临时的。 从长远考虑， 调整DNS解析让ATS和客户端都能
使用应该是可能的。 这两种应用场景，由客户端决定标识特定的域是可以满足需求的
通过URL映射来禁用特定的域也可以很粗糙的达到同样的效果。

Parent Proxy Configuration
==========================

.. ts:cv:: CONFIG proxy.config.http.parent_proxy_routing_enable INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) the parent caching option. Refer to :ref:`hierarchical-caching`.

.. ts:cv:: CONFIG proxy.config.http.parent_proxy.retry_time INT 300
   :reloadable:

   The amount of time allowed between connection retries to a parent cache that is unavailable.

.. ts:cv:: CONFIG proxy.config.http.parent_proxy.fail_threshold INT 10
   :reloadable:

   The number of times the connection to the parent cache can fail before Traffic Server considers the parent unavailable.

.. ts:cv:: CONFIG proxy.config.http.parent_proxy.total_connect_attempts INT 4
   :reloadable:

   The total number of connection attempts allowed to a parent cache before Traffic Server bypasses the parent or fails the request
   (depending on the ``go_direct`` option in the :file:`parent.config` file).

.. ts:cv:: CONFIG proxy.config.http.parent_proxy.per_parent_connect_attempts INT 2
   :reloadable:

   The total number of connection attempts allowed per parent, if multiple parents are used.

.. ts:cv:: CONFIG proxy.config.http.parent_proxy.connect_attempts_timeout INT 30
   :reloadable:

   The timeout value (in seconds) for parent cache connection attempts.

.. ts:cv:: CONFIG proxy.config.http.forward.proxy_auth_to_parent INT 0
   :reloadable:

   Configures Traffic Server to send proxy authentication headers on to the parent cache.

.. ts:cv:: CONFIG proxy.config.http.no_dns_just_forward_to_parent INT 0
   :reloadable:

   Don't try to resolve DNS, forward all DNS requests to the parent. This is off (``0``) by default.

HTTP Connection Timeouts
========================

.. ts:cv:: CONFIG proxy.config.http.keep_alive_no_activity_timeout_in INT 10
   :reloadable:

   Specifies how long Traffic Server keeps connections to clients open for a subsequent request after a transaction ends.

.. ts:cv:: CONFIG proxy.config.http.keep_alive_no_activity_timeout_out INT 10
   :reloadable:

   Specifies how long Traffic Server keeps connections to origin servers open for a subsequent transfer of data after a transaction ends.

.. ts:cv:: CONFIG proxy.config.http.transaction_no_activity_timeout_in INT 120
   :reloadable:

   Specifies how long Traffic Server keeps connections to clients open if a transaction stalls.

.. ts:cv:: CONFIG proxy.config.http.transaction_no_activity_timeout_out INT 120
   :reloadable:

   Specifies how long Traffic Server keeps connections to origin servers open if the transaction stalls.

.. ts:cv:: CONFIG proxy.config.http.transaction_active_timeout_in INT 0
   :reloadable:

   The maximum amount of time Traffic Server can remain connected to a client. If the transfer to the client is not complete before this
   timeout expires, then Traffic Server closes the connection.

The default value of ``0`` specifies that there is no timeout.

.. ts:cv:: CONFIG proxy.config.http.transaction_active_timeout_out INT 0
   :reloadable:

   The maximum amount of time Traffic Server waits for fulfillment of a connection request to an origin server. If Traffic Server does not
   complete the transfer to the origin server before this timeout expires, then Traffic Server terminates the connection request.

The default value of ``0`` specifies that there is no timeout.

.. ts:cv:: CONFIG proxy.config.http.accept_no_activity_timeout INT 120
   :reloadable:

   The timeout interval in seconds before Traffic Server closes a connection that has no activity.

.. ts:cv:: CONFIG proxy.config.http.background_fill_active_timeout INT 60
   :reloadable:

   Specifies how long Traffic Server continues a background fill before giving up and dropping the origin server connection.

.. ts:cv:: CONFIG proxy.config.http.background_fill_completed_threshold FLOAT 0.50000
   :reloadable:

   The proportion of total document size already transferred when a client aborts at which the proxy continues fetching the document
   from the origin server to get it into the cache (a **background fill**).

Origin Server Connect Attempts
==============================

.. ts:cv:: CONFIG proxy.config.http.connect_attempts_max_retries INT 6
   :reloadable:

   The maximum number of connection retries Traffic Server can make when the origin server is not responding.

.. ts:cv:: CONFIG proxy.config.http.connect_attempts_max_retries_dead_server INT 2
   :reloadable:

   The maximum number of connection retries Traffic Server can make when the origin server is unavailable.

.. ts:cv:: CONFIG proxy.config.http.server_max_connections INT 0
   :reloadable:

   Limits the number of socket connections across all origin servers to the value specified. To disable, set to zero (``0``).

.. ts:cv:: CONFIG proxy.config.http.origin_max_connections INT 0
   :reloadable:

   Limits the number of socket connections per origin server to the value specified. To enable, set to one (``1``).

.. ts:cv:: CONFIG proxy.config.http.origin_min_keep_alive_connections INT 0
   :reloadable:

   As connection to an origin server are opened, keep at least 'n' number of connections open to that origin, even if
   the connection isn't used for a long time period. Useful when the origin supports keep-alive, removing the time
   needed to set up a new connection from
   the next request at the expense of added (inactive) connections. To enable, set to one (``1``).

.. ts:cv:: CONFIG proxy.config.http.connect_attempts_rr_retries INT 2
   :reloadable:

   The maximum number of failed connection attempts allowed before a round-robin entry is marked as 'down' if a server
   has round-robin DNS entries.

.. ts:cv:: CONFIG proxy.config.http.connect_attempts_timeout INT 30
   :reloadable:

   The timeout value (in seconds) for an origin server connection.

.. ts:cv:: CONFIG proxy.config.http.post_connect_attempts_timeout INT 1800
   :reloadable:

   The timeout value (in seconds) for an origin server connection when the client request is a ``POST`` or ``PUT``
   request.

.. ts:cv:: CONFIG proxy.config.http.down_server.cache_time INT 900
   :reloadable:

   Specifies how long (in seconds) Traffic Server remembers that an origin server was unreachable.

.. ts:cv:: CONFIG proxy.config.http.down_server.abort_threshold INT 10
   :reloadable:

   The number of seconds before Traffic Server marks an origin server as unavailable after a client abandons a request
   because the origin server was too slow in sending the response header.

Congestion Control
==================

.. ts:cv:: CONFIG proxy.config.http.congestion_control.enabled INT 0

   Enables (``1``) or disables (``0``) the Congestion Control option, which configures Traffic Server to stop forwarding
   HTTP requests to origin servers when they become congested. Traffic Server sends the client a message to retry the
   congested origin server later. Refer to :ref:`using-congestion-control`.

.. ts:cv:: CONFIG proxy.config.http.flow_control.enabled INT 0

   Transaction buffering / flow control is enabled if this is set to a non-zero value. Otherwise no flow control is done.

.. ts:cv:: CONFIG proxy.config.http.flow_control.high_water INT 65536
   :metric: bytes

   The high water mark for transaction buffer control. External source I/O is halted when the total buffer space in use
   by the transaction exceeds this value.

.. ts:cv:: CONFIG proxy.config.http.flow_control.low_water INT 65536
   :metric: bytes

   The low water mark for transaction buffer control. External source I/O is resumed when the total buffer space in use
   by the transaction is no more than this value.

Negative Response Caching
=========================

.. ts:cv:: CONFIG proxy.config.http.negative_caching_enabled INT 0
   :reloadable:

   When enabled (``1``), Traffic Server caches negative responses (such as ``404 Not Found``) when a requested page does
   not exist. The next time a client requests the same page, Traffic Server serves the negative response directly from
   cache.

   .. note::

      ``Cache-Control`` directives from the server forbidding ache are ignored for the following HTTP response codes, regardless
      of the value specified for the :ts:cv:`proxy.config.http.negative_caching_enabled` variable. The
      following negative responses are cached by Traffic Server:::

         204  No Content
         305  Use Proxy
         400  Bad Request
         403  Forbidden
         404  Not Found
         405  Method Not Allowed
         500  Internal Server Error
         501  Not Implemented
         502  Bad Gateway
         503  Service Unavailable
         504  Gateway Timeout

   The cache lifetime for objects cached from this setting is controlled via
   :ts:cv:`proxy.config.http.negative_caching_lifetime`.

Proxy User Variables
====================

.. ts:cv:: CONFIG proxy.config.http.anonymize_remove_from INT 0
   :reloadable:

   When enabled (``1``), Traffic Server removes the ``From`` header to protect the privacy of your users.

.. ts:cv:: CONFIG proxy.config.http.anonymize_remove_referer INT 0
   :reloadable:

   When enabled (``1``), Traffic Server removes the ``Referrer`` header to protect the privacy of your site and users.

.. ts:cv:: CONFIG proxy.config.http.anonymize_remove_user_agent INT 0
   :reloadable:

   When enabled (``1``), Traffic Server removes the ``User-agent`` header to protect the privacy of your site and users.

.. ts:cv:: CONFIG proxy.config.http.anonymize_remove_cookie INT 0
   :reloadable:

   When enabled (``1``), Traffic Server removes the ``Cookie`` header to protect the privacy of your site and users.

.. ts:cv:: CONFIG proxy.config.http.anonymize_remove_client_ip INT 0
   :reloadable:

   When enabled (``1``), Traffic Server removes ``Client-IP`` headers for more privacy.

.. ts:cv:: CONFIG proxy.config.http.anonymize_insert_client_ip INT 1
   :reloadable:

   When enabled (``1``), Traffic Server inserts ``Client-IP`` headers to retain the client IP address.

.. ts:cv:: CONFIG proxy.config.http.append_xforwards_header INT 0

   When enabled (``1``), Traffic Server appends ``X-Forwards`` headers to outgoing requests.

.. ts:cv:: CONFIG proxy.config.http.anonymize_other_header_list STRING NULL
   :reloadable:

   The headers Traffic Server should remove from outgoing requests.

.. ts:cv:: CONFIG proxy.config.http.insert_squid_x_forwarded_for INT 0
   :reloadable:

   When enabled (``1``), Traffic Server adds the client IP address to the ``X-Forwarded-For`` header.

.. ts:cv:: CONFIG proxy.config.http.normalize_ae_gzip INT 0
   :reloadable:

   Enable (``1``) to normalize all ``Accept-Encoding:`` headers to one of the following:

   -  ``Accept-Encoding: gzip`` (if the header has ``gzip`` or ``x-gzip`` with any ``q``) **OR**
   -  *blank* (for any header that does not include ``gzip``)

   This is useful for minimizing cached alternates of documents (e.g. ``gzip, deflate`` vs. ``deflate, gzip``). Enabling this option is
   recommended if your origin servers use no encodings other than ``gzip``.


Security
========

.. ts:cv:: CONFIG proxy.config.http.push_method_enabled INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) the HTTP ``PUSH`` option, which allows you to deliver content directly to the cache without a user
   request.

   .. important::

       If you enable this option, then you must also specify
       a filtering rule in the ip_allow.config file to allow only certain
       machines to push content into the cache.

Cache Control
=============

.. ts:cv:: CONFIG proxy.config.cache.enable_read_while_writer INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) ability to a read cached object while the another connection is completing the write to cache for
   the same object. Several other configuration values need to be set for this to become active. See :ref:`reducing-origin-server-requests-avoiding-the-thundering-herd`

.. ts:cv:: CONFIG proxy.config.cache.force_sector_size INT 512
   :reloadable:

   Forces the use of a specific hardware sector size (512 - 8192 bytes).

.. ts:cv:: CONFIG proxy.config.http.cache.http INT 1
   :reloadable:

   Enables (``1``) or disables (``0``) caching of HTTP requests.

.. ts:cv:: CONFIG proxy.config.http.cache.allow_empty_doc INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) caching objects that have an empty
   response body. This is particularly useful for caching 301 or 302 responses
   with a ``Location`` header but no document body. This only works if the
   origin response also has a ``Content-Length`` header.

.. ts:cv:: CONFIG proxy.config.http.cache.ignore_client_no_cache INT 0
   :reloadable:

   When enabled (``1``), Traffic Server ignores client requests to bypass the cache.

.. ts:cv:: CONFIG proxy.config.http.cache.ims_on_client_no_cache INT 0
   :reloadable:

   When enabled (``1``), Traffic Server issues a conditional request to the origin server if an incoming request has a ``No-Cache`` header.

.. ts:cv:: CONFIG proxy.config.http.cache.ignore_server_no_cache INT 0
   :reloadable:

   When enabled (``1``), Traffic Server ignores origin server requests to bypass the cache.

.. ts:cv:: CONFIG proxy.config.http.cache.cache_responses_to_cookies INT 3
   :reloadable:

   Specifies how cookies are cached:

   -  ``0`` = do not cache any responses to cookies
   -  ``1`` = cache for any content-type
   -  ``2`` = cache only for image types
   -  ``3`` = cache for all but text content-types

.. ts:cv:: CONFIG proxy.config.http.cache.ignore_authentication INT 0

   When enabled (``1``), Traffic Server ignores ``WWW-Authentication`` headers in responses ``WWW-Authentication`` headers are removed and
   not cached.

.. ts:cv:: CONFIG proxy.config.http.cache.cache_urls_that_look_dynamic INT 1
   :reloadable:

   Enables (``1``) or disables (``0``) caching of URLs that look dynamic, i.e.: URLs that end in *``.asp``* or contain a question
   mark (*``?``*), a semicolon (*``;``*), or *``cgi``*. For a full list, please refer to
   `HttpTransact::url_looks_dynamic </link/to/doxygen>`_

.. ts:cv:: CONFIG proxy.config.http.cache.enable_default_vary_headers INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) caching of alternate versions of HTTP objects that do not contain the ``Vary`` header.

.. ts:cv:: CONFIG proxy.config.http.cache.when_to_revalidate INT 0
   :reloadable:

   Specifies when to revalidate content:

   -  ``0`` = use cache directives or heuristic (the default value)
   -  ``1`` = stale if heuristic
   -  ``2`` = always stale (always revalidate)
   -  ``3`` = never stale
   -  ``4`` = use cache directives or heuristic (0) unless the request
       has an ``If-Modified-Since`` header

   If the request contains the ``If-Modified-Since`` header, then
   Traffic Server always revalidates the cached content and uses the
   client's ``If-Modified-Since`` header for the proxy request.

.. ts:cv:: CONFIG proxy.config.http.cache.when_to_add_no_cache_to_msie_requests INT 0
   :reloadable:

   Specifies when to add ``no-cache`` directives to Microsoft Internet Explorer requests. You can specify the following:

   -  ``0`` = ``no-cache`` is *not* added to MSIE requests
   -  ``1`` = ``no-cache`` is added to IMS MSIE requests
   -  ``2`` = ``no-cache`` is added to all MSIE requests

.. ts:cv:: CONFIG proxy.config.http.cache.required_headers INT 0
   :reloadable:

   The type of headers required in a request for the request to be cacheable.

   -  ``0`` = no headers required to make document cacheable
   -  ``1`` = either the ``Last-Modified`` header, or an explicit lifetime header, ``Expires`` or ``Cache-Control: max-age``, is required
   -  ``2`` = explicit lifetime is required, ``Expires`` or ``Cache-Control: max-age``

.. ts:cv:: CONFIG proxy.config.http.cache.max_stale_age INT 604800
   :reloadable:

   The maximum age allowed for a stale response before it cannot be cached.

.. ts:cv:: CONFIG proxy.config.http.cache.range.lookup INT 1

   When enabled (``1``), Traffic Server looks up range requests in the cache.

.. ts:cv:: CONFIG proxy.config.http.cache.ignore_accept_mismatch INT 0
   :reloadable:

   When enabled with a value of ``1``, Traffic Server serves documents from cache with a
   ``Content-Type:`` header even if it does not match the ``Accept:`` header of the
   request. If set to ``2``, this logic only happens in the absence of a
   ``Vary`` header in the cached response (which is the recommended and safe use).

   .. note::
      This option should only be enabled with ``1`` if you're having
      problems with caching *and* you origin server doesn't set the ``Vary``
      header. Alternatively, if the origin is incorrectly setting
      ``Vary: Accept`` or doesn't respond with ``406 (Not Acceptable)``,
      you can also enable this configuration with a ``1``.


.. ts:cv:: CONFIG proxy.config.http.cache.ignore_accept_language_mismatch INT 0
   :reloadable:

   When enabled with a value of ``1``, Traffic Server serves documents from cache with a
   ``Content-Language:`` header even if it does not match the ``Accept-Language:``
   header of the request. If set to ``2``, this logic only happens in the absence of a
   ``Vary`` header in the cached response (which is the recommended and safe use).

   .. note::

      This option should only be enabled with ``1`` if you're having
      problems with caching *and* you origin server doesn't set the ``Vary``
      header. Alternatively, if the origin is incorrectly setting
      ``Vary: Accept-Language`` or doesn't respond with ``406 (Not Acceptable)``,
      you can also enable this configuration with a ``1``.


.. ts:cv:: CONFIG proxy.config.http.cache.ignore_accept_encoding_mismatch INT 0
   :reloadable:

   When enabled with a value of ``1``, Traffic Server serves documents from cache with a
   ``Content-Encoding:`` header even if it does not match the ``Accept-Encoding:``
   header of the request. If set to ``2``, this logic only happens in the absence of a
   ``Vary`` header in the cached response (which is the recommended and safe use).

   .. note::

      This option should only be enabled with ``1`` if you're having
      problems with caching *and* you origin server doesn't set the ``Vary``
      header. Alternatively, if the origin is incorrectly setting
      ``Vary: Accept-Encoding`` or doesn't respond with ``406 (Not Acceptable)``
      you can also enable this configuration with a ``1``.


.. ts:cv:: CONFIG proxy.config.http.cache.ignore_accept_charset_mismatch INT 0
   :reloadable:

   When enabled with a value of ``1``, Traffic Server serves documents from cache with a
   ``Content-Type:`` header even if it does not match the ``Accept-Charset:`` header
   of the request. If set to ``2``, this logic only happens in the absence of a
   ``Vary`` header in the cached response (which is the recommended and safe use).

   .. note::

      This option should only be enabled with ``1`` if you're having
      problems with caching *and* you origin server doesn't set the ``Vary``
      header. Alternatively, if the origin is incorrectly setting
      ``Vary: Accept-Charset`` or doesn't respond with ``406 (Not Acceptable)``,
      you can also enable this configuration with a ``1``.


.. ts:cv:: CONFIG proxy.config.http.cache.ignore_client_cc_max_age INT 1
   :reloadable:

   When enabled (``1``), Traffic Server ignores any ``Cache-Control:
   max-age`` headers from the client. This technically violates the HTTP RFC,
   but avoids a problem where a client can forcefully invalidate a cached object.

.. ts:cv:: CONFIG proxy.config.cache.max_doc_size INT 0

   Specifies the maximum object size that will be cached. ``0`` is unlimited.

.. ts:cv:: CONFIG proxy.config.cache.permit.pinning INT 0
   :reloadable:

   When enabled (``1``), Traffic Server will keep certain HTTP objects in the cache for a certain time as specified in cache.config.

.. ts:cv:: CONFIG proxy.config.cache.hit_evacuate_percent INT 10

   The size of the region (as a percentage of the total content storage in a :term:`cache stripe`) in front of the
   :term:`write cursor` that constitutes a recent access hit for evacutating the accessed object.

   When an object is accessed it can be marked for evacuation, that is to be copied over the write cursor and
   thereby preserved from being overwritten. This is done if it is no more than a specific number of bytes in front of
   the write cursor. The number of bytes is a percentage of the total number of bytes of content storage in the cache
   stripe where the object is stored and that percentage is set by this variable.

.. ts:cv:: CONFIG proxy.config.cache.hit_evacuate_size_limit INT 0
   :metric: bytes

   Limit the size of objects that are hit evacuated.

   Objects larger than the limit are not hit evacuated. A value of 0 disables the limit.

RAM Cache
=========

.. ts:cv:: CONFIG proxy.config.cache.ram_cache.size INT -1

   By default the RAM cache size is automatically determined, based on
   disk cache size; approximately 10 MB of RAM cache per GB of disk cache.
   Alternatively, it can be set to a fixed value such as
   **20GB** (21474836480)

.. ts:cv:: CONFIG proxy.config.cache.ram_cache.algorithm INT 0

   Two distinct RAM caches are supported, the default (0) being the **CLFUS**
   (*Clocked Least Frequently Used by Size*). As an alternative, a simpler
   **LRU** (*Least Recently Used*) cache is also available, by changing this
   configuration to 1.

.. ts:cv:: CONFIG proxy.config.cache.ram_cache.use_seen_filter INT 0

   Enabling this option will filter inserts into the RAM cache to ensure that
   they have been seen at least once.  For the **LRU**, this provides scan
   resistance. Note that **CLFUS** already requires that a document have history
   before it is inserted, so for **CLFUS**, setting this option means that a
   document must be seen three times before it is added to the RAM cache.

.. ts:cv:: CONFIG proxy.config.cache.ram_cache.compress INT 0

   The **CLFUS** RAM cache also supports an optional in-memory compression.
   This is not to be confused with ``Content-Encoding: gzip`` compression.
   The RAM cache compression is intended to try to save space in the RAM,
   and is not visible to the User-Agent (client).

   Possible values are:

   - ``0`` = no compression
   - ``1`` = fastlz (extremely fast, relatively low compression)
   - ``2`` = libz (moderate speed, reasonable compression)
   - ``3`` = liblzma (very slow, high compression)

   .. note::

      Compression runs on task threads.  To use more cores for RAM cache compression, increase :ts:cv:`proxy.config.task_threads`.


Heuristic Expiration
====================

.. ts:cv:: CONFIG proxy.config.http.cache.heuristic_min_lifetime INT 3600
   :reloadable:

   The minimum amount of time an HTTP object without an expiration date can remain fresh in the cache before is
   considered to be stale.

.. ts:cv:: CONFIG proxy.config.http.cache.heuristic_max_lifetime INT 86400
   :reloadable:

   The maximum amount of time an HTTP object without an expiration date can remain fresh in the cache before is
   considered to be stale.

.. ts:cv:: CONFIG proxy.config.http.cache.heuristic_lm_factor FLOAT 0.10000
   :reloadable:

   The aging factor for freshness computations. Traffic Server stores an object for this percentage of the time that
   elapsed since it last changed.

.. ts:cv:: CONFIG proxy.config.http.cache.fuzz.time INT 240
   :reloadable:

   How often Traffic Server checks for an early refresh, during the period before the document stale time. The interval
   specified must be in seconds. See :ref:`fuzzy-revalidation`

.. ts:cv:: CONFIG proxy.config.http.cache.fuzz.probability FLOAT 0.00500
   :reloadable:

   The probability that a refresh is made on a document during the specified fuzz time.

.. ts:cv:: CONFIG proxy.config.http.cache.fuzz.min_time INT 0
   :reloadable:

   Handles requests with a TTL less than fuzz.time – it allows for different times to evaluate the probability of revalidation for small TTLs and big TTLs. Objects with small TTLs will start "rolling the revalidation dice" near the fuzz.min_time, while objects with large TTLs would start at fuzz.time. A logarithmic like function between determines the revalidation evaluation start time (which will be between fuzz.min_time and fuzz.time). As the object gets closer to expiring, the window start becomes more likely. By default this setting is not enabled, but should be enabled anytime you have objects with small TTLs. The default value is ``0``.

Dynamic Content & Content Negotiation
=====================================

.. ts:cv:: CONFIG proxy.config.http.cache.vary_default_text STRING NULL
   :reloadable:

   The header on which Traffic Server varies for text documents.

For example: if you specify ``User-agent``, then Traffic Server caches
all the different user-agent versions of documents it encounters.

.. ts:cv:: CONFIG proxy.config.http.cache.vary_default_images STRING NULL
   :reloadable:

   The header on which Traffic Server varies for images.

.. ts:cv:: CONFIG proxy.config.http.cache.vary_default_other STRING NULL
   :reloadable:

   The header on which Traffic Server varies for anything other than text and images.

Customizable User Response Pages
================================

.. ts:cv:: CONFIG proxy.config.body_factory.enable_customizations INT 0
   Specifies whether customizable response pages are enabled or
   disabled and which response pages are used:

   -  ``0`` = disable customizable user response pages
   -  ``1`` = enable customizable user response pages in the default directory only
   -  ``2`` = enable language-targeted user response pages

.. ts:cv:: CONFIG proxy.config.body_factory.enable_logging INT 1

   Enables (``1``) or disables (``0``) logging for customizable response pages. When enabled, Traffic Server records a message in
   the error log each time a customized response page is used or modified.

.. ts:cv:: CONFIG proxy.config.body_factory.template_sets_dir STRING config/body_factory

   The customizable response page default directory.

.. ts:cv:: CONFIG proxy.config.body_factory.response_suppression_mode INT 0

   Specifies when Traffic Server suppresses generated response pages:

   -  ``0`` = never suppress generated response pages
   -  ``1`` = always suppress generated response pages
   -  ``2`` = suppress response pages only for intercepted traffic

.. ts:cv:: CONFIG proxy.config.http_ui_enabled INT 0

   Enable the user interface page.

DNS
===

.. ts:cv:: CONFIG proxy.config.dns.search_default_domains INT 1
   :Reloadable:

   Enables (``1``) or disables (``0``) local domain expansion.

Traffic Server can attempt to resolve unqualified hostnames by
expanding to the local domain. For example if a client makes a
request to an unqualified host (``host_x``) and the Traffic Server
local domain is ``y.com`` , then Traffic Server will expand the
hostname to ``host_x.y.com``.

.. ts:cv:: CONFIG proxy.config.dns.splitDNS.enabled INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) DNS server selection. When enabled, Traffic Server refers to the :file:`splitdns.config` file for
   the selection specification. Refer to :ref:`Configuring DNS Server Selection (Split DNS) <configuring-dns-server-selection-split-dns>`.

.. ts:cv:: CONFIG proxy.config.dns.url_expansions STRING NULL

   Specifies a list of hostname extensions that are automatically added to the hostname after a failed lookup. For example: if you want
   Traffic Server to add the hostname extension .org, then specify ``org`` as the value for this variable (Traffic Server automatically
   adds the dot (.)).

.. note::

   If the variable :ts:cv:`proxy.config.http.enable_url_expandomatic` is set to ``1`` (the default value), then you do not have to
   add *``www.``* and *``.com``* to this list because Traffic Server automatically tries www. and .com after trying the values
   you've specified.

.. ts:cv:: CONFIG proxy.config.dns.resolv_conf STRING /etc/resolv.conf

   Allows to specify which ``resolv.conf`` file to use for finding resolvers. While the format of this file must be the same as the
   standard ``resolv.conf`` file, this option allows an administrator to manage the set of resolvers in an external configuration file,
   without affecting how the rest of the operating system uses DNS.

.. ts:cv:: CONFIG proxy.config.dns.round_robin_nameservers INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) DNS server round-robin.

.. ts:cv:: CONFIG proxy.config.dns.nameservers STRING NULL
   :reloadable:

   The DNS servers.

.. ts:cv:: CONFIG proxy.config.srv_enabled INT 0
   :reloadable:

   Indicates whether to use SRV records for orgin server lookup.

.. ts:cv:: CONFIG proxy.config.dns.dedicated_thread INT 0

   Create and dedicate a thread entirely for DNS processing. This is probably
   most useful on system which do a significant number of DNS lookups,
   typically forward proxies. But even on other systems, it can avoid some
   contention on the first worker thread (which otherwise takes on the burden of
   all DNS lookups).

HostDB
======

.. ts:cv:: CONFIG proxy.config.hostdb.serve_stale_for INT
   :metric: seconds

   The number of seconds for which to use a stale NS record while initiating a
   background fetch for the new data.

   If not set then stale records are not served.

.. ts:cv:: CONFIG proxy.config.hostdb.storage_size INT 33554432
   :metric: bytes

   The amount of space (in bytes) used to store ``hostdb``.
   The value of this variable must be increased if you increase the size of the
   `proxy.config.hostdb.size`_ variable.

.. ts:cv:: CONFIG proxy.config.hostdb.size INT 200000

   The maximum number of entries that can be stored in the database.

.. note::

   For values above ``200000``, you must increase :ts:cv:`proxy.config.hostdb.storage_size` by at least 44 bytes per entry.

.. ts:cv:: CONFIG proxy.config.hostdb.ttl_mode INT 0
   :reloadable:

   A host entry will eventually time out and be discarded. This variable controls how that time is calculated. A DNS
   request will return a TTL value and an internal value can be set with :ts:cv:`proxy.config.hostdb.timeout`. This
   variable determines which value will be used.

   =====    ===
   Value    TTL
   =====    ===
   0        The TTL from the DNS response.
   1        The internal timeout value.
   2        The smaller of the DNS and internal TTL values. The internal timeout value becomes a maximum TTL.
   3        The larger of the DNS and internal TTL values. The internal timeout value become a minimum TTL.
   =====    ===

.. ts:cv:: CONFIG proxy.config.hostdb.timeout INT 1440
   :metric: minutes
   :reloadable:

   Internal time to live value for host DB entries, **in minutes**.

   See :ts:cv:`proxy.config.hostdb.ttl_mode` for when this value is used.

.. ts:cv:: CONFIG proxy.config.hostdb.strict_round_robin INT 0
   :reloadable:

   Set host resolution to use strict round robin.

When this and :ts:cv:`proxy.config.hostdb.timed_round_robin` are both disabled (set to ``0``), Traffic Server always
uses the same origin server for the same client, for as long as the origin server is available. Otherwise if this is
set then IP address is rotated on every request. This setting takes precedence over
:ts:cv:`proxy.config.hostdb.timed_round_robin`.

.. ts:cv:: CONFIG proxy.config.hostdb.timed_round_robin INT 0
   :reloadable:

   Set host resolution to use timed round robin.

When this and :ts:cv:`proxy.config.hostdb.strict_round_robin` are both disabled (set to ``0``), Traffic Server always
uses the same origin server for the same client, for as long as the origin server is available. Otherwise if this is
set to :arg:`N` the IP address is rotated if more than :arg:`N` seconds have past since the first time the
current address was used.

.. ts:cv:: CONFIG proxy.config.hostdb.ip_resolve STRING ipv4;ipv6

   Set the host resolution style.

This is an ordered list of keywords separated by semicolons that specify how a host name is to be resolved to an IP address. The keywords are case
insensitive.

=======  =======
Keyword  Meaning
=======  =======
ipv4     Resolve to an IPv4 address.
ipv6     Resolve to an IPv6 address.
client   Resolve to the same family as the client IP address.
none     Stop resolving.
=======  =======

The order of the keywords is critical. When a host name needs to be resolved it is resolved in same order as the
keywords. If a resolution fails, the next option in the list is tried. The keyword ``none`` means to give up resolution
entirely. The keyword list has a maximum length of three keywords, more are never needed. By default there is an
implicit ``ipv4;ipv6`` attached to the end of the string unless the keyword ``none`` appears.

.. topic:: Example

   Use the incoming client family, then try IPv4 and IPv6. ::

      client;ipv4;ipv6

   Because of the implicit resolution this can also be expressed as just ::

      client

.. topic:: Example

   Resolve only to IPv4. ::

      ipv4;none

.. topic:: Example

   Resolve only to the same family as the client (do not permit cross family transactions). ::

      client;none

This value is a global default that can be overridden by :ts:cv:`proxy.config.http.server_ports`.

.. note::

   This style is used as a convenience for the administrator. During a resolution the *resolution order* will be
   one family, then possibly the other. This is determined by changing ``client`` to ``ipv4`` or ``ipv6`` based on the
   client IP address and then removing duplicates.

.. important::

   This option has no effect on outbound transparent connections The local IP address used in the connection to the
   origin server is determined by the client, which forces the IP address family of the address used for the origin
   server. In effect, outbound transparent connections always use a resolution style of "``client``".

Logging Configuration
=====================

.. ts:cv:: CONFIG proxy.config.log.logging_enabled INT 3
   :reloadable:

   Enables and disables event logging:

   -  ``0`` = logging disabled
   -  ``1`` = log errors only
   -  ``2`` = log transactions only
   -  ``3`` = full logging (errors + transactions)

   Refer to :ref:`working-with-log-files`.

.. ts:cv:: CONFIG proxy.config.log.max_secs_per_buffer INT 5
   :reloadable:

   The maximum amount of time before data in the buffer is flushed to disk.

.. ts:cv:: CONFIG proxy.config.log.max_space_mb_for_logs INT 2000
   :metric: megabytes
   :reloadable:

   The amount of space allocated to the logging directory (in MB).

.. note::

   All files in the logging directory contribute to the space used, even if they are not log files. In collation client
   mode, if there is no local disk logging, or :ts:cv:`proxy.config.log.max_space_mb_for_orphan_logs` is set to a higher
   value than :ts:cv:`proxy.config.log.max_space_mb_for_logs`, TS will take
   :ts:cv:`proxy.config.log.max_space_mb_for_orphan_logs` for maximum allowed log space.

.. ts:cv:: CONFIG proxy.config.log.max_space_mb_for_orphan_logs INT 25
   :metric: megabytes
   :reloadable:

   The amount of space allocated to the logging directory (in MB) if this node is acting as a collation client.

.. note::

   When max_space_mb_for_orphan_logs is take as the maximum allowedlog space in the logging system, the same rule apply
   to proxy.config.log.max_space_mb_for_logs also apply to proxy.config.log.max_space_mb_for_orphan_logs, ie: All files
   in the logging directory contribute to the space used, even if they are not log files. you may need to consider this
   when you enable full remote logging, and bump to the same size as proxy.config.log.max_space_mb_for_logs.

.. ts:cv:: CONFIG proxy.config.log.max_space_mb_headroom INT 10
   :metric: megabytes
   :reloadable:

   The tolerance for the log space limit (in megabytes). If the variable :ts:cv:`proxy.config.log.auto_delete_rolled_files` is set to ``1``
   (enabled), then autodeletion of log files is triggered when the amount of free space available in the logging directory is less than
   the value specified here.

.. ts:cv:: CONFIG proxy.config.log.hostname STRING localhost
   :reloadable:

   The hostname of the machine running Traffic Server.

.. ts:cv:: CONFIG proxy.config.log.logfile_dir STRING install_dir\ ``/logs``
   :reloadable:

   The full path to the logging directory. This can be an absolute path or a path relative to the directory in which Traffic Server is installed.

   .. note:: The directory you specify must already exist.

.. ts:cv:: CONFIG proxy.config.log.logfile_perm STRING rw-r--r--
   :reloadable:

   The log file permissions. The standard UNIX file permissions are used (owner, group, other). Permissible values are:

   ``-`` no permission ``r`` read permission ``w`` write permission ``x`` execute permission

   Permissions are subject to the umask settings for the Traffic Server process. This means that a umask setting of\ ``002`` will not allow
   write permission for others, even if specified in the configuration file. Permissions for existing log files are not changed when the
   configuration is changed.

.. ts:cv:: CONFIG proxy.config.log.custom_logs_enabled INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) custom logging.

.. ts:cv:: CONFIG proxy.config.log.squid_log_enabled INT 1
   :reloadable:

   Enables (``1``) or disables (``0``) the `squid log file format <../working-log-files/log-formats#SquidFormat>`_.

.. ts:cv:: CONFIG proxy.config.log.squid_log_is_ascii INT 1
   :reloadable:

   The squid log file type:

   -  ``1`` = ASCII
   -  ``0`` = binary

.. ts:cv:: CONFIG proxy.config.log.squid_log_name STRING squid
   :reloadable:

   The `squid log <../working-log-files/log-formats#SquidFormat>`_ filename.

.. ts:cv:: CONFIG proxy.config.log.squid_log_header STRING NULL

   The `squid log <../working-log-files/log-formats#SquidFormat>`_ file header text.

.. ts:cv:: CONFIG proxy.config.log.common_log_enabled INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) the `Netscape common log file format <../working-log-files/log-formats#NetscapeFormats>`_.

.. ts:cv:: CONFIG proxy.config.log.common_log_is_ascii INT 1
   :reloadable:

   The `Netscape common log <../working-log-files/log-formats#NetscapeFormats>`_ file type:

   -  ``1`` = ASCII
   -  ``0`` = binary

.. ts:cv:: CONFIG proxy.config.log.common_log_name STRING common
   :reloadable:

   The `Netscape common log <../working-log-files/log-formats#NetscapeFormats>`_ filename.

.. ts:cv:: CONFIG proxy.config.log.common_log_header STRING NULL
   :reloadable:

   The `Netscape common log <../working-log-files/log-formats#NetscapeFormats>`_ file header text.

.. ts:cv:: CONFIG proxy.config.log.extended_log_enabled INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) the `Netscape extended log file format <../working-log-files/log-formats#NetscapeFormats>`_.

.. ts:cv:: CONFIG proxy.confg.log.extended_log_is_ascii INT 1

   The `Netscape extended log <../working-log-files/log-formats#NetscapeFormats>`_ file type:

   -  ``1`` = ASCII
   -  ``0`` = binary

.. ts:cv:: CONFIG proxy.config.log.extended_log_name STRING extended

   The `Netscape extended log <../working-log-files/log-formats#NetscapeFormats>`_ filename.

.. ts:cv:: CONFIG proxy.config.log.extended_log_header STRING NULL
   :reloadable:

   The `Netscape extended log <../working-log-files/log-formats#NetscapeFormats>`_ file header text.

.. ts:cv:: CONFIG proxy.config.log.extended_log_is_ascii INT 0

   Set whether the extend log is written as ASCII (text) or binary.

.. ts:cv:: CONFIG proxy.config.log.extended2_log_enabled INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) the `Netscape Extended-2 log file format <../working-log-files/log-formats#NetscapeFormats>`_.

.. ts:cv:: CONFIG proxy.config.log.extended2_log_is_ascii INT 1
   :reloadable:

   The `Netscape Extended-2 log <../working-log-files/log-formats#NetscapeFormats>`_ file type:

   -  ``1`` = ASCII
   -  ``0`` = binary

.. ts:cv:: CONFIG proxy.config.log.extended2_log_name STRING extended2
   :reloadable:

   The `Netscape Extended-2 log <../working-log-files/log-formats#NetscapeFormats>`_ filename.

.. ts:cv:: CONFIG proxy.config.log.extended2_log_header STRING NULL
   :reloadable:

   The `Netscape Extended-2 log <../working-log-files/log-formats#NetscapeFormats>`_ file header text.

.. ts:cv:: CONFIG proxy.config.log.separate_icp_logs INT 0
   :reloadable:

   When enabled (``1``), configures Traffic Server to store ICP transactions in a separate log file.

   -  ``0`` = separation is disabled, all ICP transactions are recorded in the same file as HTTP transactions
   -  ``1`` = all ICP transactions are recorded in a separate log file.
   -  ``-1`` = filter all ICP transactions from the default log files; ICP transactions are not logged anywhere.

.. ts:cv:: CONFIG proxy.config.log.separate_host_logs INT 0
   :reloadable:

   When enabled (``1``), configures Traffic Server to create a separate log file for HTTP transactions for each origin server listed in the
   :file:`log_hosts.config` file. Refer to `HTTP Host Log Splitting <../working-log-files#HTTPHostLogSplitting>`_.

.. ts:cv:: LOCAL proxy.local.log.collation_mode INT 0
   :reloadable:

   Set the log collation mode.

===== ======
Value Effect
===== ======
0     collation is disabled
1     this host is a log collation server
2     this host is a collation client and sends entries using standard formats to the collation server
3     this host is a collation client and sends entries using the traditional custom formats to the collation server
4     this host is a collation client and sends entries that use both the standard and traditional custom formats to the collation server
===== ======

For information on sending XML-based custom formats to the collation
server, refer to `logs_xml.config <logs_xml.config>`_.

.. note:: Although Traffic Server supports traditional custom logging, you should use the more versatile XML-based custom formats.

.. ts:cv:: CONFIG proxy.config.log.collation_host STRING NULL

   The hostname of the log collation server.

.. ts:cv:: CONFIG proxy.config.log.collation_port INT 8085
   :reloadable:

   The port used for communication between the collation server and client.

.. ts:cv:: CONFIG proxy.config.log.collation_secret STRING foobar
   :reloadable:

   The password used to validate logging data and prevent the exchange of unauthorized information when a collation server is being used.

.. ts:cv:: CONFIG proxy.config.log.collation_host_tagged INT 0
   :reloadable:

   When enabled (``1``), configures Traffic Server to include the hostname of the collation client that generated the log entry in each entry.

.. ts:cv:: CONFIG proxy.config.log.collation_retry_sec INT 5
   :reloadable:

   The number of seconds between collation server connection retries.

.. ts:cv:: CONFIG proxy.config.log.rolling_enabled INT 1
   :reloadable:

   Specifies how log files are rolled. You can specify the following values:

   -  ``0`` = disables log file rolling
   -  ``1`` = enables log file rolling at specific intervals during the day (specified with the
       `proxy.config.log.rolling_interval_sec`_ and `proxy.config.log.rolling_offset_hr`_ variables)
   -  ``2`` = enables log file rolling when log files reach a specific size (specified with the `proxy.config.log.rolling_size_mb`_ variable)
   -  ``3`` = enables log file rolling at specific intervals during the day or when log files reach a specific size (whichever occurs first)
   -  ``4`` = enables log file rolling at specific intervals during the day when log files reach a specific size (i.e., at a specified
       time if the file is of the specified size)

.. ts:cv:: CONFIG proxy.config.log.rolling_interval_sec INT 86400
   :reloadable:

   The log file rolling interval, in seconds. The minimum value is ``300`` (5 minutes). The maximum, and default, value is 86400 seconds (one day).

   .. note:: If you start Traffic Server within a few minutes of the next rolling time, then rolling might not occur until the next rolling time.

.. ts:cv:: CONFIG proxy.config.log.rolling_offset_hr INT 0
   :reloadable:

   The file rolling offset hour. The hour of the day that starts the log rolling period.

.. ts:cv:: CONFIG proxy.config.log.rolling_size_mb INT 10
   :reloadable:

   The size that log files must reach before rolling takes place.

.. ts:cv:: CONFIG proxy.config.log.auto_delete_rolled_files INT 1
   :reloadable:

   Enables (``1``) or disables (``0``) automatic deletion of rolled files.

.. ts:cv:: CONFIG proxy.config.log.sampling_frequency INT 1
   :reloadable:

   Configures Traffic Server to log only a sample of transactions rather than every transaction. You can specify the following values:

   -  ``1`` = log every transaction
   -  ``2`` = log every second transaction
   -  ``3`` = log every third transaction and so on...

.. ts:cv:: CONFIG proxy.config.http.slow.log.threshold INT 0
   :reloadable:
   :metric: milliseconds

   If set to a non-zero value :arg:`N` then any connection that takes longer than :arg:`N` milliseconds from accept to
   completion will cause its timing stats to be written to the :ts:cv:`debugging log file
   <proxy.config.output.logfile>`. This is identifying data about the transaction and all of the :c:type:`transaction milestones <TSMilestonesType>`.

Diagnostic Logging Configuration
================================

.. ts:cv:: CONFIG proxy.config.diags.output.status STRING

.. ts:cv:: CONFIG proxy.config.diags.output.warning STRING

.. ts:cv:: CONFIG proxy.config.diags.output.emergency STRING

   control where Traffic Server should log diagnostic output. Messages at diagnostic level can be directed to any combination of diagnostic
   destinations. Valid diagnostic message destinations are:::

   * 'O' = Log to standard output
   * 'E' = Log to standard error
   * 'S' = Log to syslog
   * 'L' = Log to diags.log

.. topic:: Example

   To log debug diagnostics to both syslog and diags.log:::

        proxy.config.diags.output.debug STRING SL

Reverse Proxy
=============

.. ts:cv:: CONFIG proxy.config.reverse_proxy.enabled INT 1
   :reloadable:

   Enables (``1``) or disables (``0``) HTTP reverse proxy.

.. ts:cv:: CONFIG proxy.config.header.parse.no_host_url_redirect STRING NULL
   :reloadable:

   The URL to which to redirect requests with no host headers (reverse
   proxy).

URL Remap Rules
===============

.. ts:cv:: CONFIG proxy.config.url_remap.filename STRING remap.config

   Sets the name of the :file:`remap.config` file.

.. ts:cv:: CONFIG proxy.config.url_remap.default_to_server_pac INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) requests for a PAC file on the proxy service port (8080 by default) to be redirected to the PAC
   port. For this type of redirection to work, the variable `proxy.config.reverse_proxy.enabled`_ must be set to ``1``.

.. ts:cv:: CONFIG proxy.config.url_remap.default_to_server_pac_port INT -1
   :reloadable:

   Sets the PAC port so that PAC requests made to the Traffic Server
   proxy service port are redirected this port. ``-1`` is the default
   setting that sets the PAC port to the autoconfiguration port (the
   default autoconfiguration port is 8083). This variable can be used
   together with the `proxy.config.url_remap.default_to_server_pac`_
   variable to get a PAC file from a different port. You must create
   and run a process that serves a PAC file on this port. For example:
   if you create a Perl script that listens on port 9000 and writes a
   PAC file in response to any request, then you can set this variable
   to ``9000``. Browsers that request the PAC file from a proxy server
   on port 8080 will get the PAC file served by the Perl script.

.. ts:cv:: CONFIG proxy.config.url_remap.remap_required INT 1
   :reloadable:

   Set this variable to ``1`` if you want Traffic Server to serve
   requests only from origin servers listed in the mapping rules of the
   :file:`remap.config` file. If a request does not match, then the browser
   will receive an error.

.. ts:cv:: CONFIG proxy.config.url_remap.pristine_host_hdr INT 1
   :reloadable:

   Set this variable to ``1`` if you want to retain the client host
   header in a request during remapping.

.. _records-config-ssl-termination:

SSL Termination
===============

.. ts:cv:: CONFIG proxy.config.ssl.SSLv2 INT 0

   Enables (``1``) or disables (``0``) SSLv2. Please don't enable it.

.. ts:cv:: CONFIG proxy.config.ssl.SSLv3 INT 1

   Enables (``1``) or disables (``0``) SSLv3.

.. ts:cv:: CONFIG proxy.config.ssl.TLSv1 INT 1

   Enables (``1``) or disables (``0``) TLSv1.

.. ts:cv:: CONFIG proxy.config.ssl.client.certification_level INT 0

   Sets the client certification level:

   -  ``0`` = no client certificates are required. Traffic Server does
       not verify client certificates during the SSL handshake. Access
       to Traffic Server depends on Traffic Server configuration options
       (such as access control lists).

   -  ``1`` = client certificates are optional. If a client has a
       certificate, then the certificate is validated. If the client
       does not have a certificate, then the client is still allowed
       access to Traffic Server unless access is denied through other
       Traffic Server configuration options.

   -  ``2`` = client certificates are required. The client must be
       authenticated during the SSL handshake. Clients without a
       certificate are not allowed to access Traffic Server.

.. ts:cv:: CONFIG proxy.config.ssl.server.multicert.filename STRING ssl_multicert.config

   The location of the :file:`ssl_multicert.config` file, relative
   to the Traffic Server configuration directory. In the following
   example, if the Traffic Server configuration directory is
   `/etc/trafficserver`, the Traffic Server SSL configuration file
   and the corresponding certificates are located in
   `/etc/trafficserver/ssl`::

      CONFIG proxy.config.ssl.server.multicert.filename STRING ssl/ssl_multicert.config
      CONFIG proxy.config.ssl.server.cert.path STRING etc/trafficserver/ssl
      CONFIG proxy.config.ssl.server.private_key.path STRING etc/trafficserver/ssl

.. ts:cv:: CONFIG proxy.config.ssl.server.cert.path STRING /config

   The location of the SSL certificates and chains used for accepting
   and validation new SSL sessions. If this is a relative path,
   it is appended to the Traffic Server installation PREFIX. All
   certificates and certificate chains listed in
   :file:`ssl_multicert.config` will be loaded relative to this path.

.. ts:cv:: CONFIG proxy.config.ssl.server.private_key.path STRING NULL

   The location of the SSL certificate private keys. Change this
   variable only if the private key is not located in the SSL
   certificate file. All private keys listed in
   :file:`ssl_multicert.config` will be loaded relative to this
   path.

.. ts:cv:: CONFIG proxy.config.ssl.server.cert_chain.filename STRING NULL

   The name of a file containing a global certificate chain that
   should be used with every server certificate. This file is only
   used if there are certificates defined in :file:`ssl_multicert.config`.
   Unless this is an absolute path, it is loaded relative to the
   path specified by :ts:cv:`proxy.config.ssl.server.cert.path`.

.. ts:cv:: CONFIG proxy.config.ssl.CA.cert.path STRING NULL

   The location of the certificate authority file that client
   certificates will be verified against.

.. ts:cv:: CONFIG proxy.config.ssl.CA.cert.filename STRING NULL

   The filename of the certificate authority that client certificates
   will be verified against.

.. ts:cv:: CONFIG proxy.config.ssl.auth.enabled INT 0

   TBD

Client-Related Configuration
----------------------------

.. ts:cv:: CONFIG proxy.config.ssl.client.verify.server INT 0

   Configures Traffic Server to verify the origin server certificate
   with the Certificate Authority (CA).

.. ts:cv:: CONFIG proxy.config.ssl.client.cert.filename STRING NULL

   The filename of SSL client certificate installed on Traffic Server.

.. ts:cv:: CONFIG proxy.config.ssl.client.cert.path STRING /config

   The location of the SSL client certificate installed on Traffic
   Server.

.. ts:cv:: CONFIG proxy.config.ssl.client.private_key.filename STRING NULL

   The filename of the Traffic Server private key. Change this variable
   only if the private key is not located in the Traffic Server SSL
   client certificate file.

.. ts:cv:: CONFIG proxy.config.ssl.client.private_key.path STRING NULL

   The location of the Traffic Server private key. Change this variable
   only if the private key is not located in the SSL client certificate
   file.

.. ts:cv:: CONFIG proxy.config.ssl.client.CA.cert.filename STRING NULL

   The filename of the certificate authority against which the origin
   server will be verified.

.. ts:cv:: CONFIG proxy.config.ssl.client.CA.cert.path STRING NULL

   Specifies the location of the certificate authority file against
   which the origin server will be verified.

ICP Configuration
=================

.. ts:cv:: CONFIG proxy.config.icp.enabled INT 0

   Sets ICP mode for hierarchical caching:

   -  ``0`` = disables ICP
   -  ``1`` = allows Traffic Server to receive ICP queries only
   -  ``2`` = allows Traffic Server to send and receive ICP queries

   Refer to `ICP Peering <../hierachical-caching#ICPPeering>`_.

.. ts:cv:: CONFIG proxy.config.icp.icp_interface STRING your_interface

   Specifies the network interface used for ICP traffic.

   .. note::

       The Traffic Server installation script detects your
       network interface and sets this variable appropriately. If your
       system has multiple network interfaces, check that this variable
       specifies the correct interface.

.. ts:cv:: CONFIG proxy.config.icp.icp_port INT 3130
   :reloadable:

   Specifies the UDP port that you want to use for ICP messages.

.. ts:cv:: CONFIG proxy.config.icp.query_timeout INT 2
   :reloadable:

   Specifies the timeout used for ICP queries.

Scheduled Update Configuration
==============================

.. ts:cv:: CONFIG proxy.config.update.enabled INT 0

   Enables (``1``) or disables (``0``) the Scheduled Update option.

.. ts:cv:: CONFIG proxy.config.update.force INT 0
   :reloadable:

   Enables (``1``) or disables (``0``) a force immediate update. When
   enabled, Traffic Server overrides the scheduling expiration time for
   all scheduled update entries and initiates updates until this option
   is disabled.

.. ts:cv:: CONFIG proxy.config.update.retry_count INT 10
   :reloadable:

   Specifies the number of times Traffic Server can retry the scheduled
   update of a URL in the event of failure.

.. ts:cv:: CONFIG proxy.config.update.retry_interval INT 2
   :reloadable:

   Specifies the delay (in seconds) between each scheduled update retry
   for a URL in the event of failure.

.. ts:cv:: CONFIG proxy.config.update.concurrent_updates INT 100
   :reloadable:

   Specifies the maximum simultaneous update requests allowed at any
   time. This option prevents the scheduled update process from
   overburdening the host.

Remap Plugin Processor
======================

.. ts:cv:: CONFIG proxy.config.remap.use_remap_processor INT 0

   Enables (``1``) or disables (``0``) the ability to run separate threads for remap plugin processing.

.. ts:cv:: CONFIG proxy.config.remap.num_remap_threads INT 1

   Specifies the number of threads that will be used for remap plugin rocessing.

Plug-in Configuration
=====================

.. ts:cv:: CONFIG proxy.config.plugin.plugin_dir STRING config/plugins

   Specifies the location of Traffic Server plugins.

Sockets
=======

.. ts:cv:: CONFIG proxy.config.net.defer_accept INT `1`

   default: ``1`` meaning ``on`` all Platforms except Linux: ``45`` seconds

   This directive enables operating system specific optimizations for a listening socket. ``defer_accept`` holds a call to ``accept(2)``
   back until data has arrived. In Linux' special case this is up to a maximum of 45 seconds.

.. ts:cv:: CONFIG proxy.config.net.sock_send_buffer_size_in INT 0

   Sets the send buffer size for connections from the client to Traffic Server.

.. ts:cv:: CONFIG proxy.config.net.sock_recv_buffer_size_in INT 0

   Sets the receive buffer size for connections from the client to Traffic Server.

.. ts:cv:: CONFIG proxy.config.net.sock_option_flag_in INT 0

   Turns different options "on" for the socket handling client connections:::

        TCP_NODELAY (1)
        SO_KEEPALIVE (2)

   .. note::

       This is a flag and you look at the bits set. Therefore,
       you must set the value to ``3`` if you want to enable both options
       above.

.. ts:cv:: CONFIG proxy.config.net.sock_send_buffer_size_out INT 0

   Sets the send buffer size for connections from Traffic Server to the origin server.

.. ts:cv:: CONFIG proxy.config.net.sock_recv_buffer_size_out INT 0

   Sets the receive buffer size for connections from Traffic Server to
   the origin server.

.. ts:cv:: CONFIG proxy.config.net.sock_option_flag_out INT 0

   Turns different options "on" for the origin server socket:::

        TCP_NODELAY (1)
        SO_KEEPALIVE (2)

   .. note::

        This is a flag and you look at the bits set. Therefore,
        you must set the value to ``3`` if you want to enable both options
        above.

.. ts:cv:: CONFIG proxy.config.net.sock_mss_in INT 0

   Same as the command line option ``--accept_mss`` that sets the MSS for all incoming requests.

Undocumented
============

These are referenced but not documented. Please contribute a definition.

.. ts:cv:: CONFIG proxy.config.http.negative_caching_lifetime INT 0

.. ts:cv:: CONFIG proxy.config.task_threads INT 0

.. ts:cv:: CONFIG proxy.config.cache.limits.http.max_alts INT 5

.. ts:cv:: CONFIG proxy.config.http.enabled INT 1
