# cse291_project

1. 编译

   ```bash
   scons build/RISCV/gem5.opt -jN
   ```

2. 运行 

   输出trace.txt: 

   ```bash
   build/RISCV/gem5.opt --debug-flags=O3CPUAll --debug-file=trace.txt configs/example/se.py --cpu-type=RiscvO3CPU --caches --l2cache -c ../test_program/xxx > ../log/yyy (输出信息有点多，因此先把结果输出到文件中)
   ```

      不输出trace.txt:

   ```bash
   build/RISCV/gem5.opt configs/example/se.py --cpu-type=RiscvO3CPU --caches --l2cache -c ../test_program/xxx > ../log/yyy
   ```

3. 查看结果 
   gem5/m5out/stats.txt可查看condBranchInstsIssued, condBranchSrcReady, srcReadyRate变量的统计结果，文件中有对变量含义的详细描述;
   
   gem5/m5out/trace.txt可查看cpu运行时的trace.
