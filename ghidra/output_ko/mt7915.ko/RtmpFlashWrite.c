// module: mt7915.ko
// function: RtmpFlashWrite @ 0x25f1dc
// size: 184 bytes
//

void RtmpFlashWrite(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar2 = EEPROMValChange + 4;
  iVar1 = param_2;
  pcVar3 = pcVar2;
  do {
    while ((*pcVar3 == '\0' || (pcVar3[1] != '\x01'))) {
      pcVar3 = pcVar3 + 8;
      if (pcVar3 == (char *)&DAT_005f662c) goto LAB_0025f248;
    }
    iVar1 = *(int *)(pcVar3 + -4);
    pcVar4 = pcVar3 + 8;
    if (*(char *)(param_2 + iVar1) == pcVar3[3]) {
      *(char *)(param_2 + iVar1) = pcVar3[2];
      pcVar3[1] = '\x02';
    }
    pcVar3 = pcVar4;
  } while (pcVar4 != (char *)&DAT_005f662c);
LAB_0025f248:
  ra_mtd_write_nm(param_2,iVar1,param_3,0,param_4);
  do {
    if ((*pcVar2 != '\0') && (pcVar2[1] == '\x02')) {
      *(char *)(param_2 + *(int *)(pcVar2 + -4)) = pcVar2[3];
      pcVar2[1] = '\x01';
    }
    pcVar2 = pcVar2 + 8;
  } while (pcVar2 != (char *)&DAT_005f662c);
  return;
}

