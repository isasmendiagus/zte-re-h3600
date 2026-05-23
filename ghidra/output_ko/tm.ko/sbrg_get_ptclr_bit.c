// module: tm.ko
// function: sbrg_get_ptclr_bit @ 0x20ed8
// size: 152 bytes
//

undefined4 sbrg_get_ptclr_bit(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x1f,local_14,0,&sbragRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_ptclr_bit]output:sta = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sbrg_get_ptclr_bit] reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

