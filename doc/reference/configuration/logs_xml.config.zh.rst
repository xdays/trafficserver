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
logs_xml.config（中文）
===============

.. configfile:: logs_xml.config

The :file:`logs_xml.config` file defines the custom log file formats,
filters, and processing options. The format of this file is modeled
after XML, the Extensible Markup Language.

 :file:`logs_xml.config` 文件定义日志格式，过滤器和处理选项。文件格式为
XML，可扩展标记语言。

Format
======

The :file:`logs_xml.config` file contains the specifications below:

-  ``LogFormat`` specifies the fields to be gathered from each protocol
   event access.
-  ``LogFilter`` specifies the filters that are used to include or
   exclude certain entries being logged based on the value of a field
   within that entry.
-  ``LogObject`` specifies an object that contains a particular format,
   a local filename, filters, and collation servers.

  :file:`logs_xml.config` 文件包含如下规范:

-  ``LogFormat`` 指定从每种协议收集的字段
-  ``LogFilter`` 指定基于包含或者排除日志条目的字段的过滤器
-  ``LogObject`` 指定包含特定格式，文件名，过滤器和配合服务器的对象

The :file:`logs_xml.config` file ignores extra white space, blank lines, and
all comments.

 :file:`logs_xml.config` 文件中的空格，空行和注视行会被忽略。
.. _LogFormat:

LogFormat
=========

The following list shows ``LogFormat`` specifications.

 ``LogFormat`` 规范如下。

.. _LogFormat-name:

``<Name = "valid_format_name"/>``
    Required
    Valid format names include any name except ``squid``, ``common``,
    ``extended``, or ``extended2``, which are pre-defined formats. There
    is no default for this tag.

    必须的
    格式名是预先定义好的日志格式，此标签没有默认值，其不能
    是 ``squid``, ``common``, ``extend`` 或者 ``extend2`` 。
       

.. _LogFormat-Format:

``<Format = "valid_format_specification"/>``
    Required
    A valid format specification is a printf-style string describing
    each log entry when formatted for ASCII output. Use ``%<``
    ``field`` ``>`` as a placeholder for valid field names. For more
    information, refer to :ref:`custom-logging-fields`.

    必须
    合法的日志规范应该是printf样式的字符串，它们用来格式化ASCII日志记录。 
      ``%<`` ``field`` ``>`` 是字段名称的包含符。更多信息请参考 :ref:
    `custom-logging-fields`.

    The specified field can be one of the following types:

    Simple. For example: ``%<cqu>``
    A field within a container, such as an HTTP header or a statistic.
    Fields of this type have the syntax: ::

         %<{ field } container>

    Aggregates, such as ``COUNT``, ``SUM``, ``AVG``, ``FIRST``,
    ``LAST``. Fields of this type have the syntax: ``%<operator (``
    ``field`` ``)>``

    字段可以是如下类型:

    简单的。例如： ``%<cqu>`` 
    一个容器里包含一个像HTTP报头或者统计信息的字段。这类字段有如下语法： ::

         %<{ field } container>

    聚合的，像 ``COUNT``, ``SUM``, ``AVG``, ``FIRST``,
    ``LAST``. 这类字段语法是: ::

    ``%<operator (`` ``field`` ``)>``

.. note::

    You cannot create a format specification that contains both aggregate operators and regular fields.

    你不能创建既包含一般字段又包含聚合操作符的日志格式规范。

``<Interval = "aggregate_interval_secs"/>``
    Optional
    Use this tag when the format contains aggregate operators. The value
    "``aggregate_interval_secs``\" represents the number of seconds
    between individual aggregate values being produced.

    The valid set of aggregate operators are:

    -  COUNT
    -  SUM
    -  AVG
    -  FIRST
    -  LAST

    可选的
    当日志格式中有聚合操作符时使用这个标签。"``aggregate_interval_secs``\" 
    表示进行聚合运算的时间间隔。

    合法的聚合操作符包括：

    -  COUNT
    -  SUM
    -  AVG
    -  FIRST
    -  LAST

.. _LogFilters:

LogFilters
==========

The following list shows the ``LogFilter`` specifications.

``<Name = "valid_filter_name"/>``
    Required
    All filters must be uniquely named.

    必须的
    所有的过滤器必须命名唯一

