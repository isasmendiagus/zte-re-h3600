// module: mt7915.ko
// function: Update_Rssi_Sample @ 0xc8aec
// size: 88 bytes
//

void Update_Rssi_Sample(undefined4 param_1,int param_2,int param_3,int param_4,char *param_5)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (param_4 == 0) {
    return;
  }
  pcVar3 = (char *)(param_2 + -1);
  pcVar4 = (char *)(param_3 + -1);
  pcVar6 = param_5;
  do {
    pcVar5 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar3 = pcVar3 + 1;
    *pcVar3 = cVar1;
    pcVar4 = pcVar4 + 1;
    iVar2 = (short)*pcVar4 * 7 + (int)cVar1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 7;
    }
    *pcVar4 = (char)(iVar2 >> 3);
    pcVar6 = pcVar5;
  } while (pcVar5 != param_5 + param_4);
  return;
}

