; ModuleID = 'top'

@0 = private unnamed_addr constant [8 x i8] c"\22toto\22\0A\00"

define void @main() {
entry:
  call void @puts(i8* getelementptr inbounds ([8 x i8]* @0, i32 0, i32 0))
  ret void
}

declare void @puts(i8*)
