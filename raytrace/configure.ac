#
# Copyright (c) 2005-2013 Michael Shafae
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met: 
# 
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
# IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
# PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#
# $Id: configure.ac 4386 2013-09-06 01:23:38Z mshafae $
#
#

AC_INIT([CSUF CPSC 566 Raytracer], [0.1], [mshafae@fullerton.edu])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
dnl AC_CONFIG_MACRO_DIR([m4])
AM_PROG_AR
AC_PROG_CXX
AC_PROG_CXX
dnl LT_INIT
AC_CONFIG_HEADERS([config.h])
AC_CHECK_PROG(PDFLATEX, pdflatex, pdflatex)

if test -z "$PDFLATEX"; then
  AC_MSG_WARN([Missing pdflatex; unable to generate PDF of the raytracer's input grammar.])
fi
AM_CONDITIONAL([HAVE_PDFLATEX], test -n "$PDFLATEX")

AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])
AC_OUTPUT

