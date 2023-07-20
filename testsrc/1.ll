; Filename = ../testsrc/1.c
declare void @llvm.memset.p0.i32(i32*, i8, i32, i1)
@c = global [2 x [5 x [7 x i32]]] [[5 x [7 x i32]] zeroinitializer, [5 x [7 x i32]] [[7 x i32] [i32 22, i32 33, i32 44, i32 55, i32 0, i32 0, i32 0], [7 x i32] [i32 66, i32 77, i32 0, i32 0, i32 0, i32 0, i32 0], [7 x i32] [i32 88, i32 99, i32 1010, i32 0, i32 0, i32 0, i32 0], [7 x i32] zeroinitializer, [7 x i32] zeroinitializer]]
@b = global [1000 x float] zeroinitializer
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
    ret i32 0
}

