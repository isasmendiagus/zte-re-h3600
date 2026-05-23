// module: plat-zxylzb_9128S.ko
// function: module_proc_open @ 0x106f4
// size: 20 bytes
//

void module_proc_open(undefined4 param_1,undefined4 param_2)

{
  single_open(param_2,shellReadProc,0);
  return;
}

