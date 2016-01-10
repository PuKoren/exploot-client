#PROJECT NAME
project(exploot-client)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wall -Wno-long-long -pedantic")
endif()

#EXTERNAL PACKAGES (IRRLICHT)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Irrlicht REQUIRED)
find_package(Bullet REQUIRED)
find_package(Protobuf REQUIRED)
find_package(ENet REQUIRED)
find_package(Freetype REQUIRED)
find_package(Threads REQUIRED)

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL )
    find_library(IOKIT_FRAMEWORK IOKit)
    set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_FRAMEWORK})
endif(APPLE)

#INCLUDES & SRC FILES
include_directories(
    ${Irrlicht_INCLUDE_DIRECTORY}
    ${BULLET_INCLUDE_DIRS}
    ${INET_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/submodules
)

file(GLOB SRCS src/*.cpp)
file(GLOB HDRS include/*.h)
file(GLOB SUBSRCS submodules/RealisticWaterSceneNode/*.cpp)
file(GLOB SUBHDRS submodules/RealisticWaterSceneNode/*.h)
file(GLOB PROTOHDRS submodules/exploot-protobuf/build/*.h)
file(GLOB PROTOSRCS submodules/exploot-protobuf/build/*.cc)

#LINKING AND EXECUTABLE
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${SUBSRCS} ${SUBHDRS} ${PROTOSRCS} ${PROTOHDRS})
target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIBRARIES} ${BULLET_LIBRARIES} ${ENET_LIBRARIES} ${PROTOBUF_LIBRARIES} ${FREETYPE_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXTRA_LIBS})
