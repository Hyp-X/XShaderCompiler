
# === CMake lists for the XShaderCompiler - (09/10/2014) ===

cmake_minimum_required(VERSION 2.8)
project(XShaderCompiler)


# === Build path ===

set(BUILD_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/build")
set(EXECUTABLE_OUTPUT_PATH ${BUILD_OUTPUT_PATH} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${BUILD_OUTPUT_PATH} CACHE PATH "Build directory" FORCE)
set(INSTALL_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "Installation directory" FORCE)


# === Options ===

option(XSC_BUILD_SHELL "Build XShaderCompiler shell 'xsc'" ON)
option(XSC_BUILD_DEBUGGER "Build XShaderCompiler debugger 'xsc_debugger' (requires wxWidgets library)" OFF)
option(XSC_SHARED_LIB "Build XShaderCompiler as a shared library instead of a static library" OFF)
option(XSC_ENABLE_EASTER_EGGS "Enables little easter eggs" OFF)
option(XSC_MEMORY_POOL "Enables the memory pool for optimized memory allocation (Experimental)" OFF)


# === Preprocessor definitions ===

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

if(XSC_SHARED_LIB)
	add_definitions(-DXSC_SHARED_LIB)
endif()

if(XSC_ENABLE_EASTER_EGGS)
	add_definitions(-DXSC_ENABLE_EASTER_EGGS)
endif()

if(XSC_MEMORY_POOL)
	add_definitions(-DXSC_ENABLE_MEMORY_POOL)
endif()


# === Global files ===

file(GLOB FilesInc ${PROJECT_SOURCE_DIR}/inc/Xsc/*.*)
file(GLOB FilesSrcCompiler ${PROJECT_SOURCE_DIR}/src/Compiler/*.*)
file(GLOB FilesSrcCompilerAST ${PROJECT_SOURCE_DIR}/src/Compiler/AST/*.*)
file(GLOB FilesSrcCompilerASTVisitor ${PROJECT_SOURCE_DIR}/src/Compiler/AST/Visitor/*.*)
file(GLOB FilesSrcCompilerFrontend ${PROJECT_SOURCE_DIR}/src/Compiler/Frontend/*.*)
file(GLOB FilesSrcCompilerFrontendHLSL ${PROJECT_SOURCE_DIR}/src/Compiler/Frontend/HLSL/*.*)
file(GLOB FilesSrcCompilerBackend ${PROJECT_SOURCE_DIR}/src/Compiler/Backend/*.*)
file(GLOB FilesSrcCompilerBackendGLSL ${PROJECT_SOURCE_DIR}/src/Compiler/Backend/GLSL/*.*)
file(GLOB FilesSrcShell ${PROJECT_SOURCE_DIR}/src/Shell/*.*)
file(GLOB FilesSrcDebugger ${PROJECT_SOURCE_DIR}/src/Debugger/*.*)

if(WIN32)
	file(GLOB FilesSrcCompilerPlatform ${PROJECT_SOURCE_DIR}/src/Compiler/Platform/Win32/*.*)
else()
	file(GLOB FilesSrcCompilerPlatform ${PROJECT_SOURCE_DIR}/src/Compiler/Platform/Unix/*.*)
endif()

set(
	FilesCompilerAll
	${FilesInc}
	${FilesSrcCompiler}
	${FilesSrcCompilerAST}
	${FilesSrcCompilerASTVisitor}
	${FilesSrcCompilerPlatform}
	${FilesSrcCompilerFrontend}
	${FilesSrcCompilerFrontendHLSL}
	${FilesSrcCompilerBackend}
	${FilesSrcCompilerBackendGLSL}
)


# === Source group folders ===

source_group("inc\\Xsc" FILES ${FilesInc})
source_group("src" FILES ${FilesSrcCompiler} ${FilesSrcShell} ${FilesSrcDebugger})
source_group("src\\AST" FILES ${FilesSrcCompilerAST})
source_group("src\\AST\\Visitor" FILES ${FilesSrcCompilerASTVisitor})
source_group("src\\Platform" FILES ${FilesSrcCompilerPlatform})
source_group("src\\Frontend" FILES ${FilesSrcCompilerFrontend})
source_group("src\\Frontend\\HLSL" FILES ${FilesSrcCompilerFrontendHLSL})
source_group("src\\Backend" FILES ${FilesSrcCompilerBackend})
source_group("src\\Backend\\GLSL" FILES ${FilesSrcCompilerBackendGLSL})


# === Include directories ===

include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/src/Compiler")
include_directories("${PROJECT_SOURCE_DIR}/src/Compiler/AST")
include_directories("${PROJECT_SOURCE_DIR}/src/Compiler/AST/Visitor")
include_directories("${PROJECT_SOURCE_DIR}/src/Compiler/Frontend")
include_directories("${PROJECT_SOURCE_DIR}/src/Compiler/Frontend/HLSL")
include_directories("${PROJECT_SOURCE_DIR}/src/Compiler/Backend")
include_directories("${PROJECT_SOURCE_DIR}/src/Compiler/Backend/GLSL")


# === Executable ===

if(XSC_SHARED_LIB)
	add_library(xsc_core SHARED ${FilesCompilerAll})
else()
	add_library(xsc_core STATIC ${FilesCompilerAll})
endif()

set_target_properties(xsc_core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(xsc_core PRIVATE cxx_range_for)

if(XSC_BUILD_SHELL)
	add_executable(xsc ${FilesSrcShell})
	set_target_properties(xsc PROPERTIES LINKER_LANGUAGE CXX)
	target_link_libraries(xsc xsc_core)
	target_compile_features(xsc PRIVATE cxx_range_for)
endif()

if(XSC_BUILD_DEBUGGER)
	if(WIN32)
		add_executable(xsc_debugger WIN32 ${FilesSrcDebugger} "${PROJECT_SOURCE_DIR}/src/Debugger/Resources.rc")
	else()
		add_executable(xsc_debugger ${FilesSrcDebugger})
	endif()
	
	set_target_properties(xsc_debugger PROPERTIES LINKER_LANGUAGE CXX)
	target_link_libraries(xsc_debugger xsc_core)
	target_compile_features(xsc_debugger PRIVATE cxx_range_for)
	
	# wxWidgets Libs
	find_package(wxWidgets REQUIRED adv aui base core stc propgrid richtext scintilla)
	if(wxWidgets_FOUND)
		message("Found wxWidgets library")
		include_directories(${wxWidgets_INCLUDE_DIRS})
		target_link_libraries(xsc_debugger ${wxWidgets_LIBRARIES})
	else(wxWidgets_FOUND)
		message(SEND_ERROR "Missing wxWidgets library")
	endif(wxWidgets_FOUND)
endif()


# === Installation Rules ===

install(
	TARGETS xsc_core xsc
	DESTINATION ${INSTALL_OUTPUT_PATH}
)

