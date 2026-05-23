// module: mt7915.ko
// function: Air_Monitor_Pkt_Report_Action @ 0x4019c
// size: 400 bytes
//

void Air_Monitor_Pkt_Report_Action(int param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  byte *pbVar7;
  
  cVar1 = *(char *)(param_3 + 0x80);
  pbVar7 = *(byte **)(param_3 + 0x1c);
  if (cVar1 == '\0') {
    return;
  }
  uVar3 = HcGetBandByChannel(param_1,cVar1,param_3,cVar1,param_4);
  if (1 < uVar3) {
    return;
  }
  uVar3 = (uint)*(byte *)(param_2 * 0x14c0 + param_1 + uVar3 + 0xa1e98);
  iVar5 = param_1 + uVar3 * 0x44;
  if (*(char *)(iVar5 + 0xa37234) == '\0') {
    return;
  }
  uVar4 = ((uint)*pbVar7 << 0x1c) >> 0x1e;
  if (uVar4 == 1) {
    if ((*(byte *)(param_1 + 0xa376a4) & 1) == 0) {
      return;
    }
    uVar4 = 0x7240;
  }
  else {
    if (uVar4 != 2) {
      if (uVar4 != 0) {
        return;
      }
      if ((*(byte *)(param_1 + 0xa376a4) & 2) == 0) {
        return;
      }
      *(int *)(iVar5 + 0xa37240) = *(int *)(iVar5 + 0xa37240) + 1;
      goto LAB_00040254;
    }
    if ((*(byte *)(param_1 + 0xa376a4) & 4) == 0) {
      return;
    }
    uVar4 = 0x7238;
  }
  iVar5 = iVar5 + (uVar4 | 0xa30000);
  *(int *)(iVar5 + 4) = *(int *)(iVar5 + 4) + 1;
LAB_00040254:
  iVar5 = param_1 + uVar3 * 0x44;
  *(int *)(iVar5 + 0xa37238) = *(int *)(iVar5 + 0xa37238) + 1;
  memmove((void *)(iVar5 + 0xa37252),(void *)(param_3 + 0x58),4);
  bVar2 = "SetPartProfileParameters"[param_1 + 0x18];
  if ((bVar2 & 0xf) != 0) {
    uVar4 = 0;
    pcVar6 = (char *)(uVar3 * 0x44 + param_1 + 0xa37251);
    do {
      pcVar6 = pcVar6 + 1;
      uVar4 = uVar4 + 1;
      if ('\0' < *pcVar6) {
        *pcVar6 = -0x7f;
      }
    } while (uVar4 < (bVar2 & 0xf));
    return;
  }
  return;
}

