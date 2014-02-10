; ModuleID = 'top'

@0 = private unnamed_addr constant [15 x i8] c"\22Hello World\22\0A\00"
@1 = private unnamed_addr constant [10 x i8] c"\22n = %d\22\0A\00"

define void @main() {
entry:
  call void @puts(i8* getelementptr inbounds ([15 x i8]* @0, i32 0, i32 0))
  call void (i8*, ...)* @printf(i8* getelementptr inbounds ([10 x i8]* @1, i32 0, i32 0), i32 3)
  ret void
}

declare void @puts(i8*)

declare void @printf(i8*, ...)
