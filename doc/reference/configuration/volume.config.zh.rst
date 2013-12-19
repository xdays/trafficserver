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
volume.config（中文）
=============

.. configfile:: volume.config

The :file:`volume.config` file enables you to manage your cache space more
efficiently and restrict disk usage by creating cache volumes of
different sizes for specific protocols. You can further configure these
volumes to store data from certain origin servers and/or domains in the
:file:`hosting.config` file.

文件 :file:`volume.config` 可以让你更有效的管理存储空间，可以通过创建缓存卷
来限制针对特定协议的磁盘。你甚至可以在 :file:`hosting.config` 配置把这些卷用于特
定的源站或者域名。

.. important::

    The volume configuration must be the same on all nodes in
    a cluster. You must stop Traffic Server before you change the cache
    volume size and protocol assignment. For step-by-step instructions about
    partitioning the cache, refer to :ref:`partitioning-the-cache`.

    卷配置必须在集群中保持一致。修改卷和协议分配时必须停止 Traffic Server 
    详细的教程参考  :ref:`partitioning-the-cache`。

Format
======

For each volume you want to create, enter a line with the following
format: ::

    volume=volume_number  scheme=protocol_type  size=volume_size

要创建卷，使用如下格式： ::

    volume=volume_number  scheme=protocol_type  size=volume_size

where ``volume_number`` is a number between 1 and 255 (the maximum
number of volumes is 255) and ``protocol_type`` is ``http``. Traffic
Server supports ``http`` for HTTP volume types; ``volume_size`` is the
amount of cache space allocated to the volume. This value can be either
a percentage of the total cache space or an absolute value. The absolute
value must be a multiple of 128 MB, where 128 MB is the smallest value.
If you specify a percentage, then the size is rounded down to the
closest multiple of 128 MB.

这里的  ``volume_number`` 是介于1到255的一个数值， ``protocol_type`` 是
``http`` 。 Traffic Server支持 ``http`` 卷类型； ``volume_size`` 是分配给
这个卷的缓存空间大小。 这个值可以是整个缓存空间的百分比或者绝对值。绝对至
必须是128M的倍数。如果指定了百分比，大小取小于百分比的128M的最大公倍数。

Each volume is striped across several disks to achieve parallel I/O. For
example: if there are four disks, then a 1-GB volume will have 256 MB on
each disk (assuming each disk has enough free space available). If you
do not allocate all the disk space in the cache, then the extra disk
space is not used. You can use the extra space later to create new
volumes without deleting and clearing the existing volumes.

每个卷被切到几个不同的磁盘来达到并发IO的性能。例如，如果你有四个磁盘，那么
1G的卷将会在每个磁盘上分配256M（假设每个磁盘有足够的空间）。如果你没有把磁盘
所有的空间分配给缓存，那么额外的空间不会被使用。你可以用额外的空间来创建
卷，不需要删除或者清掉已经存在的卷。

Examples
========

The following example partitions the cache evenly between HTTP and HTTPS
requests::

    volume=1 scheme=http size=50%
    volume=2 scheme=https size=50%

下边的例子把缓存空间均分给HTTP和HTTPS::

    volume=1 scheme=http size=50%
    volume=2 scheme=https size=50%
