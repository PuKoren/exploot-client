#PROJECT NAME
project(exploot-client)
cmake_minimum_required(VERSION 2.8)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

#EXTERNAL PACKAGES (IRRLICHT)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Irrlicht REQUIRED)
find_package(Bullet REQUIRED)
find_package(Protobuf REQUIRED)
find_package(ENet REQUIRED)
find_package(Freetype REQUIRED)
find_package(Threads REQUIRED)

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
target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIBRARIES} ${BULLET_LIBRARIES} ${ENET_LIBRARIES} ${PROTOBUF_LIBRARIES} ${FREETYPE_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
