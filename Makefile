CXX = g++
CXX_FLAGS = -I include 

BUILD_DIR = build

SRC_DIR = src

OBJS = ${BUILD_DIR}/Server.o



all: ${BUILD_DIR} ${BUILD_DIR}/main

${BUILD_DIR}: 
	mkdir -p $@

${BUILD_DIR}/main: ${SRC_DIR}/main.cpp ${OBJS}
	${CXX} ${CXX_FLAGS} $^ -o $@

${BUILD_DIR}/Server.o: ${SRC_DIR}/Server.cpp
	${CXX} ${CXX_FLAGS} -c $^ -o $@