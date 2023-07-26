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
    include_directories("C:/Program Files (x86)/LIBANTLR4/include/antlr4-runtime")
    link_directories("E:\\alter\\cmake-build-debug\\runtime")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MT")
endif (WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# add source files like CBaseListener.cpp, CBaseVisitor.cpp, etc.
file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST} R5Logger.h MiddleIR/GenIRAST.cpp MiddleIR/GenIRAST.h R5Builder.cpp R5Builder.h MiddleIR/MiddleIRAST.cpp MiddleIR/MiddleIRAST.h MiddleIR/MiddleIRType.cpp MiddleIR/MiddleIRType.h R5Def.h MiddleIR/MiddleIRInst.cpp MiddleIR/MiddleIRInst.h MiddleIR/MiddleIRFuncDef.cpp MiddleIR/MiddleIRFuncDef.h MiddleIR/MiddleIRFuncDecl.cpp MiddleIR/MiddleIRFuncDecl.h R5ASMProgram.cpp R5ASMProgram.h MiddleIR/MiddleIRBasicBlock.cpp MiddleIR/MiddleIRBasicBlock.h MiddleIR/MiddleIRVal.cpp MiddleIR/MiddleIRVal.h MiddleIR/MiddleIRBrInst.h MiddleOpt/IROptimizer.cpp MiddleOpt/IROptimizer.h MiddleOpt/IROptimizerBase.cpp MiddleOpt/IROptimizerBase.h MiddleOpt/NoneOptimizer.cpp MiddleOpt/NoneOptimizer.h MiddleOpt/RedundantLoadEliminationOptimizer.cpp MiddleOpt/RedundantLoadEliminationOptimizer.h R5Emitter/R5Program.cpp R5Emitter/R5Program.h R5Emitter/R5IREmitter.h R5Emitter/R5IREmitter.cpp R5Emitter/R5Function.cpp R5Emitter/R5Function.h R5Emitter/R5AsmStrangeFake.cpp R5Emitter/R5AsmStrangeFake.h R5Emitter/R5Yin.cpp R5Emitter/R5Yin.h R5Emitter/R5Yang.cpp R5Emitter/R5Yang.h R5Emitter/R5Taichi.cpp R5Emitter/R5Taichi.h MiddleIR/ArrayHelper.h R5Emitter/R5FakeSeihai.cpp R5Emitter/R5FakeSeihai.h R5Emitter/R5Ru.cpp R5Emitter/R5Ru.h R5Emitter/R5Lai.cpp R5Emitter/R5Lai.h R5Emitter/R5Lai64.cpp R5Emitter/R5Lai64.h R5Emitter/R5Allot.cpp R5Emitter/R5Allot.h R5Emitter/R5TaichiMap.cpp R5Emitter/R5TaichiMap.h)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/antlr4-runtime)
target_link_libraries(${PROJECT_NAME} antlr4-runtime)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "E:\\alter\\cmake-build-debug\\runtime\\libantlr4-runtime.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying libantlr4-runtime.dll to executable directory"
            )
endif ()