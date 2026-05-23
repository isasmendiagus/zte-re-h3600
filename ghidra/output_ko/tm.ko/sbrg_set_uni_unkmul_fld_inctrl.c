// module: tm.ko
// function: sbrg_set_uni_unkmul_fld_inctrl @ 0x20f70
// size: 300 bytes
//

undefined4 sbrg_set_uni_unkmul_fld_inctrl(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  bool bVar4;
  uint local_1c [2];
  
  bVar4 = 6 < param_3;
  bVar3 = param_3 == 7;
  if (param_3 < 8) {
    bVar4 = param_2 != 0;
    bVar3 = param_2 == 1;
  }
  if (param_1 < 8 && (!bVar4 || bVar3)) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_set_uni_unkmul_fld_inctrl]input:port_id = %d,ctrl = %d,pt_cfg = %d\n",
             param_1,param_2,param_3);
    }
    iVar1 = tmOnuRegRead(0x30,local_1c,param_1,&sbragRegTable);
    if (iVar1 == 0) {
      iVar1 = tmOnuRegWrite(0x30,local_1c[0] & ~(1 << (param_3 & 0xff)) |
                                 param_2 << (param_3 & 0xff),param_1,&sbragRegTable);
      uVar2 = 0;
      if (iVar1 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_set_uni_unkmul_fld_inctrl]write reg failed!\n");
        return 0xffffffff;
      }
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_set_uni_unkmul_fld_inctrl] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sbrg_set_uni_unkmul_fld_inctrl]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

