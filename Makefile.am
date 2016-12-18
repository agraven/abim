abimdatadir = $(datadir)/@PACKAGE@

#AM_CXXFLAGS = 
SUBDIRS = soil .

bin_PROGRAMS = bin/abim
bin_abim_CXXFLAGS = -Og -std=c++11 -DDATADIR="$(pkgdatadir)" -std=c++11 -I$(top_srcdir)/include -I$(top_srcdir)/soil/src
bin_abim_LDADD = soil/lib/libsoil.a
bin_abim_SOURCES = main.cpp \
	src/core.cpp \
	src/world.cpp \
	src/object.cpp \
	src/shader/fragment-shader.cpp \
	src/shader/vertex-shader.cpp
