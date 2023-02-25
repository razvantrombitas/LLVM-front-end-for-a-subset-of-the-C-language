; ModuleID = 'testbasic.ll'
source_filename = "testbasic.ll"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define i32 @pi100() {
  ret i32 314
}

define i32 @e1000() {
  ret i32 2718
}

define i32 @ref17k() {
  ret i32 17460
}
