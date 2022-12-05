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

编译
scons build/X86/gem5.opt -j4

直接跑一个程序（不需要内部操作系统）：
build/X86/gem5.opt configs/example/se.py -c ../test
使用O3 cpu：
build/X86/gem5.opt configs/example/se.py --cpu-type=DerivO3CPU  --caches -c ../test

跑有操作系统的：
build/X86/gem5.opt configs/example/fs.py --disk-image=linux-x86.img

看o3的执行：
build/X86/gem5.opt --debug-flags=O3PipeView --debug-start=[起始tick] --debug-file=trace.out configs/example/se.py --cpu-type=DerivO3CPU --caches -c ../test -m [结束tick]
./util/o3-pipeview.py -c 500 -o pipeview.out --color m5out/trace.out
less -r pipeview.out

build/X86/gem5.opt configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache -c ../programs/spectre

加trace
build/X86/gem5.opt --debug-flags=O3CPUAll --debug-file=trace.txt configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache -c ../programs/flush_test

加prefetcher
build/X86/gem5.opt configs/example/se.py --cpu-type=DerivO3CPU  --caches --l2cache --l1d-hwp-type=StridePrefetcher -c ../test (或者TaggedPrefetcher)

跑固定指令数量
build/X86/gem5.opt configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache -c ../test -I 100000

跑SPEC20006 429
build/X86/gem5.opt configs/example/se.py --cpu-type=DerivO3CPU --caches --l2cache -c ../SPEC2006/429/mcf_base.gcc41-64bit -o ../SPEC2006/429/inp.in

/opt/speccpu/benchspec/CPU2006
编译
runspec --config=gcc41.cfg --action=build --tune=base 程序名字/程序代号
runspec --config=gcc41.cfg --action=run --tune=base --output_format pdf -noreportable bzip

用--fake --loose查看脚本过程