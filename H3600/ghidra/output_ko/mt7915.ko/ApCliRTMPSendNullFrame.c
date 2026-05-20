// module: mt7915.ko
// function: ApCliRTMPSendNullFrame @ 0x12901c
// size: 392 bytes
//

void ApCliRTMPSendNullFrame(int param_1,undefined4 param_2,int param_3,int param_4,byte param_5)

{
  short sVar1;
  ushort uVar2;
  undefined1 uVar3;
  ushort uVar4;
  undefined4 uVar5;
  int iVar6;
  bool bVar7;
  byte local_58;
  byte local_57;
  short local_56;
  undefined4 local_54;
  undefined2 local_50;
  undefined4 local_4e;
  undefined2 local_4a;
  undefined4 local_48;
  undefined2 local_44;
  ushort local_42;
  undefined1 local_40;
  undefined1 local_3f;
  
  if (param_4 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): pMacEntry is null!","ApCliRTMPSendNullFrame");
    }
  }
  else {
    iVar6 = *(int *)(param_4 + 8);
    GetStaCfgByWdev(param_1,iVar6);
    if ((*(char *)(iVar6 + 0x888) != '\x02') &&
       (*(char *)(param_1 + (uint)*(ushort *)(param_4 + 0xe0) * 0x620 + 0x2f762) != '\x02')) {
      __memzero(&local_58,0x30);
      local_54 = *(undefined4 *)(param_4 + 0xec);
      local_4e = *(undefined4 *)(iVar6 + 0x1b);
      local_50 = *(undefined2 *)(param_4 + 0xf0);
      local_4a = *(undefined2 *)(iVar6 + 0x1f);
      local_58 = local_58 & 3 | 0x48;
      if (*(char *)(param_1 + 0x794cc6) == '\0') {
        local_57 = local_57 & 0xef | 1 | (param_5 & 1) << 4;
      }
      else {
        local_57 = local_57 | 0x11;
      }
      sVar1 = *(short *)(param_1 + 0x794c4a);
      local_48 = local_54;
      local_44 = local_50;
      local_56 = RTMPCalcDuration(param_1,param_2,0xe);
      bVar7 = param_3 != 0;
      uVar2 = *(ushort *)(param_1 + 0xa39f90);
      uVar4 = uVar2 + 1;
      uVar3 = (undefined1)uVar4;
      *(ushort *)(param_1 + 0xa39f90) = uVar4 & 0xfff;
      if (bVar7) {
        uVar3 = 0;
        uVar5 = 0x1a;
      }
      else {
        uVar5 = 0x18;
      }
      local_56 = local_56 + sVar1;
      if (bVar7) {
        local_40 = uVar3;
      }
      local_42 = local_42 & 0xf | uVar2 << 4;
      if (bVar7) {
        local_58 = local_58 & 0xf | 0xc0;
        local_3f = uVar3;
      }
      hif_kickout_nullframe_tx(param_1,0,&local_58,uVar5);
    }
  }
  return;
}

