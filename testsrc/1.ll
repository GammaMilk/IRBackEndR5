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
define i32 @t(i32* %arg_0) {
LEntry:
    %v0 = alloca i32*
    store i32* %arg_0, i32** %v0
    %v1 = load i32*, i32** %v0
    %v2 = getelementptr i32, i32* %v1, i32 10
    %v3 = load i32, i32* %v2
    ret i32 %v3
}

define i32 @p([10 x i32]* %arg_0) {
LEntry:
    %v0 = alloca [10 x i32]*
    store [10 x i32]* %arg_0, [10 x i32]** %v0
    %v1 = load [10 x i32]*, [10 x i32]** %v0
    %v2 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0
    %v3 = getelementptr [10 x i32], [10 x i32]* %v2, i32 0, i32 0
    %v4 = call i32 @t(i32* %v3)
    ret i32 %v4
}

define i32 @main() {
LEntry:
    %v0 = alloca [10 x [10 x i32]]
    %v1 = bitcast [10 x [10 x i32]]* %v0 to i32*
    call void @llvm.memset.p0.i32(i32* %v1, i8 0, i32 400, i1 false)
    %v2 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* %v0, i32 0, i32 0
    %v3 = getelementptr [10 x i32], [10 x i32]* %v2, i32 0, i32 0
    %v4 = call i32 @t(i32* %v3)
    ret i32 0
}

