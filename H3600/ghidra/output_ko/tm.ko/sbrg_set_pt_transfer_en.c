// module: tm.ko
// function: sbrg_set_pt_transfer_en @ 0x17864
// size: 272 bytes
//

undefined4 sbrg_set_pt_transfer_en(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_14;
  
  bVar4 = param_2 != 0;
  bVar3 = param_2 == 1;
  if (param_2 < 2) {
    bVar4 = 6 < param_1;
    bVar3 = param_1 == 7;
  }
  local_14 = 0;
  if (!bVar4 || bVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_set_pt_transfer_en]input:port_id = %d,en = %d\n",param_1,param_2);
    }
    iVar2 = tmOnuRegRead(1,&local_14,0,&sbragRegTable);
    if (iVar2 == 0) {
      iVar2 = tmOnuRegWrite(1,local_14 & ~(1 << (param_1 & 0xff)) | param_2 << (param_1 & 0xff),0,
                            &sbragRegTable);
      uVar1 = 0;
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_set_pt_transfer_en]write reg failed!\n");
        return 0xffffffff;
      }
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_set_pt_transfer_en] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_set_pt_transfer_en]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

