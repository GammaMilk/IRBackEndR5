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
define i32 @add(i32 %arg_0, i32 %arg_1, i32 %arg_2, i32 %arg_3, i32 %arg_4, i32 %arg_5, i32 %arg_6, i32 %arg_7, i32 %arg_8, i32 %arg_9, i32 %arg_10, i32 %arg_11, float %arg_12, float %arg_13) {
LEntry:
    %v0 = alloca i32
    %v1 = alloca i32
    %v2 = alloca i32
    %v3 = alloca i32
    %v4 = alloca i32
    %v5 = alloca i32
    %v6 = alloca i32
    %v7 = alloca i32
    %v8 = alloca i32
    %v9 = alloca i32
    %v10 = alloca i32
    %v11 = alloca i32
    %v12 = alloca float
    %v13 = alloca float
    store i32 %arg_0, i32* %v0
    store i32 %arg_1, i32* %v1
    store i32 %arg_2, i32* %v2
    store i32 %arg_3, i32* %v3
    store i32 %arg_4, i32* %v4
    store i32 %arg_5, i32* %v5
    store i32 %arg_6, i32* %v6
    store i32 %arg_7, i32* %v7
    store i32 %arg_8, i32* %v8
    store i32 %arg_9, i32* %v9
    store i32 %arg_10, i32* %v10
    store i32 %arg_11, i32* %v11
    store float %arg_12, float* %v12
    store float %arg_13, float* %v13
    store i32 1, i32* %v10
    %v14 = load i32, i32* %v10
    %v15 = load i32, i32* %v11
    %v16 = srem i32 %v14, %v15
    ret i32 %v16
}

define i32 @main() {
LEntry:
    %v0 = call i32 @add(i32 1, i32 2, i32 3, i32 4, i32 5, i32 6, i32 7, i32 8, i32 9, i32 10, i32 11, i32 12, float 0x402a000000000000, float 0x402c000000000000)
    ret i32 %v0
}

