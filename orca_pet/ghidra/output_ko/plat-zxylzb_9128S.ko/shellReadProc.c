// module: plat-zxylzb_9128S.ko
// function: shellReadProc @ 0x10708
// size: 20 bytes
//

void shellReadProc(undefined4 param_1)

{
  seq_printf(param_1,&_LC0,
             "Usage: echo [OPTIONS] > /proc/tm/shell \nexample -f sym p1,p2,p3 \n        sym=1, set sym to 1 \n        sym, get sym value \nOptions:\n  -b,         data is byte\n  -w,         data is word , 2 bytes\n  -l,         data is dword , 4 bytes\n  -f,         data is function with check\n  -F,         data is function ,no check\n  -c,         data counts\n  -a,         get sym address\n  -s,         translate address to sym name\n  -d,         data base is dec, default is hex\n  -p,         pid, dec mode\n  -P,         pid\'s full path\n  -t,         vaddr to paddr\n  -h,         help\n"
            );
  return;
}