``<Condition = "valid_log_field valid_operator valid_comparison_value"/>``
    Required
    This field contains the following elements:

    必须的
    这个字段包含如下元素：

    ``valid_log_field`` - the field that will be compared against
    the given value. For more information, refer to :ref:`logging-format-cross-reference`.

    ``valid_log_field`` - 用于和给定值比较的字段。更多信息参考 :ref:`logging-format-cross-reference`.

    ``valid_operator_field`` - any one of the following: ``MATCH``,
    ``CASE_INSENSITIVE_MATCH``, ``CONTAIN``,
    ``CASE_INSENSITIVE_CONTAIN``.

    ``valid_operator_field`` - 如下的任意一个值 ``MATCH``,
    ``CASE_INSENSITIVE_MATCH``, ``CONTAIN``,
    ``CASE_INSENSITIVE_CONTAIN``.

    -  ``MATCH`` is true if the field and value are identical
       (case-sensitive).
    -  ``CASE_INSENSITIVE_MATCH`` is similar to ``MATCH``, except that
       it is case-insensitive.
    -  ``CONTAIN`` is true if the field contains the value (the value is
       a substring of the field).
    -  ``CASE_INSENSITIVE_CONTAIN`` is a case-insensitive version of
       ``CONTAIN``.

    -  ``MATCH`` 字段和值完全匹配
    -  ``CASE_INSENSITIVE_MATCH`` 和 ``MATCH`` 一样，除了大小写不敏感
    -  ``CONTAIN`` 字段里包含对应的值
    -  ``CASE_INSENSITIVE_CONTAIN`` 和 ``CONTAIN`` 一样，除了大小写不敏感

    ``valid_comparison_value`` - any string or integer matching the
    field type. For integer values, all of the operators are equivalent
    and mean that the field must be equal to the specified value.

    ``valid_comparison_value`` - 与字段类型匹配的数字或者字符串。对于数字
    所有的操作符都表示要与给定值相等。

.. note::

    There are no negative comparison operators. If you want to
    specify a negative condition, then use the ``Action`` field to
    ``REJECT`` the record.

    没有反向匹配操作符，如果你像配置取反的条件，请把 ``Action`` 字段
    配置成 ``REJECT``

``<Action = "valid_action_field"/>``
    Required: ``ACCEPT`` or ``REJECT`` .
    This instructs Traffic Server to either accept or reject records
    that satisfy the filter condition.

    必须的： ``ACCEPT`` or ``REJECT`` 。
    此标签配置Traffic Server拒绝还是允许匹配过滤条件的记录。

.. _LogObject:

LogObject
=========

The following list shows the ``LogObject`` specifications.

 ``LogObject`` 的规范如下列表。

``<Format = "valid_format_name"/>``
    Required
    Valid format names include the predefined logging formats:
    ``squid``, ``common``, ``extended``, and ``extended2``, as well as
    any previously-defined custom log formats. There is no default for
    this tag.

    必须的
    合法的名称包括预先定义好的： ``squid``, ``common``, ``extended``, and
    ``extended2`` ，还有一些自定义的日志格式，此标签没有默认值

``<Filename = "file_name"/>``
    Required
    The filename to which the given log file is written on the local
    file system or on a remote collation server. No local log file will
    be created if you fail to specify this tag. All filenames are
    relative to the default logging directory.

    必须的
    保存日志文件的本地文件系统文件名或者远程的服务器。如果你不配置这个标签
    就不会生成本地文件，所有的文件名都相对于默认的日志路径。

    If the name does not contain an extension (for example, ``squid``),
    then the extension ``.log`` is automatically appended to it for
    ASCII logs and ``.blog`` for binary logs (refer to :ref:`Mode =
    "valid_logging_mode" <LogObject-Mode>`_).

    如果文件名没有扩展名（比如， ``squid`` ），那么ASCII日志会自动追加
``.log`` ，二进制日志会自动追加 ``.blog`` (参考 :ref:`Mode =
    "valid_logging_mode" <LogObject-Mode>`_).

    If you do not want an extension to be added, then end the filename
    with a single (.) dot (for example: ``squid.`` ).

    如果你不想追加扩展名那么在文件名最后加个点（例如： ``squid.`` ）

.. _LogObject-Mode:

