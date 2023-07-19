; Filename = ../testsrc/1.c
declare void @llvm.memset.p0.i32(i32*, i8, i32, i1)
@a = global [10 x [10 x i32]] [[10 x i32] [i32 2, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0], [10 x i32] zeroinitializer, [10 x i32] zeroinitializer, [10 x i32] zeroinitializer, [10 x i32] zeroinitializer, [10 x i32] zeroinitializer, [10 x i32] zeroinitializer, [10 x i32] zeroinitializer, [10 x i32] zeroinitializer, [10 x i32] zeroinitializer]
@b = global i32 0
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
define i32 @main() {
LEntry:
    %v0 = alloca i32
    %v1 = alloca i32
    store i32 1, i32* %v0
    %v2 = load i32, i32* %v0
    store i32 %v2, i32* %v1
    %v3 = load i32, i32* %v0
    store i32 %v3, i32* %v1
    %v4 = load i32, i32* %v0
    store i32 %v4, i32* %v1
    %v5 = load i32, i32* %v0
    store i32 %v5, i32* %v1
    %v6 = load i32, i32* %v0
    store i32 %v6, i32* %v1
    %v7 = load i32, i32* %v0
    store i32 %v7, i32* %v1
    %v8 = load i32, i32* %v0
    store i32 %v8, i32* %v1
    %v9 = load i32, i32* %v0
    store i32 %v9, i32* %v1
    %v10 = load i32, i32* %v0
    store i32 %v10, i32* %v1
    ret i32 1
}

