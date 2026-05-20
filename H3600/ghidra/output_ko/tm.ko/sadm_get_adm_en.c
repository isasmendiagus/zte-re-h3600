// module: tm.ko
// function: sadm_get_adm_en @ 0x23228
// size: 176 bytes
//

undefined4 sadm_get_adm_en(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  local_c = 0;
  iVar1 = tmOnuRegRead(0,&local_c,0,sadmRegTable);
  if (iVar1 == 0) {
    if (local_c < 2) {
      *param_1 = local_c;
    }
    if (g_tm_debug_level < 7) {
      uVar2 = 0;
    }
    else {
      printk("[TM][sadm_get_admen]output:en = %d\n",*param_1);
      uVar2 = 0;
    }
  }
  else {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14216,"sadm_get_adm_en"), iVar1 != 0))
    {
      printk("[TM][sadm_get_admen]write reg failed!\n");
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

