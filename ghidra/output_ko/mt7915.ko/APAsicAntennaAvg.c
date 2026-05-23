// module: mt7915.ko
// function: APAsicAntennaAvg @ 0x17b48
// size: 96 bytes
//

void APAsicAntennaAvg(int param_1,int param_2,short *param_3)

{
  char *pcVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar3 = param_1 + param_2 * 4;
  iVar5 = *(int *)((int)&DAT_00296e9c + iVar3);
  uVar4 = *(undefined4 *)("get_channel_by_reference" + iVar3 + 4);
  if (iVar5 != 0) {
    *(undefined4 *)((int)&DAT_00296e9c + param_1) = 0;
    *(undefined4 *)((int)&DAT_00296ea0 + param_1) = 0;
    *(undefined4 *)((int)&DAT_00296ea4 + param_1) = 0;
    pcVar1 = "get_channel_by_reference" + param_1;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = "get_channel_by_reference" + param_1 + 4;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = "get_channel_by_reference" + param_1 + 8;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    sVar2 = __aeabi_uidiv(iVar5,uVar4);
    *param_3 = sVar2 + -0x100;
    return;
  }
  *param_3 = 0;
  return;
}

