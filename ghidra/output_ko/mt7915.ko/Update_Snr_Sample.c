// module: mt7915.ko
// function: Update_Snr_Sample @ 0xc8a14
// size: 216 bytes
//

void Update_Snr_Sample(int param_1,char *param_2,int param_3,int param_4)

{
  char cVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  uint uVar11;
  
  sVar3 = *(short *)(param_2 + 8);
  cVar1 = param_2[4];
  cVar2 = *param_2;
  uVar11 = (byte)"SetPartProfileParameters"[param_1 + 0x18] & 0xf;
  if (uVar11 < 4) {
    if (("SetPartProfileParameters"[param_1 + 0x18] & 0xfU) == 0) {
      return;
    }
  }
  else {
    uVar11 = 4;
  }
  pcVar9 = (char *)(param_3 + 3);
  pcVar10 = param_2 + 0x14;
  psVar7 = (short *)(param_2 + 0x18);
  iVar8 = 0;
  do {
    pcVar9 = pcVar9 + 1;
    if (*pcVar9 != '\0' && param_4 != 0) {
      sVar4 = ConvertToSnr(param_1);
      sVar5 = sVar4 << 3;
      pcVar10[-4] = (char)sVar4;
      if ((sVar3 != 0 || cVar1 != '\0') || cVar2 != '\0') {
        sVar5 = (*psVar7 - (short)*pcVar10) + sVar4;
      }
      *psVar7 = sVar5;
      iVar6 = (int)sVar5;
      if (iVar6 < 0) {
        iVar6 = iVar6 + 7;
      }
      *pcVar10 = (char)(iVar6 >> 3);
    }
    iVar8 = iVar8 + 1;
    pcVar10 = pcVar10 + 1;
    psVar7 = psVar7 + 1;
  } while (iVar8 < (int)uVar11);
  return;
}

