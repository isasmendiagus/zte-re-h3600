// module: mt7915.ko
// function: RRM_PeerMeasureReportSanity @ 0x223974
// size: 164 bytes
//

undefined4
RRM_PeerMeasureReportSanity
          (undefined4 param_1,int param_2,int param_3,undefined1 *param_4,char *param_5,
          undefined4 *param_6)

{
  undefined4 uVar1;
  char *pcVar2;
  
  if (param_5 == (char *)0x0) {
    return 0;
  }
  pcVar2 = (char *)(param_2 + 0x1b);
  *param_4 = *(undefined1 *)(param_2 + 0x1a);
  uVar1 = 0;
  if ((char *)(param_2 + param_3) <= pcVar2 + *(byte *)(param_2 + 0x1c) + 1) {
    return 0;
  }
  do {
    if (*pcVar2 == '\'') {
      uVar1 = 1;
      *param_5 = pcVar2[2];
      param_5[1] = pcVar2[3];
      param_5[2] = pcVar2[4];
      *param_6 = pcVar2 + 5;
    }
    pcVar2 = pcVar2 + (byte)pcVar2[1] + 2;
  } while (pcVar2 + (byte)pcVar2[1] + 1 < (char *)(param_2 + param_3));
  return uVar1;
}

