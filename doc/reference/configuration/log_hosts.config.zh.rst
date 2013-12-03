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

================
log_hosts.config（中文）
================

.. configfile:: log_hosts.config

To record HTTP transactions for different origin servers in separate log
files, you must list each origin server hostname in the
:file:`log_hosts.config` file. In addition, you must enable the `HTTP Host
Log Splitting <../working-log-files#HTTPHostLogSplitting>`_ option. You
should use the same :file:`log_hosts.config` file on every Traffic Server
node in your cluster. After you modify the :file:`log_hosts.config` file,
run the :option:`traffic_line -x` command to apply the changes.
When you apply the changes to a node in a cluster, Traffic Server automatically applies the
changes to all other nodes in the cluster.

用于分别记录每个源站的请求到指定文件里， 需要在 :file:`log_hosts.config` 文件中列出
所有源站的主机名。此外，你需要打开  `HTTP Host Log Splitting <../working-log-files#HTTPHostLogSplitting>`
选项。在集群中的每一台Traffic Server的 :file:`log_hosts.config` 要保持一致。
当你修改了 :file:`hosting.config` 之后，切换到Traffic Server的bin目录，然后
执行 :option:`traffic_line -x` 命令使配置生效，当你在集群中的一个节点使配置生效后，
其他节点自动更新配置。

Format
======

Each line in the :file:`log_hosts.config` file has the following format::

    hostname

文件 :file:`log_hosts.config` 的每一行有如下格式::

    hostname

where ``hostname`` is the hostname of the origin server.

这里的 ``hostname`` 就是源站的主机名

.. hint::

    You can specify keywords in the :file:`log_hosts.config` file to
    record all transactions from origin servers with the specified keyword
    in their names in a separate log file. See the example below.

.. hint::

    在文件 :file:`log_hosts.config` 中你可以指定关键字来把带有这个关键字
    的源站的所有请求记录到单独的文件中，具体看下边的例子。

Examples
========

The following example configures Traffic Server to create separate log
files containing all HTTP transactions for the origin servers
``webserver1``, ``webserver2``, and ``webserver3``::

    webserver1
    webserver2
    webserver3

下边的例子把主机名包含 ``webserver1``, ``webserver2``, and ``webserver3`` 
的源站服务器的所有请求信息记录到单独的日志文件中::

    webserver1
    webserver2
    webserver3

The following example records all HTTP transactions from origin servers
that contain ``sports`` in their names. For example:
``sports.yahoo.com`` and ``www.foxsports.com`` in a log file called
``squid-sport.log`` (the Squid format is enabled)::

    sports

下边的例子把主机名中包含 ``sports`` 的源站，如 ``sports.yahoo.com`` 和
 ``www.foxsports.com`` 的请求信息记录到单独的日志文件 ``squid-sport.log`` 中::

    sports
