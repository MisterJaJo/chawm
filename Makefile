# chawm - The cha(d) window manager
# chawm - Pronunced: cha-d ouble-u m
# See LICENSE file for copyright and license details.

include config.mk

SRC      = $(wildcard ${SRC_DIR}/*.c)
OBJ      = $(patsubst src/%.c, build/%.o, $(SRC))
DEPS     = $(addprefix -I, $(SRC_DIR))

vpath %.c $(SRC_DIR)

define make-goal
$1/%.o: %.c
	${CC} ${DEPS} -c $$< -o $$@
endef

all: options checkdirs build/chawm

options:
	@echo chawm build options:
	@echo "Sources  = ${SRC}"
	@echo "Object   = ${OBJ}"
	@echo "Deps     = ${DEPS}"
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

build/chawm: ${OBJ}
	${CC} $^ -o $@

checkdirs: ${BUILD_DIR}

${BUILD_DIR}:
	mkdir -p $@

clean:
	rm -rf ${BUILD_DIR}

$(foreach bdir, $(BUILD_DIR), $(eval $(call make-goal, $(bdir))))

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f build/chawm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/chawm
	cp chawm.desktop /usr/share/xsessions/

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
	      /usr/share/xsessions/chawm.desktop

.PHONY: all checkdirs clean install uninstall
