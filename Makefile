#############################################################################
# Makefile for building: ControlPanel3D
# Generated by qmake (2.01a) (Qt 4.8.6) on: Fri Apr 20 17:59:19 2018
# Project:  ControlPanel3D.pro
# Template: app
# Command: /usr/local/qt4.8.2-armhf/bin/qmake -spec /usr/local/qt4.8.2-armhf/mkspecs/linux-arm-gnueabihf-g++ -o Makefile ControlPanel3D.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-linux-gnueabihf-gcc
CXX           = arm-linux-gnueabihf-g++
DEFINES       = -DQT_DEPRECATED_WARNINGS -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/local/qt4.8.2-armhf/mkspecs/linux-arm-gnueabihf-g++ -I. -I/usr/local/qt4.8.2-armhf/include/QtCore -I/usr/local/qt4.8.2-armhf/include/QtGui -I/usr/local/qt4.8.2-armhf/include -I. -I. -I/opt/tslib/include
LINK          = arm-linux-gnueabihf-g++
LFLAGS        = -Wl,-rpath-link=/opt/tslib/lib -Wl,-rpath,/usr/local/qt4.8.2-armhf/lib
LIBS          = $(SUBLIBS)  -L/opt/tslib/lib -L/usr/local/qt4.8.2-armhf/lib -lQtGui -L/usr/local/qt4.8.2-armhf/lib -L/opt/tslib/lib -lQtNetwork -lQtCore -lpthread 
AR            = arm-linux-gnueabihf-ar cqs
RANLIB        = 
QMAKE         = /usr/local/qt4.8.2-armhf/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-linux-gnueabihf-strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		lcddisplay.cpp \
		managefile.cpp moc_lcddisplay.cpp
OBJECTS       = main.o \
		lcddisplay.o \
		managefile.o \
		moc_lcddisplay.o
DIST          = /usr/local/qt4.8.2-armhf/mkspecs/common/unix.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/linux.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/gcc-base.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/gcc-base-unix.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/g++-base.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/g++-unix.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/qconfig.pri \
		/usr/local/qt4.8.2-armhf/mkspecs/features/qt_functions.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/qt_config.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/exclusive_builds.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/default_pre.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/debug.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/default_post.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/shared.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/warn_on.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/qt.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/unix/thread.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/moc.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/resources.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/uic.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/yacc.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/lex.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/include_source_dir.prf \
		ControlPanel3D.pro
QMAKE_TARGET  = ControlPanel3D
DESTDIR       = 
TARGET        = ControlPanel3D

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_lcddisplay.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9][^0-9]*\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && arm-linux-gnueabihf-objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: ControlPanel3D.pro  /usr/local/qt4.8.2-armhf/mkspecs/linux-arm-gnueabihf-g++/qmake.conf /usr/local/qt4.8.2-armhf/mkspecs/common/unix.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/linux.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/gcc-base.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/gcc-base-unix.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/g++-base.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/common/g++-unix.conf \
		/usr/local/qt4.8.2-armhf/mkspecs/qconfig.pri \
		/usr/local/qt4.8.2-armhf/mkspecs/features/qt_functions.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/qt_config.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/exclusive_builds.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/default_pre.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/debug.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/default_post.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/shared.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/warn_on.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/qt.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/unix/thread.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/moc.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/resources.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/uic.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/yacc.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/lex.prf \
		/usr/local/qt4.8.2-armhf/mkspecs/features/include_source_dir.prf \
		/usr/local/qt4.8.2-armhf/lib/libQtGui.prl \
		/usr/local/qt4.8.2-armhf/lib/libQtNetwork.prl \
		/usr/local/qt4.8.2-armhf/lib/libQtCore.prl
	$(QMAKE) -spec /usr/local/qt4.8.2-armhf/mkspecs/linux-arm-gnueabihf-g++ -o Makefile ControlPanel3D.pro
/usr/local/qt4.8.2-armhf/mkspecs/common/unix.conf:
/usr/local/qt4.8.2-armhf/mkspecs/common/linux.conf:
/usr/local/qt4.8.2-armhf/mkspecs/common/gcc-base.conf:
/usr/local/qt4.8.2-armhf/mkspecs/common/gcc-base-unix.conf:
/usr/local/qt4.8.2-armhf/mkspecs/common/g++-base.conf:
/usr/local/qt4.8.2-armhf/mkspecs/common/g++-unix.conf:
/usr/local/qt4.8.2-armhf/mkspecs/qconfig.pri:
/usr/local/qt4.8.2-armhf/mkspecs/features/qt_functions.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/qt_config.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/exclusive_builds.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/default_pre.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/debug.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/default_post.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/shared.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/warn_on.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/qt.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/unix/thread.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/moc.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/resources.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/uic.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/yacc.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/lex.prf:
/usr/local/qt4.8.2-armhf/mkspecs/features/include_source_dir.prf:
/usr/local/qt4.8.2-armhf/lib/libQtGui.prl:
/usr/local/qt4.8.2-armhf/lib/libQtNetwork.prl:
/usr/local/qt4.8.2-armhf/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/qt4.8.2-armhf/mkspecs/linux-arm-gnueabihf-g++ -o Makefile ControlPanel3D.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/ControlPanel3D1.0.0 || $(MKDIR) .tmp/ControlPanel3D1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/ControlPanel3D1.0.0/ && $(COPY_FILE) --parents lcddisplay.h managefile.h .tmp/ControlPanel3D1.0.0/ && $(COPY_FILE) --parents main.cpp lcddisplay.cpp managefile.cpp .tmp/ControlPanel3D1.0.0/ && $(COPY_FILE) --parents lcddisplay.ui .tmp/ControlPanel3D1.0.0/ && (cd `dirname .tmp/ControlPanel3D1.0.0` && $(TAR) ControlPanel3D1.0.0.tar ControlPanel3D1.0.0 && $(COMPRESS) ControlPanel3D1.0.0.tar) && $(MOVE) `dirname .tmp/ControlPanel3D1.0.0`/ControlPanel3D1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/ControlPanel3D1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_lcddisplay.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_lcddisplay.cpp
moc_lcddisplay.cpp: lcddisplay.h
	/usr/local/qt4.8.2-armhf/bin/moc $(DEFINES) $(INCPATH) lcddisplay.h -o moc_lcddisplay.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_lcddisplay.h
compiler_uic_clean:
	-$(DEL_FILE) ui_lcddisplay.h
ui_lcddisplay.h: lcddisplay.ui
	/usr/local/qt4.8.2-armhf/bin/uic lcddisplay.ui -o ui_lcddisplay.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp lcddisplay.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

lcddisplay.o: lcddisplay.cpp lcddisplay.h \
		ui_lcddisplay.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lcddisplay.o lcddisplay.cpp

managefile.o: managefile.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o managefile.o managefile.cpp

moc_lcddisplay.o: moc_lcddisplay.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_lcddisplay.o moc_lcddisplay.cpp

####### Install

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/home/debian/qtApp/ || $(MKDIR) $(INSTALL_ROOT)/home/debian/qtApp/ 
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/home/debian/qtApp/$(QMAKE_TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/home/debian/qtApp/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/home/debian/qtApp/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

