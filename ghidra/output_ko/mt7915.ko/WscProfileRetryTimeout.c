// module: mt7915.ko
// function: WscProfileRetryTimeout @ 0x1e9a30
// size: 656 bytes
//

void WscProfileRetryTimeout(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  int iVar7;
  byte local_29 [5];
  
  local_29[0] = 0;
  if (param_2 == 0) {
    return;
  }
  iVar7 = *(int *)(param_2 + 0x29e8);
  if (iVar7 == 0) {
    return;
  }
  if (2 < DebugLevel) {
    printk("WscProfileRetryTimeout:: WSC profile retry timeout index: %d\n",
           *(undefined4 *)(param_2 + 0x1c94));
  }
  uVar4 = *(byte *)(param_2 + 0x1c54) & 0xf;
  local_29[0] = (byte)uVar4;
  if (*(char *)(iVar7 + 0x286285) == '\0') {
    if ((*(uint *)(&DAT_0057ffbc + iVar7) & 1) == 0) {
      iVar2 = 2;
    }
    else {
      if (*(int *)(iVar7 + 0x794ae4) == 1) {
        *(undefined1 *)(param_2 + 0x2874) = 0;
        goto LAB_001e9bc0;
      }
      iVar2 = 2;
    }
  }
  else if (*(char *)(iVar7 + 0x286285) == '\x01') {
    iVar2 = GetAssociatedAPByWdev(iVar7,&DAT_0036db58 + iVar7 + uVar4 * 0x2137b0);
    if ((iVar2 == 0) || ((&DAT_0057ff7e)[iVar7 + (uint)local_29[0] * 0x2137b0] == '\0')) {
      iVar2 = 0;
    }
    else {
      piVar5 = (int *)(iVar7 + 0xa1d20);
      pcVar6 = (char *)(iVar7 + 0x2f762);
      bVar1 = true;
      iVar2 = 0;
      while( true ) {
        iVar3 = HcGetMaxStaNum(iVar7);
        if (iVar3 <= iVar2) break;
        if (((*piVar5 == 2) && (piVar5[0x3f] == 2)) && (*pcVar6 == '\x01')) {
          bVar1 = false;
        }
        piVar5 = piVar5 + 0x530;
        pcVar6 = pcVar6 + 0x620;
        iVar2 = iVar2 + 1;
      }
      if (!bVar1) goto LAB_001e9bc0;
      iVar2 = 0;
    }
  }
  else {
    iVar2 = 0xff;
  }
  if (*(uint *)(param_2 + 0x1c94) < *(int *)(param_2 + 0x1c90) - 1U) {
    *(uint *)(param_2 + 0x1c94) = *(uint *)(param_2 + 0x1c94) + 1;
  }
  else {
    *(undefined4 *)(param_2 + 0x1c94) = 0;
  }
  if (iVar2 == 0) {
    WscWriteConfToApCliCfg(iVar7,param_2,param_2 + *(int *)(param_2 + 0x1c94) * 0x74 + 0x1c98,1);
    RTEnqueueInternalCmd(iVar7,7,local_29,1);
  }
  else if (iVar2 == 2) {
    WscWriteConfToPortCfg(iVar7,param_2,param_2 + *(int *)(param_2 + 0x1c94) * 0x74 + 0x1c98,1);
  }
  *(byte *)(iVar7 + 0x794b18) = *(byte *)(param_2 + 0x1c54) & 0xf;
  RtmpOsTaskWakeUp(iVar7 + 0x794ae8);
  if (2 < DebugLevel) {
    printk("WscProfileRetryTimeout:: WSC profile retry index: %d\n",
           *(undefined4 *)(param_2 + 0x1c94));
  }
LAB_001e9bc0:
  (&DAT_00580cca)[iVar7] = 0;
  return;
}

