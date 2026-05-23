// module: tm.ko
// function: sbrg_get_igsdrp_mirror_en @ 0x1b3c0
// size: 152 bytes
//

undefined4 sbrg_get_igsdrp_mirror_en(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x3e,local_14,0,&sbragRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_igsdrp_mirror_en]output:drop_mir_en = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sbrg_get_igsdrp_mirror_en] reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

