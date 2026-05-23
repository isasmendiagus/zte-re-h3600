// module: tm.ko
// function: sbrg_get_desc_monitor_sel @ 0x183e8
// size: 156 bytes
//

undefined4 sbrg_get_desc_monitor_sel(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(9,local_14,0,&sbragRegTable);
  if (iVar1 == 0) {
    *param_1 = (char)local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_desc_monitor_sel]output:en = %d\n",local_14[0] & 0xff);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sbrg_get_desc_monitor_sel] reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

