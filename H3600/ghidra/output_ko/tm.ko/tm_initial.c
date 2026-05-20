// module: tm.ko
// function: tm_initial @ 0x542d4
// size: 268 bytes
//

uint tm_initial(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined1 auStack_6c [84];
  undefined4 local_18;
  undefined4 local_14;
  
  iVar3 = 0;
  do {
    uVar1 = smac_get_cfg(iVar3,auStack_6c);
    local_14 = 0;
    local_18 = 0;
    uVar2 = smac_set_cfg(iVar3,auStack_6c);
    iVar3 = iVar3 + 1;
    uVar2 = uVar2 | uVar1;
    if (uVar2 != 0) {
      printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x423);
      return uVar2;
    }
  } while (iVar3 != 5);
  g_tm_init_flag = uVar2;
  uVar1 = tm_pon_tm_initial();
  if (uVar1 == 0) {
    uVar1 = tm_pon_pp_initial();
    if (uVar1 == 0) {
      uVar1 = tm_pon_npp_initial();
      if (uVar1 == 0) {
        g_tm_init_flag = 1;
      }
      else {
        printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x432);
      }
    }
    else {
      printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x42f);
    }
  }
  else {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x42c);
  }
  return uVar1;
}

