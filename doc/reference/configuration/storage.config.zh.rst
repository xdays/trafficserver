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
storage.config（中文）
==============

.. configfile:: storage.config

The :file:`storage.config` file lists all the files, directories, and/or
hard disk partitions that make up the Traffic Server cache. After you
modify the :file:`storage.config` file, you must restart Traffic Server.

文件 :file:`storage.config` 列出所有构成Traffic Server的文件，目录和磁盘分区。
修改此文件后需要重启Traffic Server。

Format
======

The format of the :file:`storage.config` file is::

   pathname size volume=volume_number

文件 :file:`storage.config` 的格式如下::

   pathname size volume=volume_number

where :arg:`pathname` is the name of a partition, directory or file, :arg:`size`
is the size of the named partition, directory or file (in bytes), and
:arg:`volume` is the volume number that is used in :file:`volume.config`
and :file:`hosting.config`. You must specify a size for directories or
files; size is optional for raw partitions. :arg:`volume` is optional.

这里的 :arg:`pathname` 是分区，目录或者文件的名字，  :arg:`size` 是其大小，单位是byte，
:arg:`volume` 是用于 :file:`volume.config` 和 :file:`hosting.config` 文件的卷编号。
你必须给文件或者目录指定大小；裸盘的大小参数不是必须的。 :arg:`volume` 参数是可选的。

You can use any partition of any size. For best performance:

-  Use raw disk partitions.
-  For each disk, make all partitions the same size.
-  For each node, use the same number of partitions on all disks.
-  Group similar kinds of storage into different volumes. For example
   split out SSD's or RAM drives into their own volume.

你可以是使用任何大小的任何分区。考虑到性能：

-  使用裸盘分区
-  对于每个磁盘，尽量让每个分区大小一样
-  对于每个节点，使用相同数量的磁盘分区
-  把相同的存储组合到同一个卷里。比如把SSD和内存分区分隔到不同的卷。

Specify pathnames according to your operating system requirements. See
the following examples. In the :file:`storage.config` file, a formatted or
raw disk must be at least 128 MB.

根据你的操作系统来指定路径。具体看下面的例子。 在文件  :file:`storage.config` 中
一个格式化的磁盘或者裸盘必须有128MB。

When using raw disk or partitions, you should make sure the :ts:cv:`Traffic
Server user <proxy.config.admin.user_id>` used by the Traffic Server process
has read and write privileges on the raw disk device or partition. One good
practice is to make sure the device file is set with 'g+rw' and the Traffic
Server user is in the group which owns the device file.  However, some
operating systems have stronger requirements - see the following examples for
more information.

当使用裸盘或者分区时，你要确保Traffic Server进程使用的 :ts:cv:`Traffic Server
user <proxy.config.admin.user_id>` 用户对裸盘或者分区有读写的权限。 一个好的方法
是给设备文件的组用户赋予 'rw' 的权限，然后把Traffic Server用户加入到此设备文件所
属的用户组。 但是有些操作系统有更强的限制 - 具体看下边的例子吧。

As with standard ``records.config`` integers, human readable prefixes are also
supported. They include

   - ``K`` Kilobytes (1024 bytes)
   - ``M`` Megabytes (1024^2 or 1,048,576 bytes)
   - ``G`` Gigabytes (1024^3 or 1,073,741,824 bytes
   - ``T`` Terabytes (1024^4 or 1,099,511,627,776 bytes)

和标准的 ``records.config`` 整数一样，也支持友好的前缀。包括

   - ``K`` Kilobytes (1024 bytes)
   - ``M`` Megabytes (1024^2 or 1,048,576 bytes)
   - ``G`` Gigabytes (1024^3 or 1,073,741,824 bytes
   - ``T`` Terabytes (1024^4 or 1,099,511,627,776 bytes)


Examples
========

The following basic example shows 128 MB of cache storage in the
``/big_dir`` directory::

   /big_dir 134217728

下边这个基础的例子表示使用 ``/big_dir`` 的128M作为缓存存储::

   /big_dir 134217728

You can use the ``.`` symbol for the current directory. Here is an
example for 64 MB of cache storage in the current directory::

   . 134217728

你也可以用符号 ``.`` 来表示使用当前目录。下边例子表示使用当前目录的
64M作为缓存存储::

   . 134217728

As an alternative, using the human readable prefixes, you can express a 64GB
cache file with::

   /really_big_dir 64G

此外，使用后缀，你可以表示一个64G的缓存文件::

   /really_big_dir 64G


.. note::
    When using on-filesystem cache disk storage, you can only have one such
    directory specified. This will be address in a future version.

.. note::
    当使用在文件系统之上的磁盘存储时，你只能指定一个目录。这一点会在将来
    的版本中修复。
   

Solaris Example
---------------

The following example is for the Solaris operating system::

   /dev/rdsk/c0t0d0s5
   /dev/rdsk/c0t0d1s5

下边是个Solaris系统的例子::

   /dev/rdsk/c0t0d0s5
   /dev/rdsk/c0t0d1s5

.. note:: Size is optional. If not specified, the entire partition is used.

.. note:: 大小是可选的，如果没有指定就使用整个磁盘

Linux Example
-------------

The following example will use an entire raw disk in the Linux operating
system::

   /dev/sde volume=1
   /dev/sdf volume=2

下边的例子会使用Linux的整个裸盘::

   /dev/sde volume=1
   /dev/sdf volume=2

In order to make sure :program:`traffic_server` will have access to this disk
you can use :manpage:`udev(7)` to persistently set the right permissions. The
following rules are targeted for an Ubuntu system, and stored in
``/etc/udev/rules.d/51-cache-disk.rules``::

   # Assign /dev/sde and /dev/sdf to the tserver group
   # make the assignment final, no later changes allowed to the group!
   SUBSYSTEM=="block", KERNEL=="sd[ef]", GROUP:="tserver"

为了确保让 :program:`traffic_server` 程序有对磁盘的读写权限，你可以用  
:manpage:`udev(7)` 来设置合适的权限。 如下是适合Ubuntu系统的权限，保存在
``/etc/udev/rules.d/51-cache-disk.rules``::

   # Assign /dev/sde and /dev/sdf to the tserver group
   # make the assignment final, no later changes allowed to the group!
   SUBSYSTEM=="block", KERNEL=="sd[ef]", GROUP:="tserver"

FreeBSD Example
---------------

Starting with 5.1 FreeBSD dropped support for explicit raw devices. All
devices on FreeBSD can be accessed raw now.

从5.1的版本开始FreeBSD放弃了对显式裸盘的支持。FreeBSD上的所有设备都可裸读。

The following example will use an entire raw disk in the FreeBSD
operating system::

   /dev/ada1
   /dev/ada2

下边这个例子会使用FreeBSD上的所有裸盘::

   /dev/ada1
   /dev/ada2

In order to make sure :program:`traffic_server` will have access to this disk
you can use :manpage:`devfs(8)` to persistently set the right permissions. The
following rules are stored in :manpage:`devfs.conf(5)`::

   # Assign /dev/ada1 and /dev/ada2 to the tserver user
   own    ada[12]  tserver:tserver

为了确保让 :program:`traffic_server` 程序有对磁盘的读写权限，你可以用
:manpage:`devfs(8)` 来设置合适的权限。下边是 :manpage:`devfs.conf(5)` 的规则::

   # Assign /dev/ada1 and /dev/ada2 to the tserver user
   own    ada[12]  tserver:tserver
