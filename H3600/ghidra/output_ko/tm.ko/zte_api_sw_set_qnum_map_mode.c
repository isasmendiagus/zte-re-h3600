// module: tm.ko
// function: zte_api_sw_set_qnum_map_mode @ 0x63bd4
// size: 4 bytes
//

undefined4 zte_api_sw_set_qnum_map_mode(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int aiStack_18 [3];
  
  iVar1 = getPort(param_1,aiStack_18);
  if (iVar1 == -1 || aiStack_18[0] == 8) {
    printk("tm_set_qnum_map_mode fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = sbrg_set_qnum_map_mode(aiStack_18[0],param_2);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("ERROR:(%s:%d)","tm_api.c",0x4fc9);
      printk("tm_set_qnum_map_mode fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

