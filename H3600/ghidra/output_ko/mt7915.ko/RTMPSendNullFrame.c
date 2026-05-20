// module: mt7915.ko
// function: RTMPSendNullFrame @ 0x1292d4
// size: 376 bytes
//

void RTMPSendNullFrame(int param_1,int param_2,undefined4 param_3,int param_4,byte param_5)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  bool bVar6;
  byte local_50;
  byte local_4f;
  undefined2 local_4e;
  ushort local_3a;
  undefined1 local_38;
  undefined1 local_37;
  
  if (((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) &&
     ((*(int *)(param_1 + 0xa77bb4) != 1 ||
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
    if (param_2 == 0) {
      printk(&_LC13,0x290);
      dump_stack();
    }
    else {
      iVar5 = *(int *)(param_2 + 8);
      GetStaCfgByWdev(param_1,iVar5);
      if ((*(char *)(iVar5 + 0x888) != '\x02') &&
         (*(char *)(param_1 + (uint)*(ushort *)(param_2 + 0xe0) * 0x620 + 0x2f762) != '\x02')) {
        __memzero(&local_50,0x30);
        ComposeNullFrame(param_1,&local_50,param_2 + 0xec,iVar5 + 0x1b,param_2 + 0xec);
        uVar1 = *(ushort *)(param_1 + 0x794c4a);
        if (*(char *)(param_1 + 0x794cc6) == '\0') {
          local_4f = local_4f & 0xef | (param_5 & 1) << 4;
        }
        else {
          local_4f = local_4f | 0x10;
        }
        iVar5 = RTMPCalcDuration(param_1,param_3,0xe);
        bVar6 = param_4 != 0;
        sVar2 = *(short *)(param_1 + 0xa39f90);
        *(ushort *)(param_1 + 0xa39f90) = sVar2 + 1U & 0xfff;
        if (bVar6) {
          uVar4 = 0x1a;
        }
        else {
          uVar4 = 0x18;
        }
        uVar3 = iVar5 + (uint)uVar1;
        local_4e = (undefined2)uVar3;
        if (bVar6) {
          uVar3 = 0xc;
        }
        local_3a = local_3a & 0xf | sVar2 << 4;
        if (bVar6) {
          local_50 = local_50 & 0xf | (byte)((uVar3 & 0xf) << 4);
          local_38 = 0;
          local_37 = local_38;
        }
        hif_kickout_nullframe_tx(param_1,0,&local_50,uVar4);
      }
    }
  }
  return;
}

