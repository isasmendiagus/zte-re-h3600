// module: mt7915.ko
// function: UpdateChannelInfo @ 0x1f6ec
// size: 660 bytes
//

void UpdateChannelInfo(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  ulonglong uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_2c [2];
  
  iVar3 = HcGetBandByWdev(param_4);
  local_2c[0] = 0;
  piVar4 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,iVar3);
  if (*piVar4 == 0) {
    if (-1 < DebugLevel) {
      printk("pAutoChCtrl->pChannelInfo equal NULL.\n");
    }
  }
  else {
    iVar5 = AsicGetCCACnt(param_1,iVar3);
    *(int *)(param_1 + 0xa39e10) = iVar5 + *(int *)(param_1 + 0xa39e10);
    *(int *)(*piVar4 + (param_2 + 0x78) * 4) = iVar5;
    iVar6 = iVar3 * 0xaf5d8 + param_1;
    iVar5 = AsicGetChBusyCnt(param_1,iVar3,local_2c,*(undefined4 *)(*piVar4 + 0x50c));
    if (*(char *)(iVar6 + (uint)*(byte *)(iVar6 + 0x8292c4) + 0x8292bf) != '\0') {
      ktime_get(&local_38);
      *(undefined4 *)(iVar6 + 0x8292e0) = local_38;
      *(undefined4 *)(iVar6 + 0x8292e4) = uStack_34;
    }
    iVar6 = DebugLevel;
    iVar7 = param_1 + param_2 * 4;
    *(uint *)(*piVar4 + param_2 * 4 + 0x32c) = (uint)(iVar5 * 100) / 400;
    *(undefined4 *)(*piVar4 + param_2 * 4 + 0x41c) = local_2c[0];
    *(int *)(iVar7 + 0x286094) = iVar5;
    if (2 < iVar6) {
      printk("[%s] channel busy time[%d] = %d\n","UpdateChannelInfo",param_2);
    }
    iVar5 = DebugLevel;
    param_1 = iVar3 * 0xaf5d8 + param_1;
    if (*(char *)(param_1 + (uint)*(byte *)(param_1 + 0x8292c4) + 0x8292bf) != '\0') {
      uVar8 = *(int *)(param_1 + 0x8292e4) -
              (*(int *)(param_1 + 0x8292dc) +
              (uint)(*(uint *)(param_1 + 0x8292e0) < *(uint *)(param_1 + 0x8292d8)));
      uVar1 = (int)uVar8 >> 0x1f;
      uVar9 = uVar1 ^ *(uint *)(param_1 + 0x8292e0) - *(uint *)(param_1 + 0x8292d8);
      uVar10 = uVar9 - uVar1;
      uVar8 = (uVar1 ^ uVar8) - (uVar1 + (uVar9 < uVar1));
      uVar2 = (ulonglong)uVar10 * 0x431bde82 + ((ulonglong)uVar10 * 0xd7b634db >> 0x20);
      uVar8 = -uVar1 + (uVar8 * 0x431bde82 +
                        (int)((ulonglong)uVar8 * 0xd7b634db + (uVar2 & 0xffffffff) >> 0x20) +
                        (int)(uVar2 >> 0x20) >> 0x12 ^ uVar1) + 1;
      *(char *)(param_1 + 0x8292e8) = (char)uVar8;
      if (2 < iVar5) {
        printk("time_diff: %d Busytime: %d\n",uVar8 & 0xff,*(undefined4 *)(iVar7 + 0x286094),
               iVar7 + 0x284000,-uVar1,0);
      }
    }
  }
  return;
}

