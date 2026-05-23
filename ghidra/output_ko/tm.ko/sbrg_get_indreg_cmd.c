// module: tm.ko
// function: sbrg_get_indreg_cmd @ 0x1c770
// size: 216 bytes
//

undefined4 sbrg_get_indreg_cmd(uint *param_1,uint *param_2,uint *param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c;
  
  local_1c = 0;
  iVar1 = tmOnuRegRead(0x13,&local_1c,0,&sbragRegTable);
  if (iVar1 == 0) {
    *param_4 = local_1c & 0xfff;
    *param_3 = (local_1c << 5) >> 0x1b;
    *param_2 = (local_1c << 4) >> 0x1f;
    *param_1 = local_1c >> 0x1f;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_indreg_cmd]output:mode = %d, rw = %d, mem_id = %d, ram_addr = %d\n",
             local_1c >> 0x1f,*param_2,*param_3,*param_4);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sbrg_get_indreg_cmd] reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

