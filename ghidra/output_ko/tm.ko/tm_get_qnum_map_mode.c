// module: tm.ko
// function: tm_get_qnum_map_mode @ 0x555f8
// size: 136 bytes
//

undefined4 tm_get_qnum_map_mode(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [3];
  
  iVar1 = getPort(param_1,local_18);
  if (iVar1 == -1 || local_18[0] == 8) {
    printk("tm_get_qnum_map_mode fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = sbrg_get_qnum_map_mode(local_18[0],param_2);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("ERROR:(%s:%d)","tm_api.c",0x4fdf);
      printk("tm_get_qnum_map_mode fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