``<Mode = "valid_logging_mode"/>``
    Optional
    Valid logging modes include ``ascii`` , ``binary`` , and
    ``ascii_pipe`` . The default is ``ascii`` .

    -  Use ``ascii`` to create event log files in human-readable form
       (plain ASCII).
    -  Use ``binary`` to create event log files in binary format. Binary
       log files generate lower system overhead and occupy less space on
       the disk (depending on the information being logged). You must
       use the :program:`traffic_logcat` utility to translate binary log files to ASCII
       format before you can read them.
    -  Use ``ascii_pipe`` to write log entries to a UNIX named pipe (a
       buffer in memory). Other processes can then read the data using
       standard I/O functions. The advantage of using this option is
       that Traffic Server does not have to write to disk, which frees
       disk space and bandwidth for other tasks. In addition, writing to
       a pipe does not stop when logging space is exhausted because the
       pipe does not use disk space.

    可选的
    合法的日志模式包括 ``ascii``, ``bonary`` ，和 ``ascii_pipe`` ，默认是
    ``ascii`` 。

    - ``ascii`` 格式创建易于阅读的日志
    - ``bonary`` 格式创建二进制日志，写二进制日志的开销小而且占用较小的空间
    （视要写入的信息而定）。阅读之前必须使用 :program: `traffic_logcat`
    工具来将二进制日志转为ASCII格式。
    - ``ascii_pipe`` 格式用于将日志写到UNIX的命名管道（一种内存缓存）。过后
    其他程序使用标准的IO函数读取数据。这种格式的优势是Traffic Server不需要
    写磁盘，这样就能给其他任务节省空间和带宽。此外写管道不会在日志空间耗尽时
    停止，因为管道不占用磁盘空间。

    If you are using a collation server, then the log is written to a
    pipe on the collation server. A local pipe is created even before a
    transaction is processed, so you can see the pipe right after
    Traffic Server starts. Pipes on a collation server, however, *are*
    created when Traffic Server starts.

    如果你使用配合服务器，日志会写入配合服务器的管道里。Traffic Server会首先在
    第一个事务前创建本地管道，因此在Traffic Server启动后就能看到管道，
    但是在配合服务器上，管道 *都是* 在Traffic Server启动时创建的。

``<Filters = "list_of_valid_filter_names"/>``
    Optional
    A comma-separated list of names of any previously-defined log
    filters. If more than one filter is specified, then all filters must
    accept a record for the record to be logged.

    可选的
    逗号分隔的预先定义好的过滤器，如果配置多个过滤器，那么每条记录必须经过
    所有过滤器处理后才能保存

``<Protocols = "list_of_valid_protocols"/>``
    Optional
    A comma-separated list of the protocols this object should log.
    Valid protocol names for this release are ``HTTP`` (FTP is
    deprecated).

    可选的
    逗号分割的协议，只有该协议的类型才能记录。在这个版本中合法的名称是 ``HTTP``
    （FTP已废弃）

``<ServerHosts = "list_of_valid_servers"/>``
    Optional
    A comma-separated list of valid hostnames.This tag indicates that
    only entries from the named servers will be included in the file.

    可选的
    逗号分割的合法主机名。这个标签指定只有输入对应服务器的记录才会写入日志。

.. _logs-xml-logobject-collationhost:

``<CollationHosts = "list_of_valid_hostnames"/>``
    Optional
    A comma-separated list of collation servers to which all log entries
    (for this object) are forwarded. Collation servers can be specified
    by name or IP address. Specify the collation port with a colon after
    the name; for example, ``host:port`` .

    可选的
    逗号分割的服务器列表，所有该对象下的日志都会转发给对应的服务器。配合服务器
    可以通过域名或者IP制定。端口号和主机名以分号分割；比如 ``host:port`` 。

``<Header = "header"/>``
    Optional
    The header text you want the log files to contain. The header text
    appears at the beginning of the log file, just before the first
    record.

    可选的
    在日志文件中包含的header头信息。该信息保存在日志的第一个记录的前面。

