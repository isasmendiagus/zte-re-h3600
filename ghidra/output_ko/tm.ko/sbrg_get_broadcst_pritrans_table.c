// module: tm.ko
// function: sbrg_get_broadcst_pritrans_table @ 0x1c3e8
// size: 200 bytes
//

undefined4 sbrg_get_broadcst_pritrans_table(uint *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_c;
  
  local_c = 0;
  if (param_2 < 0x30) {
    iVar2 = tmOnuRegRead(0x4b,&local_c,param_2,&sbragRegTable);
    if (iVar2 == 0) {
      *(byte *)((int)param_1 + 9) = (byte)local_c & 7;
      param_1[1] = (uint)(local_c << 0x1c) >> 0x1f;
      *(byte *)(param_1 + 2) = (byte)((uint)(local_c << 0x19) >> 0x1d);
      *param_1 = (uint)(local_c << 0x18) >> 0x1f;
      return 0;
    }
    if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_broadcst_pritrans_table] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_get_broadcst_pritrans_table]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

