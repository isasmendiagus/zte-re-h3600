// module: mt7915.ko
// function: ARC4_INIT @ 0x1240f4
// size: 128 bytes
//

void ARC4_INIT(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int extraout_r1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  
  pbVar6 = (byte *)((int)param_1 + 7);
  iVar3 = 0;
  *param_1 = 0;
  param_1[1] = 0;
  pbVar2 = pbVar6;
  do {
    pbVar2 = pbVar2 + 1;
    *pbVar2 = (byte)iVar3;
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x100);
  uVar4 = 0;
  iVar5 = 0;
  iVar3 = 0x100;
  do {
    __aeabi_uidivmod(iVar5,param_3,pbVar2,iVar3,param_4);
    pbVar6 = pbVar6 + 1;
    bVar1 = *pbVar6;
    pbVar2 = (byte *)(uint)bVar1;
    iVar5 = iVar5 + 1;
    uVar4 = (uint)(pbVar2 + uVar4 + *(byte *)(param_2 + extraout_r1)) & 0xff;
    iVar3 = (int)param_1 + uVar4;
    *pbVar6 = *(byte *)(iVar3 + 8);
    *(byte *)(iVar3 + 8) = bVar1;
  } while (iVar5 != 0x100);
  return;
}