``<RollingEnabled = "truth value"/>``
    Optional
    Enables or disables log file rolling for the ``LogObject``. This
    setting overrides the value for the
    :ts:cv:`proxy.config.log.rolling_enabled` variable in the
    :file:`records.config` file. Set *truth value* to one of the
    following values:

    -  ``0`` to disable rolling for this particular ``LogObject``.
    -  ``1`` to roll log files at specific intervals during the day (you
       specify time intervals with the ``RollingIntervalSec`` and
       ``RollingOffsetHr`` fields).
    -  ``2`` to roll log files when they reach a certain size (you
       specify the size with the ``RollingSizeMb`` field).
    -  ``3`` to roll log files at specific intervals during the day or
       when they reach a certain size (whichever occurs first).
    -  ``4`` to roll log files at specific intervals during the day when
       log files reach a specific size (at a specified time if the file
       is of the specified size).

    可选的
    控制 ``LogObject`` 的日志滚动开关。这里的配置会覆盖 :file:`records.config` 
    中的 :ts:cv:`proxy.config.log.rolling_enabled` 变量。可配置的值如下：

    - ``0`` 关闭特定  ``LogObject`` 的日志滚动
    - ``1`` 每天定间隔的滚动日志，间隔时间通过 ``RollingIntervalSec`` 和
      ``RollingOffsetHr`` 指定
    - ``2`` 当文件达到制定大小时滚动日志， 大小通过 ``RollingSizeMb`` 指定
    - ``3``  通过时间间隔和大小两个条件来滚动日志，只要有一个条件满足即可
    - ``4``  通过时间间隔和大小两个条件来滚动日志，只要指定时间达到指定大小

.. XXX this is confusing ^ really, why is it a "truth value" but then it's 5 different integer values that means varias strange things?

``<RollingIntervalSec = "seconds"/>``
    Optional
    The seconds between log file rolling for the ``LogObject``; enables
    you to specify different rolling intervals for different
    ``LogObjects``.

    This setting overrides the value for
    :ts:cv:`proxy.config.log.rolling_interval_sec` in the
    :file:`records.config` file.

    可选的
    日志对象 ``LogObject`` 滚动的时间间隔，可针对不同的对象配置不同的时间间隔

    此配置覆盖 :file:`records.config` 文件的 
     :ts:cv:`proxy.config.log.rolling_interval_sec` 变量

``<RollingOffsetHr = "hour"/>``
    Optional
    Specifies an hour (from 0 to 23) at which rolling is guaranteed to
    align. Rolling might start before then, but a rolled file will be
    produced only at that time. The impact of this setting is only
    noticeable if the rolling interval is larger than one hour. This
    setting overrides the configuration setting for
    :ts:cv:`proxy.config.log.rolling_offset_hr` in the :file:`records.config`
    file.

    可选的
    制定日志滚动的小时（从0到23）。滚动可能会在指定的时间之前发生，但是滚动文件
    只会在指定的时间产生。这个配置只会在滚动间隔大于一小时的时候引起注意。此配置
    会覆盖 :file:`records.config` 的
     :ts:cv:`proxy.config.log.rolling_offset_hr` 变量。

``<RollingSizeMb = "size_in_MB"/>``
    Optional
    The size at which log files are rolled.

    可选的
    日志文件滚动的大小

Examples
========

The following is an example of a ``LogFormat`` specification that
collects information using three common fields: ::

         <LogFormat>
             <Name="minimal"/>
             <Format = "%<chi> : %<cqu> : %<pssc>"/>
         </LogFormat>

如下是一个 ``LogFormat`` 规范的例子，使用三个字段收集信息： ::

         <LogFormat>
             <Name="minimal"/>
             <Format = "%<chi> : %<cqu> : %<pssc>"/>
         </LogFormat>

The following is an example of a ``LogFormat`` specification that
uses aggregate operators: ::

         <LogFormat>
             <Name = "summary"/>
             <Format = "%<LAST(cqts)> : %<COUNT(*)> : %<SUM(psql)>"/>
             <Interval = "10"/>
         </LogFormat>

如下是一个使用了聚合操作符的 ``LogFormat`` 规范的例子： ::

         <LogFormat>
             <Name = "summary"/>
             <Format = "%<LAST(cqts)> : %<COUNT(*)> : %<SUM(psql)>"/>
             <Interval = "10"/>
         </LogFormat>

The following is an example of a ``LogFilter`` that will cause only
``REFRESH_HIT`` entries to be logged: ::

         <LogFilter>
              <Name = "only_refresh_hits"/>
              <Action = "ACCEPT"/>
              <Condition = "%<pssc> MATCH REFRESH_HIT"/>
         </LogFilter>

如下是一个 ``LogFilter`` 的例子，用于只对 ``REFRESH_HIT`` 的请求写日志： ::

         <LogFilter>
              <Name = "only_refresh_hits"/>
              <Action = "ACCEPT"/>
              <Condition = "%<pssc> MATCH REFRESH_HIT"/>
         </LogFilter>

