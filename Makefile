CXX = g++
CXX_FLAGS = -I include 

BUILD_DIR = build

SRC_DIR = src

OBJS = ${BUILD_DIR}/Server.o

all: ${BUILD_DIR} ${BUILD_DIR}/main ${BUILD_DIR}/client_main

${BUILD_DIR}: 
	mkdir -p $@

${BUILD_DIR}/client_main: ${SRC_DIR}/client_main.cpp ${BUILD_DIR}/Client.o
	${CXX} ${CXX_FLAGS} $^ -o $@

${BUILD_DIR}/main: ${SRC_DIR}/main.cpp ${OBJS}
	${CXX} ${CXX_FLAGS} $^ -o $@

${BUILD_DIR}/Server.o: ${SRC_DIR}/Server.cpp
	${CXX} ${CXX_FLAGS} -c $^ -o $@

${BUILD_DIR}/Client.o: ${SRC_DIR}/Client.cpp
	${CXX} ${CXX_FLAGS} -c $^ -o $@