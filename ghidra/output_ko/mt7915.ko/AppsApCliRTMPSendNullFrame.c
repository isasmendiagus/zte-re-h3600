// module: mt7915.ko
// function: AppsApCliRTMPSendNullFrame @ 0x128ea0
// size: 380 bytes
//

void AppsApCliRTMPSendNullFrame
               (int param_1,undefined4 param_2,int param_3,int param_4,ushort param_5)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  undefined1 uVar4;
  ushort uVar5;
  undefined4 uVar6;
  bool bVar7;
  byte local_50;
  byte local_4f;
  short local_4e;
  undefined4 local_4c;
  undefined2 local_48;
  undefined4 local_46;
  undefined2 local_42;
  undefined4 local_40;
  undefined2 local_3c;
  ushort local_3a;
  undefined1 local_38;
  undefined1 local_37;
  
  iVar3 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_4 + 8));
  if ((iVar3 == 0) ||
     ((*(char *)(iVar3 + 0x888) != '\x02' &&
      (*(char *)(param_1 + (uint)*(ushort *)(param_4 + 0xe0) * 0x620 + 0x2f762) != '\x02')))) {
    __memzero(&local_50,0x30);
    local_4c = *(undefined4 *)(param_4 + 0xec);
    local_46 = *(undefined4 *)(iVar3 + 0x1b);
    local_48 = *(undefined2 *)(param_4 + 0xf0);
    local_42 = *(undefined2 *)(iVar3 + 0x1f);
    local_50 = local_50 & 3 | 0x48;
    if (*(char *)(param_1 + 0x794cc6) == '\0') {
      local_4f = local_4f & 0xef | 1 | (byte)((param_5 & 1) << 4);
    }
    else {
      local_4f = local_4f | 0x11;
    }
    if (*(char *)(iVar3 + 0x4061) == '\x01') {
      local_4f = local_4f | 0x10;
    }
    else {
      local_4f = local_4f & 0xef | (byte)((param_5 & 1) << 4);
    }
    sVar1 = *(short *)(param_1 + 0x794c4a);
    local_40 = local_4c;
    local_3c = local_48;
    local_4e = RTMPCalcDuration(param_1,param_2,0xe);
    bVar7 = param_3 != 0;
    uVar2 = *(ushort *)(param_1 + 0xa39f90);
    uVar5 = uVar2 + 1;
    uVar4 = (undefined1)uVar5;
    *(ushort *)(param_1 + 0xa39f90) = uVar5 & 0xfff;
    if (bVar7) {
      uVar4 = 0;
      uVar6 = 0x1a;
    }
    else {
      uVar6 = 0x18;
    }
    local_4e = local_4e + sVar1;
    if (bVar7) {
      local_38 = uVar4;
    }
    local_3a = local_3a & 0xf | uVar2 << 4;
    if (bVar7) {
      local_50 = local_50 & 0xf | 0xc0;
      local_37 = uVar4;
    }
    hif_kickout_nullframe_tx(param_1,0,&local_50,uVar6);
  }
  return;
}

