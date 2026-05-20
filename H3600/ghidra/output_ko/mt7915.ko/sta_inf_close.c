// module: mt7915.ko
// function: sta_inf_close @ 0x68c08
// size: 200 bytes
//

undefined4 sta_inf_close(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = *(byte *)(param_1 + 0xe);
  iVar2 = *(int *)(param_1 + 8);
  (&DAT_00580ee8)[iVar2 + (uint)bVar1 * 0x2137b0] = 0;
  if (*(char *)(param_1 + 0x3f58) == '\x01') {
    MWDSDisable(iVar2,*(undefined1 *)(param_1 + 0xe),0,1,param_4);
  }
  MSTAStop(iVar2,param_1);
  (&DAT_00580f3b)[iVar2 + (uint)bVar1 * 0x2137b0] = 0;
  iVar2 = wifi_sys_close(param_1);
  if (iVar2 == 1) {
    return 1;
  }
  if (DebugLevel < 3) {
    return 0;
  }
  printk("%s() close fail!!!\n","sta_inf_close");
  return 0;
}

