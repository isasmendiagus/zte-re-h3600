// module: tm.ko
// function: spa_set_pt_802x_trap_en @ 0x38c8c
// size: 248 bytes
//

int spa_set_pt_802x_trap_en(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  uint local_14;
  
  uVar2 = param_1 - 1;
  bVar4 = param_2 != 0;
  bVar3 = param_2 == 1;
  if (param_2 < 2) {
    bVar4 = 5 < uVar2;
    bVar3 = uVar2 == 6;
  }
  local_14 = 0;
  if (!bVar4 || bVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_set_pt_802x_trap_en]input:port_id = %d,trap_en = %d\n",param_1,param_2);
    }
    tmOnuRegRead(9,&local_14,0,&spaRegTable);
    iVar1 = tmOnuRegWrite(9,local_14 & ~(1 << (uVar2 & 0xff)) | param_2 << (uVar2 & 0xff),0,
                          &spaRegTable);
    if ((iVar1 == 0) || (g_tm_debug_level == 0)) {
      return iVar1;
    }
    printk("[TM][spa_set_pt_802x_trap_en]write reg failed!\n");
  }
  else if (g_tm_debug_level == 0) {
    iVar1 = 1;
  }
  else {
    printk("[TM][spa_set_pt_802x_trap_en]input invalid parameter!\n");
    iVar1 = 1;
  }
  return iVar1;
}

