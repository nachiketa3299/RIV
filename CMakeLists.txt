CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RIV, LANGUAGES CXX)
SET(PROJECT_DESCRIPTION "RIV - Interactive Visualizer")
SET(CMAKE_CXX_STANDARD 23)

# 소스 파일 경로 및 파일
SET(riv_source_dir ${PROJECT_SOURCE_DIR}/src)

# 아래 변수에 추가
SET(riv_sources
	Vec2.cc
	Vec3.cc
)

LIST(TRANSFORM riv_sources PREPEND ${riv_source_dir}/)

# 빌드 타겟 설정 (이름: RVI (프로젝트 이름과 동일))
ADD_EXECUTABLE(riv_sim main.cc ${riv_sources})
TARGET_INCLUDE_DIRECTORIES(riv_sim PRIVATE ${PROJECT_SOURCE_DIR})