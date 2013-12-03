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
hosting.config（中文）
==============

.. configfile:: hosting.config

The :file:`hosting.config` file enables you to assign cache partitions to
specific origin servers and/or domains so that you can manage cache
space efficiently and restrict disk usage. For step-by-step instructions
on partitioning the cache according to origin servers and/or domains,
refer to `Partitioning the Cache <../configuring-cache#PartitoningCache>`_.
Before you can assign cache partitions to specific
origin servers and/or domains, you must first partition your cache
according to size and protocol in the :file:`volume.config`
file. For step-by-step instructions about partitioning your cache, refer
to `Partitioning the Cache <../configuring-cache#PartitioningCache>`_.

:file:`hosting.config` 文件用于给特定源站或者域名指定缓存分区，这样能更好
地使用缓存空间和对磁盘做限制。想了解如何一步一步按源站或者域名限制缓存分区
使用，请参考 `Partitioning the Cache <../configuring-cache#PartitoningCache>`_.
在给源站或者域名配置缓存分区前你需要在 :file:`volume.config` 先根据大小和协议对
你的缓存分区。想了解如何一步一步对缓存分区，请参考 `Partitioning the Cache
<../configuring-cache#PartitioningCache>`_.

After you modify hosting.config, navigate to the Traffic Server bin
directory and run :option:`traffic_line -x` to apply your changes.

When you apply the changes to a node in a cluster, Traffic Server
automatically applies the changes to all other nodes in the cluster.

当你修改了 :file:`hosting.config` 之后，切换到Traffic Server的bin目录，然后
执行 :option:`traffic_line -x` 命令使配置生效，当你在集群中的一个节点使配置
生效后，其他节点自动更新配置。

.. important::

    The :file:`volume.config` configuration must be the same on all nodes in a cluster.

.. important::

    文件 :file:`volume.config` 在集群里必须保持一致。


Format
======

Each line in the :file:`hosting.config` file must have one of the following
formats::

    hostname=HOST partition=NUMBERS
    domain=DOMAIN partition=NUMBERS

文件 :file:`hosting.config` 格式如下::

    hostname=HOST partition=NUMBERS
    domain=DOMAIN partition=NUMBERS

where ``HOST`` is the fully-qualified hostname of the origin server
whose content you want to store on a particular partition (for example,
``www.myhost.com``); ``DOMAIN`` is the domain whose content you
want to store on a particular partition(for example, ``mydomain.com``);
and ``NUMBERS`` is a comma-separated list of the partitions on
which you want to store the content that belongs to the origin server or
domain listed. The partition numbers must be valid numbers listed in the
file:`volume.config`.

这里的 ``HOST`` 是想要缓存到特定分区的服务器的FQDN（比如 ``www.myhost.com`` ）;
``DOMAIN`` 是想要缓存到特定分区服务器的域名（ ``mydoain.com`` ）； ``NUMBERS``
是逗号分隔的属于这个服务器的分区，分区号必须配置到了 :file:`volume.config` 。

**Note:** To allocate more than one partition to an origin server or
domain, you must enter the partitions in a comma-separated list on one
line, as shown in the example below. The
:file:`hosting.config`  file cannot contain multiple entries
for the same origin server or domain.

**注意** 要给源站或者域名指定多个分区，必须用逗号分隔的格式，
:file:`hosting.config` 里不能出现相同的源站和域名。

Generic Partition
=================

When configuring the :file:`hosting.config` file, you must assign a generic
partition to use for content that does not belong to any of the origin
servers or domains listed. If all partitions for a particular origin
server become corrupt, Traffic Server will also use the generic
partition to store content for that origin server.

当配置 :file:`hosting.config` 时你需要配置一个通用分区用来缓存没有匹
配到任何源站或者域名的内容。如果对于摸个源站的所有分区都挂掉了，Traffic Server
就会使用通用的分区。

The generic partition must have the following format::

    hostname=* partition=NUMBERS

通用分区必须是如下格式::

    hostname=* partition=NUMBERS

where ``NUMBERS`` is a comma-separated list of generic
partitions.

这里的 ``NUMBERS`` 是以逗号分隔的分区号。

Examples
========

The following example configures Traffic Server to store content from
the domain ``mydomain.com`` in partition 1 and content from
``www.myhost.com`` in partition 2. Traffic Server stores content from
all other origin servers in partitions 3 and 4.

::

    domain=mydomain.com partition=1
    hostname=www.myhost.com partition=2
    hostname=* partition=3,4

如下配置Traffic Server存储域名 ``mydomain.com`` 的内容到分区1，
``www.myhost.com`` 的内容到分区2。其他域名的内容保存到分区3和4。

::

    domain=mydomain.com partition=1
    hostname=www.myhost.com partition=2
    hostname=* partition=3,4
