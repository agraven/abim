AC_PREREQ([2.69])
AC_INIT([ABIM Engine Prototype], [0.0.1], [amandapg@protonmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([main.cpp])
AC_CONFIG_HEADERS([include/config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror -Wno-portability])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([GL], [glClear])
AC_CHECK_LIB([GLEW], [glewInit])
AC_CHECK_LIB([glfw], [glfwGetVersionString])

# Checks for header files.
AC_CHECK_HEADERS([memory.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([sqrt])
AC_CHECK_FUNCS([strstr])
AC_CHECK_FUNCS([strtol])

AC_CONFIG_FILES([Makefile
                 soil/Makefile])

AC_OUTPUT
