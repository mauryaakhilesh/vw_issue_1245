AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}


CFLAGS		= -g -Wall -O2 -std=gnu99 -Wno-unused-variable -Wno-sign-compare
CXXFLAGS	= -g -Wall -O2 -std=c++11 -std=c++0x -fno-strict-aliasing -Wno-unused-variable -Wno-sign-compare

BASE_DIR 	= .
TEST_DIR    = test
SRC_DIR 	= src
LIB_DIR 	= lib
INCLUDE_DIR = include 
OBJDIR 		= build

CC=gcc
CXX=g++

PREDICT_DEFAULT_INCLUDES = -I$(INCLUDE_DIR) -I/usr/include/glib-2.0 -DOPTIMIZE_RESPONSE_FOR_SIZE=1

if CENTOS64
PREDICT_INCLUDES = $(PREDICT_DEFAULT_INCLUDES) -I /usr/lib64/glib-2.0/include
endif

if CENTOS
PREDICT_INCLUDES = $(PREDICT_DEFAULT_INCLUDES) -I /usr/lib/glib-2.0/include
endif

if DEBIAN64
PREDICT_INCLUDES = $(PREDICT_DEFAULT_INCLUDES) -I /usr/lib/x86_64-linux-gnu/glib-2.0/include 
endif

if DEBIAN
PREDICT_INCLUDES = $(PREDICT_DEFAULT_INCLUDES) -I /usr/lib/i386-linux-gnu/glib-2.0/include
endif


PREDICT_SRC_FILES = $(SRC_DIR)/vw_predict_model.cpp

TEST_INCLUDE_DIR = $(TEST_DIR)/include
TEST_SRC_DIR = $(TEST_DIR)/src

TEST_SRC_FILES = $(TEST_SRC_DIR)/predictTest.cpp

test: predictTest
	./predictTest

bin_PROGRAMS = predictTest
# predict

all-local: $(bin_PROGRAMS)
	rm -rf *.o

## processor test
predictTest_SOURCES	= $(TEST_SRC_FILES) $(PREDICT_SRC_FILES)
#predictTest_LDADD	= $(LIB_DIR)/pcache/libpcache.a -lm -lssl -lglib-2.0 -lstdc++ -lz -lrt -lpthread $(LIB_DIR)/vw/libvw.a $(LIB_DIR)/vw/liballreduce.a -lboost_program_options -lz -lpthread 

predictTest_LDADD      = -lglib-2.0 -lstdc++ -lz -lrt -lpthread $(LIB_DIR)/vw/libvw.a $(LIB_DIR)/vw/liballreduce.a -lboost_program_options  -lpthread
predictTest_CXXFLAGS =  -I$(TEST_INCLUDE_DIR) $(PREDICT_INCLUDES) -D_GTEST
predictTest_CFLAGS	= $(PREDICT_INCLUDES) --std=gnu99 -D_GTEST
predictTest_LDFLAGS	= -Wall 

