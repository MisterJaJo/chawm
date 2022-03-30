# chawm version
VERSION = 0.1

# Customize below to fit your system

# some additional definitions
DEFINITIONS=

# paths
SRC_DIR    = src
BUILD_DIR  = build
PREFIX     = /usr/local
MAN_PREFIX = ${PREFIX}/share/man

XCB_INC = /usr/include/xcb

# Xinerama, comment if you don't want it
XINERAMA_LIBS  = -lXinerama
XINERAMA_FLAGS = -DXINERAMA

# freetype
FREETYPE_LIBS  = -lfontconfig -lXft
FREETYPE_INC   = /usr/include/freetype2

# includes and libs
INCS = -I${XCB_INC} -I${FREETYPE_INC}
LIBS = -lxcb ${XINERAMA_LIBS} ${FREETYPE_LIBS}

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\" ${XINERAMA_FLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} ${DEFINITIONS} ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# compiler and linker
CC = cc
