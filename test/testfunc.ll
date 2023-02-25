; ModuleID = 'testfunc.ll'
source_filename = "testfunc.ll"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define i32 @circleArea100(i32 %radius) {
  %1 = mul i32 314, %radius
  %2 = mul i32 %1, %radius
  ret i32 %2
}

define i32 @mac(i32 %a, i32 %b, i32 %c) {
  %1 = mul i32 %b, %c
  %2 = add i32 %a, %1
  ret i32 %2
}

define i32 @f(i32 %a, i32 %b, i32 %c) {
  %1 = mul i32 %b, %b
  %2 = mul i32 4, %a
  %3 = mul i32 %2, %c
  %4 = sub i32 %1, %3
  ret i32 %4
}

define i32 @pnd(i32 %n1, i32 %n2, i32 %p, i32 %Multiplier) {
  %1 = mul i32 %n1, %p
  %2 = sub i32 100, %p
  %3 = mul i32 %n2, %2
  %4 = add i32 %1, %3
  %5 = mul i32 %Multiplier, %4
  ret i32 %5
}

define i32 @rcubed(i32 %return2) {
  %1 = mul i32 %return2, %return2
  %2 = mul i32 %1, %return2
  ret i32 %2
}

define i32 @volume(i32 %pi, i32 %r, i32 %height) {
  %1 = mul i32 %r, %r
  %2 = mul i32 %pi, %1
  %3 = mul i32 %2, %height
  ret i32 %3
}

define i32 @Taylor_1_div_x(i32 %x) {
  %1 = sub i32 %x, 1
  %2 = sub i32 1, %1
  %3 = sub i32 %x, 1
  %4 = sub i32 %x, 1
  %5 = mul i32 %3, %4
  %6 = add i32 %2, %5
  %7 = sub i32 %x, 1
  %8 = sub i32 %x, 1
  %9 = mul i32 %7, %8
  %10 = sub i32 %x, 1
  %11 = mul i32 %9, %10
  %12 = sub i32 %6, %11
  ret i32 %12
}

define i32 @xx(i32 %a, i32 %b, i32 %c, i32 %d) {
  %1 = sub i32 %d, %a
  %2 = mul i32 %1, 0
  %3 = sub i32 %a, %b
  %4 = mul i32 %3, 10
  %5 = sub i32 %b, %c
  %6 = mul i32 %5, 20
  %7 = sub i32 %c, %d
  %8 = mul i32 %7, 30
  %9 = sub i32 %6, %8
  %10 = add i32 %4, %9
  %11 = sub i32 %2, %10
  ret i32 %11
}

define i32 @deepExp(i32 %x, i32 %y, i32 %z, i32 %t) {
  %1 = mul i32 %x, 1
  %2 = mul i32 %y, 2
  %3 = mul i32 %z, 3
  %4 = mul i32 %t, 4
  %5 = mul i32 %x, 11
  %6 = mul i32 %y, 12
  %7 = mul i32 %z, 13
  %8 = mul i32 %t, 14
  %9 = mul i32 %x, 21
  %10 = mul i32 %y, 22
  %11 = mul i32 %z, 23
  %12 = mul i32 %t, 24
  %13 = mul i32 %x, 31
  %14 = mul i32 %y, 32
  %15 = mul i32 %z, 33
  %16 = mul i32 %t, 34
  %17 = sub i32 %15, %16
  %18 = sub i32 %14, %17
  %19 = sub i32 %13, %18
  %20 = sub i32 %12, %19
  %21 = sub i32 %11, %20
  %22 = sub i32 %10, %21
  %23 = sub i32 %9, %22
  %24 = sub i32 %8, %23
  %25 = sub i32 %7, %24
  %26 = sub i32 %6, %25
  %27 = sub i32 %5, %26
  %28 = sub i32 %4, %27
  %29 = sub i32 %3, %28
  %30 = sub i32 %2, %29
  %31 = sub i32 %1, %30
  ret i32 %31
}

define i32 @scalarProd_3d(i32 %x1, i32 %y1, i32 %z1, i32 %x2, i32 %y2, i32 %z2) {
  %1 = mul i32 %x1, %x2
  %2 = mul i32 %y1, %y2
  %3 = add i32 %1, %2
  %4 = mul i32 %z1, %z2
  %5 = add i32 %3, %4
  ret i32 %5
}

define i32 @point_cross_diff(i32 %x1, i32 %y1, i32 %z1, i32 %x2, i32 %y2, i32 %z2) {
  %1 = mul i32 %y1, %z2
  %2 = mul i32 %z1, %y2
  %3 = sub i32 %1, %2
  ret i32 %3
}

define i32 @det3(i32 %a11, i32 %a12, i32 %a13, i32 %a21, i32 %a22, i32 %a23, i32 %a31, i32 %a32, i32 %a33) {
  %1 = mul i32 %a22, %a33
  %2 = mul i32 %a23, %a32
  %3 = sub i32 %1, %2
  %4 = mul i32 %a11, %3
  %5 = mul i32 %a21, %a33
  %6 = mul i32 %a23, %a31
  %7 = sub i32 %5, %6
  %8 = mul i32 %a12, %7
  %9 = sub i32 %4, %8
  %10 = mul i32 %a21, %a32
  %11 = mul i32 %a22, %a31
  %12 = sub i32 %10, %11
  %13 = mul i32 %a13, %12
  %14 = add i32 %9, %13
  ret i32 %14
}
