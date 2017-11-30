# swenston/sort (2017.24.11)

```
export LLVM_COMPILER=clang
CC=wllvm make multidemo
extract-bc multidemo
cp multidemo.bc ../../../java-llvm-ir-builder-dev/sulong/multidemo.bc
```

## Execution on sulong:

```
time mx --jdk jvmci --dynamicimports=/compiler lli multidemo.bc  -Dgraal.TraceTruffleCompilation=true -Dgraal.TraceTruffleCompilation=true
```

Shows lots of opt invalidated even when the program runs > 1 minute, which is not correct for a program with only does the same

```
[truffle] opt done         @sorter_quick_sort_recursive <opt>                          |ASTSize     839/  839 |Time    51(  45+6   )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress 0x7f0aea4acd90 |Source     sort.h:696 
[truffle] opt done         @sorter_quick_sort_recursive <opt>                          |ASTSize     839/  839 |Time    49(  42+7   )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress 0x7f0aea59a890 |Source     sort.h:696 
[truffle] opt invalidated  @run_tests                                                  |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @run_tests                                                  |ASTSize    1458/ 2128 |Time   254( 130+124 )ms |DirectCallNodes I   28/D    3 |GraalNodes  3818/ 4443 |CodeSize        13729 |CodeAddress       0x0 |Source multidemo.c:127 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    16(  13+2   )ms |DirectCallNodes I    0/D    1 |GraalNodes    28/   31 |CodeSize          176 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    16(  15+2   )ms |DirectCallNodes I    0/D    1 |GraalNodes    28/   31 |CodeSize          176 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    51(  44+7   )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @run_tests                                                  |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @run_tests                                                  |ASTSize    1458/ 2128 |Time   263( 143+120 )ms |DirectCallNodes I   28/D    3 |GraalNodes  3818/ 4443 |CodeSize        13729 |CodeAddress       0x0 |Source multidemo.c:127 
[truffle] opt done         @sorter_quick_sort_recursive <opt>                          |ASTSize     839/  839 |Time    16(  15+1   )ms |DirectCallNodes I    0/D    1 |GraalNodes    28/   31 |CodeSize          176 |CodeAddress 0x7f0ae9dd6a90 |Source     sort.h:696 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    49(  40+9   )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    40(  33+7   )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    47(  35+12  )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @run_tests                                                  |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @run_tests                                                  |ASTSize    1458/ 2128 |Time   243( 125+117 )ms |DirectCallNodes I   28/D    3 |GraalNodes  3818/ 4443 |CodeSize        13729 |CodeAddress       0x0 |Source multidemo.c:127 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    15(  13+2   )ms |DirectCallNodes I    0/D    1 |GraalNodes    28/   31 |CodeSize          176 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    45(  35+10  )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt done         @sorter_quick_sort_recursive <opt>                          |ASTSize     839/  839 |Time    46(  37+9   )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress 0x7f0ae96a9590 |Source     sort.h:696 
[truffle] opt done         @sorter_quick_sort_recursive <opt>                          |ASTSize     839/  839 |Time    49(  39+10  )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress 0x7f0ae9a41950 |Source     sort.h:696 
[truffle] opt invalidated  @run_tests                                                  |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @run_tests                                                  |ASTSize    1458/ 2128 |Time   275( 137+138 )ms |DirectCallNodes I   28/D    3 |GraalNodes  3818/ 4443 |CodeSize        13729 |CodeAddress       0x0 |Source multidemo.c:127 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    43(  34+9   )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @sorter_quick_sort_recursive                                |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @sorter_quick_sort_recursive                                |ASTSize     839/  839 |Time    50(  38+12  )ms |DirectCallNodes I    0/D    1 |GraalNodes   409/  400 |CodeSize         1118 |CodeAddress       0x0 |Source     sort.h:696 
[truffle] opt invalidated  @run_tests                                                  |SourceClass OptimizedAssumption |Source Assumption(invalid, name=null) |Reason assumption already invalidated when installing code 
[truffle] opt done         @run_tests                                                  |ASTSize    1458/ 2128 |Time   271( 151+121 )ms |DirectCallNodes I   28/D    3 |GraalNodes  3818/ 4443 |CodeSize        13729 |CodeAddress       0x0 |Source multidemo.c:127
```

