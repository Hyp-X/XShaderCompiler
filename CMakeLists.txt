
# === CMake lists for the HLSL Translator - (09/10/2014) ===

cmake_minimum_required(VERSION 2.8)
project(HLSLTranslator)


# === Build path ===

set(dir ${CMAKE_CURRENT_BINARY_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)


# === Preprocessor definitions ===

add_definitions(-D_CRT_SECURE_NO_WARNINGS)


# === Global files ===

file(GLOB FilesInc	${PROJECT_SOURCE_DIR}/inc/HT/*.*)
file(GLOB FilesSrc	${PROJECT_SOURCE_DIR}/src/*.*)
file(GLOB FilesTest	${PROJECT_SOURCE_DIR}/test/*.*)

set(
	FilesAll
	${FilesInc}
	${FilesSrc}
)


# === Source group folders ===

source_group("inc" FILES ${FilesInc})
source_group("src" FILES ${FilesSrc})
source_group("test" FILES ${FilesTest})


# === Include directories ===

include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/src")


# === Executable ===

add_library(HLSLTranslator STATIC ${FilesAll})
add_executable(TranslationTest ${FilesTest})

target_link_libraries(TranslationTest HLSLTranslator)

set_target_properties(HLSLTranslator PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(TranslationTest PROPERTIES LINKER_LANGUAGE CXX)

