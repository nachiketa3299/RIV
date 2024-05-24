CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RIV, LANGUAGES CXX)
SET(PROJECT_DESCRIPTION "RIV - RZN Interactive Visualizer")
SET(CMAKE_CXX_STANDARD 23)

# 소스 파일 경로 및 파일
SET(riv_source_dir ${PROJECT_SOURCE_DIR}/src)
SET(riv_include_dir ${PROJECT_SOURCE_DIR}/include)

# NOTE 그냥 일단 다 가져오는 것으로 (너무 귀찮음)
FILE(GLOB_RECURSE riv_sources ${riv_source_dir}/*.cc)

# 추가된 소스 파일 로그
MESSAGE(STATUS "[RIV]: 추가될 소스 파일 목록: ")

FOREACH(riv_source ${riv_sources})
	MESSAGE(STATUS "\t${riv_source}")
ENDFOREACH()

# OpenGL 및 freeglut 라이브러리 추가
FIND_PACKAGE(OpenGL REQUIRED)
SET(FREEGLUT_BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)
ADD_SUBDIRECTORY(external/freeglut)

# 빌드 타겟 (1) -> riv_sim
ADD_EXECUTABLE(riv_sim main.cc ${riv_sources})

TARGET_LINK_LIBRARIES(riv_sim PRIVATE OpenGL::GL freeglut)
TARGET_INCLUDE_DIRECTORIES(riv_sim PRIVATE ${riv_include_dir} external/freeglut/include)

ADD_CUSTOM_COMMAND(TARGET riv_sim POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${CMAKE_BINARY_DIR}/external/freeglut/bin/libfreeglut.dll"
	$<TARGET_FILE_DIR:riv_sim>
)