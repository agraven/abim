abimdatadir = $(datadir)/@PACKAGE@

AM_CXXFLAGS = -DDATADIR="$(pkgdatadir)" -std=c++11
SUBDIRS = soil .

bin_PROGRAMS = bin/abim
bin_abim_SOURCES = main.cpp \
	include/shader/fragment-shader.h \
	include/shader/vertex-shader.h \
	src/shader/fragment-shader.cpp \
	src/shader/vertex-shader.cpp
bim_abim_CPPFLAGS = -I$(top_srcdir)/include 
bin_abim_LDADD = soil/lib/libsoil.a
