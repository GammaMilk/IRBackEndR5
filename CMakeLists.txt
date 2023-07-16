cmake_minimum_required(VERSION 3.15)

project(IRBackEndR5)
set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

# add antlr4
include_directories(/usr/local/include/antlr4-runtime)
link_directories(/usr/local/lib)
# multi-platform dependency
if (WIN32)
    include_directories("C:\\Program Files (x86)\\LIBANTLR4\\include\\antlr4-runtime")
    link_directories("F:\\Downloads\\antlr4-cpp-runtime-4.13.0-source\\cmake-build-debug-gcc112\\runtime")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MT")
endif (WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# add source files like CBaseListener.cpp, CBaseVisitor.cpp, etc.
file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST} R5Logger.h R5VisitorGenIRTree.cpp R5VisitorGenIRTree.h R5Builder.cpp R5Builder.h R5IR/R5IRAST.cpp R5IR/R5IRAST.h R5IR/R5IRType.cpp R5IR/R5IRType.h R5Def.h R5Global.cpp R5Global.h R5IR/R5IRInst.cpp R5IR/R5IRInst.h R5IR/R5IRFuncDef.cpp R5IR/R5IRFuncDef.h R5IR/R5IRFuncDecl.cpp R5IR/R5IRFuncDecl.h R5IR/R5IRGlobalVar.h R5IR/R5IRGlobalConst.h R5Inst.cpp R5Inst.h R5ASMProgram.cpp R5ASMProgram.h R5IR/R5IRBasicBlock.cpp R5IR/R5IRBasicBlock.h R5IR/R5IRVal.cpp R5IR/R5IRVal.h R5IR/R5IRBrInst.h)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/antlr4-runtime)
target_link_libraries(${PROJECT_NAME} antlr4-runtime)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "F:/Downloads/antlr4-cpp-runtime-4.13.0-source/cmake-build-debug-gcc112/runtime/libantlr4-runtime.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying libantlr4-runtime.dll to executable directory"
            )
endif()