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
splitdns.config
===============

.. configfile:: splitdns.config

The :file:`splitdns.config` file enables you to specify the DNS server that
Traffic Server should use for resolving hosts under specific conditions.
For more information, refer to :ref:`configuring-dns-server-selection-split-dns`.

文件 :file:`splitdns.config` 用于让Traffic Server在特定条件下使用特定的DNS服务器
来解析主机，详细信息参考  :ref:`configuring-dns-server-selection-split-dns` .

To specify a DNS server, you must supply the following information in
each active line within the file:

-  A primary destination specifier in the form of a destination domain,
   a destination host, or a URL regular expression
-  A set of server directives, listing one or more DNS servers with
   corresponding port numbers

要指定一台DNS服务器，你需要在每一行配置如下信息：

-  基础目标标识符，格式如域名，主机名，URL正则表达式
-  服务器指令指定DNS服务器和端口号

You can also include the following optional information with each DNS
server specification:

-  A default domain for resolving hosts
-  A search list specifying the domain search order when multiple
   domains are specified

你也可以给DNS服务器指定可选的信息：

-  要解析主机的默认的域
-  当指定多个域时搜索列表顺序

After you modify the :file:`splitdns.config` file,
run the :option:`traffic_line -x`
command to apply the changes. When you apply changes to a node in a
cluster, Traffic Server automatically applies the changes to all other
nodes in the cluster.

在你修改 :file:`splitdns.config` 文件之后，运行 :option:`traffic_line -x` 
使配置生效。当你改变集群中的一台设备的配置后其他节点自动更新配置。

Format
======

Each line in the :file:`splitdns.config` file uses one of the following
formats: ::

    dest_domain=dest_domain | dest_host | url_regex named=dns_server def_domain=def_domain search_list=search_list

文件 :file:`splitdns.config` 中的每一行使用如下的格式: ::

    dest_domain=dest_domain | dest_host | url_regex named=dns_server def_domain=def_domain search_list=search_list

The following list describes each field.

下面列举了每个字段的描述。

.. _splitdns-config-format-dest-domain:

``dest_domain``
    A valid domain name. This specifies that DNS server selection will
    be based on the destination domain. You can prefix the domain with
    an exclamation mark (``!``) to indicate the NOT logical operator.

    合法的域名。指定了给予域名的DNS服务器选择规则。可以通过在域名前加排除符号（ ``!`` ）
    来达到逻辑非的操作。

.. _splitdns-config-format-dest-host:

``dest_host``
    A valid hostname. This specifies that DNS server selection will be
    based on the destination host. You can prefix the host with an
    exclamation mark (``!``) to indicate the ``NOT`` logical operator.

    合法的主机名。指定了给予目标主机名的DNS服务器选择规则。可以通过在域名前加排除符号（ ``!`` ）
    来达到逻辑非的操作。

.. _splitdns-config-format-url-regex:

``url_regex``
    A valid URL regular expression. This specifies that DNS server
    selection will be based on a regular expression.

    URL正则表达式。指定了基于正则表达式的DNS服务器选择规则。

.. _splitdns-config-format-dns-server:

``dns_server``
    This is a required directive. It identifies the DNS server that
    Traffic Server should use with the given destination specifier. You
    can specify a port using a colon (``:``). If you do not specify a
    port, then 53 is used. Specify multiple DNS servers with spaces or
    semicolons (``;``) as separators.

    必须的字段。 指定了Traffic Server对指定的目标使用的DNS服务器。你可以
    指定冒号配置端口号。如果你不指定端口好，默认使用53端口，多个DNS服务器
    用空格或者分号分隔。

    You must specify the domains with IP addresses in CIDR ("dot")
    notation.

    你必须用CIDR格式的域。

.. _splitdns-config-format-def-domain:

``def_domain``
    A valid domain name. This optional directive specifies the default
    domain name to use for resolving hosts. Only one entry is allowed.
    If you do not provide the default domain, the system determines its
    value from ``/etc/resolv.conf``

    合法的域名。这是一个可选的指令，用于解析主机的默认域名，只允许配置一条。
    如果你没有提供默认域，系统会通过 ``/etc/resolv.conf`` 来判断域。

.. _splitdns-config-format-search-list:

``search_list``
    A list of domains separated by spaces or semicolons (;). This
    specifies the domain search order. If you do not provide the search
    list, the system determines the value from :manpage:`resolv.conf(5)`

    通过空格或者分号分割的域名。指定了域搜索的顺序，如果你没有提供列表，
    系统通过 :manpage:`resolv.conf(5)` 来判断。

Examples
========

Consider the following DNS server selection specifications: ::

      dest_domain=internal.company.com named=255.255.255.255:212 255.255.255.254 def_domain=company.com search_list=company.com company1.com
      dest_domain=!internal.company.com named=255.255.255.253

使用如下的DNS选择规则： ::

      dest_domain=internal.company.com named=255.255.255.255:212 255.255.255.254 def_domain=company.com search_list=company.com company1.com
      dest_domain=!internal.company.com named=255.255.255.253

Now consider the following two requests: ::

     http://minstar.internal.company.com

当有如下两个请求进入时： ::

     http://minstar.internal.company.com

This request matches the first line and therefore selects DNS server
``255.255.255.255`` on port ``212``. All resolver requests use
``company.com`` as the default domain, and ``company.com`` and
``company1.com`` as the set of domains to search first. ::

     http://www.microsoft.com

这个请求匹配到第一行配置，所以DNS服务器 ``255.255.255.255`` 端口号  ``212`` 会被使用。
所有的解析请求都使用 ``company.com`` 作为默认的域， ``company.com`` 和
``company1.com`` 作为搜索的域。 ::

     http://www.microsoft.com

This request matches the second line. Therefore, Traffic Server selects
DNS server ``255.255.255.253``. Because no ``def_domain`` or
``search_list`` was supplied, Traffic Server retrieves this information
from :manpage:`resolv.conf(5)`

这个请求匹配第二行配置。因此Traffic Server使用DNS服务器 ``255.255.255.253`` 。因
为没有定义 ``def_domain`` 或者 ``search_list`` 。Traffic Server从  :manpage:`resolv.conf(5)`
获取信息。
