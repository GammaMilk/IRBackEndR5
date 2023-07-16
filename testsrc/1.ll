; Filename = ../testsrc/1.c
declare void @llvm.memset.p0.i32(i32*, i8, i32, i1)
declare i32 @getint()
declare float @getfloat()
declare i32 @getch()
declare i32 @getarray(i32*)
declare i32 @getfarray(float*)
declare void @putint(i32)
declare void @putfloat(float)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare void @putfarray(i32, float*)
declare void @_sysy_starttime(i32)
declare void @_sysy_stoptime(i32)

define i32 @func(i32 %arg_0) {
LEntry:
    %v0 = alloca i32
    store i32 %arg_0, i32* %v0
    load i32, i32* %v0
    ret i32 0
}

define i32 @main() {
LEntry:
    %v0 = alloca i32
    store i32 114514, i32* %v0
    %v1 = alloca float
    store float 1919810.0, float* %v1
    %v2 = load i32, i32* %v0
    %v3 = getelementptr i32, i32* %v0, i32 1
    %v4 = call i32 @func(i32 %v2)
    br label %L1
L1:
    ret i32 0
}