## Patch (not cleaned up)

```diff
diff --git a/multidemo.c b/multidemo.c
index 90e8316..4fdf8bf 100644
--- a/multidemo.c
+++ b/multidemo.c
@@ -59,8 +59,8 @@
 
 /* Used to control the demo */
 #define SEED 123
-#define SIZE 10000
-#define RUNS 1
+#define SIZE 400
+#define RUNS 20
 
 /* helper functions */
 void verify(int64_t *dst, const int size) {
@@ -131,79 +131,101 @@ void run_tests(void) {
   double start_time;
   double end_time;
   double total_time;
-  printf("Running tests\n");
+  //printf("Running tests\n");
   srand48(SEED);
-  total_time = 0.0;
-
+  //total_time = 0.0;
+start_time = utime();
   for (i = 0; i < RUNS; i++) {
     fill(arr, SIZE);
     memcpy(dst, arr, sizeof(int64_t) * SIZE);
-    start_time = utime();
+    
     qsort(dst, SIZE, sizeof(int64_t), simple_cmp);
-    end_time = utime();
-    total_time += end_time - start_time;
+    
+    
     verify(dst, SIZE);
   }
-
-  printf("stdlib qsort time:          %10.2f us per iteration\n", total_time / RUNS);
+//end_time = utime();
+//total_time += end_time - start_time;
+ // printf("stdlib qsort time:          %10.2f us per iteration\n", total_time / RUNS);
 #if !defined(__linux__) && !defined(__CYGWIN__)
-  srand48(SEED);
-  total_time = 0.0;
 
+
+  srand48(SEED);
+  //total_time = 0.0;
+//start_time = utime();
   for (i = 0; i < RUNS; i++) {
     fill(arr, SIZE);
     memcpy(dst, arr, sizeof(int64_t) * SIZE);
-    start_time = utime();
+    
     heapsort(dst, SIZE, sizeof(int64_t), simple_cmp);
-    end_time = utime();
-    total_time += end_time - start_time;
+    
     verify(dst, SIZE);
   }
+//end_time = utime();
+   // total_time += end_time - start_time;
+ // printf("stdlib heapsort time:       %10.2f us per iteration\n", total_time / RUNS);
 
-  printf("stdlib heapsort time:       %10.2f us per iteration\n", total_time / RUNS);
   srand48(SEED);
-  total_time = 0.0;
+  //total_time = 0.0;
+
+//start_time = utime();
 
   for (i = 0; i < RUNS; i++) {
     fill(arr, SIZE);
     memcpy(dst, arr, sizeof(int64_t) * SIZE);
-    start_time = utime();
+    
     mergesort(dst, SIZE, sizeof(int64_t), simple_cmp);
-    end_time = utime();
-    total_time += end_time - start_time;
+    
     verify(dst, SIZE);
   }
-
-  printf("stdlib mergesort time:      %10.2f us per iteration\n", total_time / RUNS);
+//end_time = utime();
+    //total_time += end_time - start_time;
+  //printf("stdlib mergesort time:      %10.2f us per iteration\n", total_time / RUNS);
 #endif
   srand48(SEED);
-  total_time = 0.0;
-
+  //total_time = 0.0;
+//start_time = utime();
   for (i = 0; i < RUNS; i++) {
     fill(arr, SIZE);
     memcpy(dst, arr, sizeof(int64_t) * SIZE);
-    start_time = utime();
+    
     sorter_quick_sort(dst, SIZE);
-    end_time = utime();
-    total_time += end_time - start_time;
+
     verify(dst, SIZE);
   }
-
-  printf("quick sort time:            %10.2f us per iteration\n", total_time / RUNS);
+    //end_time = utime();
+    //total_time += end_time - start_time;
+  //printf("quick sort time:            %10.2f us per iteration\n", total_time / RUNS);
   srand48(SEED);
   total_time = 0.0;
 
   for (i = 0; i < RUNS; i++) {
     fill(arr, SIZE);
     memcpy(dst, arr, sizeof(int64_t) * SIZE);
-    start_time = utime();
+    //start_time = utime();
     sorter_selection_sort(dst, SIZE);
-    end_time = utime();
-    total_time += end_time - start_time;
+    //end_time = utime();
+    //total_time += end_time - start_time;
     verify(dst, SIZE);
   }
 
-  printf("selection sort time:        %10.2f us per iteration\n", total_time / RUNS);
+  //printf("selection sort time:        %10.2f us per iteration\n", total_time / RUNS);
+
+  //total_time = 0.0;
+//start_time = utime();
+  for (i = 0; i < RUNS; i++) {
+    fill(arr, SIZE);
+    memcpy(dst, arr, sizeof(int64_t) * SIZE);
+    
+    sorter_selection_sort(dst, SIZE);
+
+    verify(dst, SIZE);
+  }
+   // end_time = utime();
+   // total_time += end_time - start_time;
+  //printf("selection sort time2:        %10.2f us per iteration\n", total_time / RUNS);
+
+  return;
   srand48(SEED);
   total_time = 0.0;
   
@@ -455,8 +477,27 @@ void run_tests2(void) {
 
   printf("tim sort time:              %10.2f us per iteration\n", total_time / RUNS);
 }
+
+void my_test() {
+    for(int i=0; i < 200; i++) {
+      run_tests();
+
+      // run_tests2();
+  }
+}
+
 int main(void) {
-  run_tests();
-  run_tests2();
+  for(int i=0; i < 100; i++) {
+      my_test();
+      printf(".");
+      fflush(stdout);
+      //run_tests2();
+  }
+  double start_time = utime();
+  my_test();
+  //run_tests2();
+  double end_time = utime();
+  printf("\n######################################\n");
+  printf("time testsuite:              %10.2f us\n", end_time - start_time);
   return 0;
 }
```


