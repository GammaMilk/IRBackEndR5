; Filename = ../testsrc/1.c
declare void @llvm.memset.p0.i32(i32*, i8, i32, i1)
@RADIUS = constant float 0x4016000000000000
@PI = constant float 0x400921fb60000000
@EPS = constant float 0x3eb0c6f7a0000000
@PI_HEX = constant float 0x400921fb60000000
@HEX2 = constant float 0x3fb4000000000000
@FACT = constant float 0xc0e01d0000000000
@EVAL1 = constant float 0x4057c21fc0000000
@EVAL2 = constant float 0x4041475ce0000000
@EVAL3 = constant float 0x4041475ce0000000
@CONV1 = constant float 0x406d200000000000
@CONV2 = constant float 0x40affe0000000000
@MAX = constant i32 1000000000
@TWO = constant i32 2
@THREE = constant i32 3
@FIVE = constant i32 5
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
define float @float_abs(float %arg_0) {
LEntry:
    %v0 = alloca float
    store float %arg_0, float* %v0
    %v1 = load float, float* %v0
    %v2 = sitofp i32 0 to float
    %v3 = fcmp ult float %v1, %v2
    br i1 %v3, label %L1, label %L2
L1:
    %v4 = load float, float* %v0
    %v5 = fsub float 0x0, %v4
    ret float %v5
L2:
    %v6 = load float, float* %v0
    ret float %v6
}

define float @circle_area(i32 %arg_0) {
LEntry:
    %v0 = alloca i32
    store i32 %arg_0, i32* %v0
    %v1 = load float, float* @PI
    %v2 = load i32, i32* %v0
    %v3 = sitofp i32 %v2 to float
    %v4 = fmul float %v1, %v3
    %v5 = load i32, i32* %v0
    %v6 = sitofp i32 %v5 to float
    %v7 = fmul float %v4, %v6
    %v8 = load i32, i32* %v0
    %v9 = load i32, i32* %v0
    %v10 = mul i32 %v8, %v9
    %v11 = load float, float* @PI
    %v12 = sitofp i32 %v10 to float
    %v13 = fmul float %v12, %v11
    %v14 = fadd float %v7, %v13
    %v15 = sitofp i32 2 to float
    %v16 = fdiv float %v14, %v15
    ret float %v16
}

define i32 @float_eq(float %arg_0, float %arg_1) {
LEntry:
    %v0 = alloca float
    %v1 = alloca float
    store float %arg_0, float* %v0
    store float %arg_1, float* %v1
    %v2 = load float, float* %v0
    %v3 = load float, float* %v1
    %v4 = fsub float %v2, %v3
    %v5 = call float @float_abs(float %v4)
    %v6 = load float, float* @EPS
    %v7 = fcmp ult float %v5, %v6
    br i1 %v7, label %L1, label %L3
L1:
    ret i32 1
L2:
    ret i32 0
L3:
    ret i32 0
}

define void @error() {
LEntry:
    call void @putch(i32 101)
    call void @putch(i32 114)
    call void @putch(i32 114)
    call void @putch(i32 111)
    call void @putch(i32 114)
    call void @putch(i32 10)
    ret void
}

define void @ok() {
LEntry:
    call void @putch(i32 111)
    call void @putch(i32 107)
    call void @putch(i32 10)
    ret void
}

define void @assert(i32 %arg_0) {
LEntry:
    %v0 = alloca i32
    store i32 %arg_0, i32* %v0
    %v1 = load i32, i32* %v0
    %v2 = icmp eq i32 %v1, 0
    %v3 = zext i1 %v2 to i32
    %v4 = icmp ne i32 %v3, 0
    br i1 %v4, label %L1, label %L3
L1:
    call void @error()
    br label %L2
L2:
    ret void
L3:
    call void @ok()
    br label %L2
}

define void @assert_not(i32 %arg_0) {
LEntry:
    %v0 = alloca i32
    store i32 %arg_0, i32* %v0
    %v1 = load i32, i32* %v0
    %v2 = icmp ne i32 %v1, 0
    br i1 %v2, label %L1, label %L3
L1:
    call void @error()
    br label %L2
L2:
    ret void
L3:
    call void @ok()
    br label %L2
}

