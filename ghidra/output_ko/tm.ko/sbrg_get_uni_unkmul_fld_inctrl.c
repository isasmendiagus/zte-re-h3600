// module: tm.ko
// function: sbrg_get_uni_unkmul_fld_inctrl @ 0x2109c
// size: 252 bytes
//

undefined4 sbrg_get_uni_unkmul_fld_inctrl(uint param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_1c [2];
  
  uVar1 = param_3;
  if (param_3 < 8) {
    uVar1 = param_1;
  }
  local_1c[0] = 0;
  if (uVar1 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_uni_unkmul_fld_inctrl]input:port_id = %d,pt_cfg = %d\n",param_1);
    }
    iVar3 = tmOnuRegRead(0x30,local_1c,param_1,&sbragRegTable);
    if (iVar3 == 0) {
      *param_2 = local_1c[0] >> (param_3 & 0xff) & 1;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_get_uni_unkmul_fld_inctrl]output:ctrl = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_uni_unkmul_fld_inctrl] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sbrg_get_uni_unkmul_fld_inctrl]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

