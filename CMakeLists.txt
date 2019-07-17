# minimum version
cmake_minimum_required (VERSION 2.8)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

# project name
project (Catherine)

# #configure file
# configure_file (
# 	"${PROJECT_SOURCE_DIR}/config.h.in"
# 	"${PROJECT_BINARY_DIR}/config.h"
# 	)

# # defines
# option (USE_MYFUNCTION "Use provided function" ON)

# if (USE_MYFUNCTION)
# 	include_directories("${PROJECT_SOURCE_DIR}/function")
# 	add_subdirectory(function)
# 	set(EXTRA_LIBS ${EXTRA_LIBS} functionlib)
# endif (USE_MYFUNCTION)

# header file directories
include_directories(
	"${PROJECT_SOURCE_DIR}/Src/glad/include"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/assimp/include"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/glm"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/glfw-3.3.bin.WIN64/include"
)

# lib file directories
link_directories(
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/glfw-3.3.bin.WIN64/lib-vc2017"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/assimp/lib"
)

# source path
aux_source_directory(./Src SRC_DIR)
aux_source_directory(./Src/glad/src GLAD_SRC_DIR)

# executable file
add_executable(Catherine ${SRC_DIR} ${GLAD_SRC_DIR})

# lib
target_link_libraries(Catherine glfw3.lib assimp-vc140-mt.lib)