define i32 @main() {
LEntry:
    %v24 = alloca i32
    %v25 = alloca i32
    %v26 = alloca [10 x float]
    %v31 = alloca i32
    %v37 = alloca float
    %v39 = alloca float
    %v45 = alloca float
    %v0 = load float, float* @HEX2
    %v1 = load float, float* @FACT
    %v2 = call i32 @float_eq(float %v0, float %v1)
    call void @assert_not(i32 %v2)
    %v3 = load float, float* @EVAL1
    %v4 = load float, float* @EVAL2
    %v5 = call i32 @float_eq(float %v3, float %v4)
    call void @assert_not(i32 %v5)
    %v6 = load float, float* @EVAL2
    %v7 = load float, float* @EVAL3
    %v8 = call i32 @float_eq(float %v6, float %v7)
    call void @assert(i32 %v8)
    %v9 = load float, float* @RADIUS
    %v10 = fptosi float %v9 to i32
    %v11 = call float @circle_area(i32 %v10)
    %v12 = load i32, i32* @FIVE
    %v13 = call float @circle_area(i32 %v12)
    %v14 = call i32 @float_eq(float %v11, float %v13)
    call void @assert(i32 %v14)
    %v15 = load float, float* @CONV1
    %v16 = load float, float* @CONV2
    %v17 = call i32 @float_eq(float %v15, float %v16)
    call void @assert_not(i32 %v17)
    %v18 = fcmp une float 0x3ff8000000000000, 0x0000000000000000
    br i1 %v18, label %L1, label %L2
L1:
    call void @ok()
    br label %L2
L2:
    %v19 = fcmp une float 0x3ff0000000000000, 0x0000000000000000
    br i1 %v19, label %L3, label %L4
L3:
    call void @ok()
    br label %L4
L4:
    %v20 = fcmp une float 0x0, 0x0000000000000000
    br i1 %v20, label %L7, label %L6
L5:
    call void @error()
    br label %L6
L6:
    %v22 = icmp ne i32 0, 0
    br i1 %v22, label %L8, label %L10
L7:
    %v21 = icmp ne i32 3, 0
    br i1 %v21, label %L5, label %L6
L8:
    call void @ok()
    br label %L9
L9:
    store i32 1, i32* %v24
    store i32 0, i32* %v25
    %v27 = bitcast [10 x float]* %v26 to i32*
    call void @llvm.memset.p0.i32(i32* %v27, i8 0, i32 40, i1 false)
    %v28 = getelementptr [10 x float], [10 x float]* %v26, i32 0, i32 0
    store float 0x3ff0000000000000, float* %v28
    %v29 = sitofp i32 2 to float
    %v30 = getelementptr [10 x float], [10 x float]* %v26, i32 0, i32 1
    store float %v29, float* %v30
    %v32 = getelementptr [10 x float], [10 x float]* %v26, i32 0, i32 0
    %v33 = call i32 @getfarray(float* %v32)
    store i32 %v33, i32* %v31
    br label %L11
L10:
    %v23 = fcmp une float 0x3fd3333340000000, 0x0000000000000000
    br i1 %v23, label %L8, label %L9
L11:
    %v34 = load i32, i32* %v24
    %v35 = load i32, i32* @MAX
    %v36 = icmp slt i32 %v34, %v35
    br i1 %v36, label %L12, label %L13
L12:
    %v38 = call float @getfloat()
    store float %v38, float* %v37
    %v40 = load float, float* @PI
    %v41 = load float, float* %v37
    %v42 = fmul float %v40, %v41
    %v43 = load float, float* %v37
    %v44 = fmul float %v42, %v43
    store float %v44, float* %v39
    %v46 = load float, float* %v37
    %v47 = fptosi float %v46 to i32
    %v48 = call float @circle_area(i32 %v47)
    store float %v48, float* %v45
    %v49 = load i32, i32* %v25
    %v50 = getelementptr [10 x float], [10 x float]* %v26, i32 0, i32 %v49
    %v51 = load i32, i32* %v25
    %v52 = getelementptr [10 x float], [10 x float]* %v26, i32 0, i32 %v51
    %v53 = load float, float* %v52
    %v54 = load float, float* %v37
    %v55 = fadd float %v53, %v54
    store float %v55, float* %v50
    %v56 = load float, float* %v39
    call void @putfloat(float %v56)
    call void @putch(i32 32)
    %v57 = load float, float* %v45
    %v58 = fptosi float %v57 to i32
    call void @putint(i32 %v58)
    call void @putch(i32 10)
    %v59 = load i32, i32* %v24
    %v60 = sitofp i32 %v59 to float
    %v61 = fmul float %v60, 0x4024000000000000
    %v62 = fptosi float %v61 to i32
    store i32 %v62, i32* %v24
    %v63 = load i32, i32* %v25
    %v64 = add i32 %v63, 1
    store i32 %v64, i32* %v25
    br label %L11
L13:
    %v65 = load i32, i32* %v31
    %v66 = getelementptr [10 x float], [10 x float]* %v26, i32 0, i32 0
    call void @putfarray(i32 %v65, float* %v66)
    ret i32 0
}

