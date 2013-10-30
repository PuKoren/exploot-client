#PROJECT NAME
project(PukoWorld_Client)
cmake_minimum_required(VERSION 2.8)

#EXTERNAL PACKAGES (IRRLICHT)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Irrlicht REQUIRED)
find_package(Bullet REQUIRED)
find_package(Protobuf REQUIRED)
find_package(ENet REQUIRED)
find_package(Freetype REQUIRED)

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

#LINKING AND EXECUTABLE
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${SUBSRCS} ${SUBHDRS})
target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIBRARIES} ${BULLET_LIBRARIES} ${ENET_LIBRARIES} ${PROTOBUFF_LIBRARIES} ${FREETYPE_LIBRARIES})
