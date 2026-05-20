// module: tm.ko
// function: sbrg_get_pt_macaddr_clr @ 0x17b40
// size: 200 bytes
//

undefined4 sbrg_get_pt_macaddr_clr(uint *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  byte local_20 [4];
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  iVar1 = tmOnuRegRead(2,local_20,0,&sbragRegTable);
  iVar2 = tmOnuRegRead(3,local_1c,0,&sbragRegTable);
  if (iVar2 == 0 && iVar1 == 0) {
    *param_1 = (uint)local_20[0];
    *param_2 = local_1c[0];
    uVar3 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_pt_macaddr_clr]output:port_mask = 0x%x,en = %d\n",*param_1);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    printk("[TM][sbrg_get_pt_macaddr_clr] reg read failed\n");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

