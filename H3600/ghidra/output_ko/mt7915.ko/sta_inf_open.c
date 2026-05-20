// module: mt7915.ko
// function: sta_inf_open @ 0x694a4
// size: 428 bytes
//

undefined4 sta_inf_open(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = *(int *)(param_1 + 8);
  if ((*(byte *)(iVar3 + 0x286294) & 3) == 3) {
    if (1 < *(byte *)(param_1 + 0xe)) {
      return 0;
    }
    apcli_sync_wdev(iVar3,param_1);
  }
  uVar4 = (uint)*(byte *)(param_1 + 0xe);
  (&DAT_00580f3b)[iVar3 + uVar4 * 0x2137b0] = 0;
  iVar1 = wifi_sys_open(param_1);
  if (iVar1 != 1) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s() open fail!!!\n","sta_inf_open");
    return 0;
  }
  if ((*(byte *)(iVar3 + 0x286294) & 3) == 3) {
    RTMPSetPhyMode(iVar3,param_1,*(undefined2 *)(param_1 + 0x18));
  }
  WscUUIDInit(iVar3,*(undefined1 *)(param_1 + 0xe),1);
  if (*(char *)(param_1 + 0x3f58) == '\x01') {
    MWDSEnable(iVar3,*(undefined1 *)(param_1 + 0xe),0);
  }
  sta_os_completion_initialize(&DAT_0036db58 + iVar3 + uVar4 * 0x2137b0);
  if (0 < DebugLevel) {
    iVar1 = uVar4 * 0x2137b0 + iVar3;
    pcVar2 = "apcli";
    if ((*(byte *)(iVar3 + 0x286294) & 3) != 3) {
      pcVar2 = "ra";
    }
    printk("MSTA interface up for %s%x func_idx=%d OmacIdx=%d\n",pcVar2,
           *(undefined1 *)(param_1 + 0xe),(&DAT_0036db66)[iVar1],(&DAT_0036db81)[iVar1]);
    return 1;
  }
  return 1;
}

