// module: tm.ko
// function: tm_cla_cpu_queueid_get @ 0x53df8
// size: 124 bytes
//

undefined4
tm_cla_cpu_queueid_get(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1ff < param_1) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3ee8,param_4,param_4);
    printk("tm_cla_cpu_queueid_get: invalid parameter set!\n");
  }
  iVar1 = cla_get_cpu_queue_id(param_1,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  printk("ERROR:(%s:%d)","tm_api.c",0x3eed);
  printk("cla_get_cpu_queue_id fail\n");
  return 0xffffffff;
}

