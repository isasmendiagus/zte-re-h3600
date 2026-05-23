// module: mt7915.ko
// function: RTMPCalculateMICValue @ 0x11775c
// size: 480 bytes
//

void RTMPCalculateMICValue
               (int param_1,int param_2,undefined1 *param_3,undefined4 param_4,undefined4 param_5,
               byte param_6)

{
  undefined1 uVar1;
  int iVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined1 *puVar5;
  
  pbVar3 = *(byte **)(param_2 + 0xcc);
  iVar2 = *(int *)(param_2 + 100);
  uVar1 = *(undefined1 *)(param_2 + 0x2a);
  uVar9 = (uint)param_6;
  if ((uint)pbVar3[0xd] + (uint)pbVar3[0xc] * 0x100 == 0x8100) {
    iVar7 = 0x12;
    iVar6 = 4;
  }
  else {
    iVar7 = 0xe;
    iVar6 = 0;
  }
  if (((uVar9 < 0x30) || (1 < (int)(uVar9 - 0x30))) || (*(char *)(param_1 + 0x286285) != '\x01')) {
    if (((*(ushort *)(param_2 + 0x42) == 0) || ((*pbVar3 & 1) == 0)) ||
       (*(char *)(param_1 + 0x286285) != '\x01')) {
      if ((uVar9 == 0) || (*(char *)(param_1 + 0x286285) != '\0')) {
        RTMPInitMICEngine(param_1,param_4,pbVar3,pbVar3 + 6,uVar1,param_5);
      }
      else {
        RTMPInitMICEngine(param_1,param_4,pbVar3,param_1 + 0x794b5b,uVar1,param_5);
      }
    }
    else {
      RTMPInitMICEngine(param_1,param_4,
                        (uint)*(ushort *)(param_2 + 0x42) * 0x14c0 + param_1 + 0xa1e0c,pbVar3 + 6,
                        uVar1,param_5);
    }
  }
  else {
    RTMPInitMICEngine(param_1,param_4,pbVar3,&DAT_0036db73 + param_1 + (uVar9 - 0x30) * 0x2137b0,
                      uVar1,param_5);
  }
  if (param_3 != (undefined1 *)0x0) {
    iVar8 = param_1 + 0xa39f14;
    puVar5 = param_3;
    do {
      puVar4 = puVar5 + 1;
      RTMPTkipAppendByte(iVar8,*puVar5);
      puVar5 = puVar4;
    } while (puVar4 != param_3 + 6);
    RTMPTkipAppendByte(iVar8,pbVar3[iVar6 + 0xc]);
    RTMPTkipAppendByte(iVar8,pbVar3[iVar6 + 0xd]);
  }
  iVar6 = (iVar2 + -0xe) - iVar6;
  if (iVar6 != 0) {
    pbVar3 = pbVar3 + iVar7;
    do {
      RTMPTkipAppendByte(param_1 + 0xa39f14,*pbVar3);
      iVar6 = iVar6 + -1;
      pbVar3 = pbVar3 + 1;
    } while (iVar6 != 0);
  }
  RTMPTkipGetMIC(param_1 + 0xa39f14);
  return;
}