.. note::

    When specifying the field in the filter condition, you can
    omit the ``%<>``. This means that the filter below is equivalent to the
    example directly above: ::

         <LogFilter>
             <Name = "only_refresh_hits"/>
             <Action = "ACCEPT"/>
             <Condition = "pssc MATCH REFRESH_HIT"/>
         </LogFilter>

    在指定过滤器条件时，你可以忽略 ``%<>`` 。也就是说下边的写法与上边的一样: ::

         <LogFilter>
             <Name = "only_refresh_hits"/>
             <Action = "ACCEPT"/>
             <Condition = "pssc MATCH REFRESH_HIT"/>
         </LogFilter>


The following is an example of a ``LogObject`` specification that
creates a local log file for the minimal format defined earlier. The log
filename will be ``minimal.log`` because this is an ASCII log file (the
default).::

         <LogObject>
             <Format = "minimal"/>
             <Filename = "minimal"/>
         </LogObject>

如下是一个 ``LogObject`` 规范的例子，用于把上边的最小日志格式对应的日志
写入本地日志文件。日志文件名为 ``minimal.log`` ，
这是一个ASCII日志文件（默认）：  ::

         <LogObject>
             <Format = "minimal"/>
             <Filename = "minimal"/>
         </LogObject>


The following is an example of a ``LogObject`` specification that
includes only HTTP requests served by hosts in the domain
``company.com`` or by the specific server ``server.somewhere.com``. Log
entries are sent to port 4000 of the collation host ``logs.company.com``
and to port 5000 of the collation host ``209.131.52.129.`` ::

         <LogObject>
              <Format = "minimal"/>
              <Filename = "minimal"/>
              <ServerHosts = "company.com,server.somewhere.com"/>
              <Protocols = "http"/>
              <CollationHosts = "logs.company.com:4000,209.131.52.129:5000"/>
         </LogObject>

如下是一个 ``LogObject`` 的例子，用于仅把 ``company.com`` 域名和
 ``server.somewhere.com`` 这台服务器的HTTP请求写入日志。 日志条目会被发送
至 ``logs.company.com`` 这台机器的4000端口和 ``209.131.52.129.`` 这台机器的5000
端口： ::

         <LogObject>
              <Format = "minimal"/>
              <Filename = "minimal"/>
              <ServerHosts = "company.com,server.somewhere.com"/>
              <Protocols = "http"/>
              <CollationHosts = "logs.company.com:4000,209.131.52.129:5000"/>
         </LogObject>

.. _WELF:

WELF
====

Traffic Server supports WELF (WebTrends Enhanced Log Format) so you can
analyze Traffic Server log files with WebTrends reporting tools. A
predefined ``<LogFormat>`` that is compatible with WELF is provided in
the :file:`logs_xml.config` file (shown below). To create a WELF format log
file, create a ``<LogObject>`` that uses this predefined format. ::

         <LogFormat>
             <Name = "welf"/>
             <Format = "id=firewall time=\"%<cqtd> %<cqtt>\" fw=%<phn> pri=6
                proto=%<cqus> duration=%<ttmsf> sent=%<psql> rcvd=%<cqhl>
                src=%<chi> dst=%<shi> dstname=%<shn> user=%<caun> op=%<cqhm>
                arg=\"%<cqup>\" result=%<pssc> ref=\"%<{Referer}cqh>\"
                agent=\"%<{user-agent}cqh>\" cache=%<crc>"/>
         </LogFormat>

Traffic Server支持WELF，因此你可以通过WebTrends报告工具来分析日志，
 :file:`logs_xml.config`  文件里提供了一个预先定义的  ``<LogFormat>`` （如下）
想要创建WELF格式的日志文件，创建一个使用该预先定义的日志格式的  ``<LogObject>`` 
即可： ::

         <LogFormat>
             <Name = "welf"/>
             <Format = "id=firewall time=\"%<cqtd> %<cqtt>\" fw=%<phn> pri=6
                proto=%<cqus> duration=%<ttmsf> sent=%<psql> rcvd=%<cqhl>
                src=%<chi> dst=%<shi> dstname=%<shn> user=%<caun> op=%<cqhm>
                arg=\"%<cqup>\" result=%<pssc> ref=\"%<{Referer}cqh>\"
                agent=\"%<{user-agent}cqh>\" cache=%<crc>"/>
         </LogFormat>