# rigtorp/ipc-bench (2017.30.11)

```
export LLVM_COMPILER=clang
CC=wllvm make
extract-bc tcp_lat
cp tcp_lat.bc ../../../java-llvm-ir-builder-dev/sulong/tcp_lat.bc
```

command uses fork -> not usable in sulong yet
benchmark questionable, because it's mainly targeted at the host system


# nitlang/nit (2017.30.11)

```
sudo pacman -S ccache

export LLVM_COMPILER=clang
CC=wllvm make
```

Some problems with building the benchmarks


# wbhart/bsdnt (2017.30.11)

```
export LLVM_COMPILER=clang
./configure
make AS='wllvm' CC='wllvm'
extract-bc build/test/t-nn_linear
cp build/test/t-nn_linear.bc ../../../java-llvm-ir-builder-dev/sulong/t-nn_linear.bc
```

Similar bug found as for: swenston/sort

Bugreport: https://github.com/graalvm/sulong/issues/824


# antirez/otree (2017.30.11)

```
export LLVM_COMPILER=clang
wllvm -o btree_example btree.c btree_example.c -Wall -g -rdynamic -ggdb -O2  # -W causes wllvm to not work?
extract-bc btree_example
cp btree_example.bc ../../../java-llvm-ir-builder-dev/sulong/btree_example.bc
```

```
time mx --jdk jvmci --dynamicimports=/compiler lli btree_example.bc allocfree 10000000000 200000 -Dgraal.TraceTruffleCompilation=true -Dgraal.TraceTruffleCompilation=true
```

# chrismoos/hash-ring (2017.30.11)

```
sudo pacman -S erlang  # for test script (didn't worked)
```

# zhemao/libds (2017.30.11)

```
export LLVM_COMPILER=clang
make CC='wllvm' test
extract-bc vectest
cp vectest.bc ../../../java-llvm-ir-builder-dev/sulong/vectest.bc
```

# openSUSE/libsolv (2017.30.11)

```
cmake .
make test # TODO: continue
