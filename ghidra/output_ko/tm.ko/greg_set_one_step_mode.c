// module: tm.ko
// function: greg_set_one_step_mode @ 0x32dc4
// size: 252 bytes
//

undefined4 greg_set_one_step_mode(uint param_1,uint param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  if (param_2 < 2) {
    cVar1 = tmOnuRegRead(0x40,local_14,0,&gregRegTable);
    if (cVar1 == '\0') {
      local_14[0] = local_14[0] & ~(1 << (param_1 & 0xff)) | param_2 << (param_1 & 0xff);
      cVar1 = tmOnuRegWrite(0x40,local_14[0],0,&gregRegTable);
      uVar2 = 0;
      if (cVar1 != '\0') {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][greg_set_one_step_mode]write failed\n");
        return 0xffffffff;
      }
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][greg_set_one_step_mode]reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][greg_set_one_step_mode]param error!\n");
    uVar2 = 1;
  }
  return uVar2;
}

