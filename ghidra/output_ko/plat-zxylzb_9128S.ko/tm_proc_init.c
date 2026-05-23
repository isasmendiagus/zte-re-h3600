// module: plat-zxylzb_9128S.ko
// function: tm_proc_init @ 0x105e8
// size: 72 bytes
//

undefined4 tm_proc_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  tm_proc_root = proc_mkdir(&_LC5,0,param_3,param_4,param_4);
  if (tm_proc_root != 0) {
    create_shell_proc();
    return 0;
  }
  printk("proc_mkdir tm failed");
  return 0xffffffff;
}

