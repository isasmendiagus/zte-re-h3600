// module: tm.ko
// function: tm_cla_cpu_queueid_set @ 0x53d78
// size: 128 bytes
//

undefined4 tm_cla_cpu_queueid_set(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = 6 < param_2;
  if (param_2 < 8) {
    bVar2 = 0x1ff < param_1;
  }
  if (bVar2) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3ec8,param_4,param_4);
    printk("tm_cla_cpu_queueid_set: invalid parameter set!\n");
  }
  iVar1 = cla_set_cpu_queue_id(param_1,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  printk("ERROR:(%s:%d)","tm_api.c",0x3ecd);
  printk("cla_set_cpu_queue_id fail\n");
  return 0xffffffff;
}

