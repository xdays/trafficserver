# Makefile.am for the traffic/iocore/aio hierarchy
#
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

AM_CPPFLAGS = \
  -I$(top_srcdir)/iocore/eventsystem \
  -I$(top_srcdir)/lib \
  -I$(top_srcdir)/lib/records \
  -I$(top_srcdir)/lib/ts

DEFS += @IOCORE_MODULARIZED_DEFS@
TESTS = test_AIO.sample

noinst_LIBRARIES = libinkaio.a
check_PROGRAMS = test_AIO

libinkaio_a_SOURCES = AIO.cc I_AIO.h P_AIO.h Inline.cc
test_AIO_SOURCES = \
  test_AIO.cc

test_AIO_CXXFLAGS = \
  $(iocore_include_dirs) \
  -I$(top_builddir)/proxy \
  -I$(top_builddir)/proxy/api/ts \
  -I$(top_srcdir)/proxy/api \
  -I$(top_srcdir)/proxy \
  -I$(top_srcdir)/proxy/hdrs \
  -I$(top_srcdir)/proxy/http \
  -I$(top_srcdir)/proxy/logging \
  -I$(top_srcdir)/mgmt \
  -I$(top_srcdir)/mgmt/utils

test_AIO_LDADD = \
  libinkaio.a \
  $(top_builddir)/lib/records/librecprocess.a \
  $(top_builddir)/mgmt/libmgmt_p.a \
  $(top_builddir)/mgmt/utils/libutils_p.a \
  $(top_builddir)/iocore/eventsystem/libinkevent.a \
  $(top_builddir)/lib/ts/libtsutil.la \
  $(top_builddir)/proxy/shared/libUglyLogStubs.a \
  @LIBTCL@

