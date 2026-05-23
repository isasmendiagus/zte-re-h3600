// module: tm.ko
// function: smct_get_pp_pmau @ 0x37224
// size: 152 bytes
//

undefined4 smct_get_pp_pmau(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,0,&smctRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][smct_get_pp_pmau]output:pamu = %u\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][smct_get_pp_pmau]read reg failed!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

