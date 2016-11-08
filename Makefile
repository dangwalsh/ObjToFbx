
SHELL       = /bin/sh

# default config:
#    release
#    x86
#    shared
#    clang
#    
#    to build 64 bit:                make -e M64=-m64
#    to build static:                make -e STATIC_LINK=1
#    to build 64 bit static debug:   make -e M64=-m64 STATIC_LINK=1 VARIANT=debug
#    to build using gcc:             make -e GCC_COMPILER=1
#

DS           = dsymutil
CC           = cc -std=c++11
LD           = cc 
STDC         = c++
COMPILER     = clang
ifneq "$(GCC_COMPILER)" ""
    COMPILER = gcc4
    CC       = gcc
    LD       = gcc
    STDC     = stdc++
endif

VARIANT = release
ifeq "$(VARIANT)" "debug"
    GCC_DEBUG_FLAGS += -g -D_DEBUG
endif 

M64 =
ARCH = x86
ifeq "$(M64)" "-m64"
    ARCH=x64
endif

PROJECT     = ObjToFbx
BINDIR      = ~/bin/$(COMPILER)/$(ARCH)/$(VARIANT)/$(PROJECT)
OBJDIR      = ~/obj/$(COMPILER)/$(ARCH)/$(VARIANT)/$(PROJECT)
LIBDIR      = /usr/local/lib
LIBDIR_FBX  = /Applications/Autodesk/FBX\ SDK/2015.1/lib/$(COMPILER)/$(VARIANT)
INCDIR      = /usr/local/include
INCDIR_FBX  = /Applications/Autodesk/FBX\ SDK/2015.1/include
PROJDIR	    = ./$(PROJECT)
EXCEPTDIR   = $(PROJDIR)/Exceptions
GEOMDIR	    = $(PROJDIR)/Geometry
IODIR	    = $(PROJDIR)/Io
UTILDIR     = $(PROJDIR)/Utilities

TARGET      = $(BINDIR)/$(PROJECT)
OBJS        = $(PROJDIR)/main.o \
                $(IODIR)/ObjReader.o \
                $(IODIR)/MtlReader.o \
                $(IODIR)/ObjReaderFacade.o \
                $(GEOMDIR)/ObjTex.o \
                $(GEOMDIR)/ObjFace.o \
                $(GEOMDIR)/ObjGroup.o \
                $(GEOMDIR)/ObjScene.o \
                $(GEOMDIR)/ObjMaterial.o \
                $(UTILDIR)/SdkTools.o \
                $(UTILDIR)/StringTools.o \
                $(UTILDIR)/GeometryTools.o \
                $(UTILDIR)/ClTools.o \
                $(EXCEPTDIR)/SdkException.o \
                $(EXCEPTDIR)/VectorException.o

CP          = cp -f
RM          = /bin/rm -rf

CXXFLAGS    = -pipe $(M64) $(GCC_DEBUG_FLAGS) 
LDFLAGS     = $(M64)
DBFLAGS     = -o

STATIC_LINK  =
FBXSDK_LIB   = -lfbxsdk
BOOST_LIB    = -lboost_filesystem -lboost_system
ifeq "$(STATIC_LINK)" ""
    CXXFLAGS += -DFBXSDK_SHARED
    COPY_LIB = $(CP) \
                $(LIBDIR_FBX)/libfbxsdk.dylib \
                $(LIBDIR)/libboost_filesystem.dylib \
                $(LIBDIR)/libboost_system.dylib \
                $(BINDIR)
else
    FBXSDK_LIB = $(LIBDIR_FBX)/libfbxsdk.a
    BOOST_LIB  = $(LIBDIR)/libboost_filesystem.a \
                 $(LIBDIR)/libboost_system.a
endif

GEN_SYM     = $(DS) $(TARGET) $(DBFLAGS) $(TARGET).dSYM
LIBS        = $(FBXSDK_LIB) $(BOOST_LIB) -lm -l$(STDC) -liconv -fexceptions -lz -framework Carbon -framework SystemConfiguration 

.SUFFIXES: .cxx

all: $(TARGET)

$(TARGET): $(OBJS)
	@if [ ! -d $(@D) ]; then mkdir -p $(@D) ; fi
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR) ; fi
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -L$(LIBDIR) $(LIBS) -L$(LIBDIR_FBX)
	$(GEN_SYM)
	mv $(PROJDIR)/*.o $(OBJDIR)
	mv $(IODIR)/*.o $(OBJDIR)
	mv $(GEOMDIR)/*.o $(OBJDIR)
	mv $(UTILDIR)/*.o $(OBJDIR)
	mv $(EXCEPTDIR)/*.o $(OBJDIR)
	$(COPY_LIB)

.cxx.o:
	$(CC) $(CXXFLAGS) -I$(INCDIR) -I$(INCDIR_FBX) -c $< -o $*.o

clean:
	$(RM) $(OBJDIR)
	$(RM) $(BINDIR)
