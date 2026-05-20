// module: mt7915.ko
// function: GetCuntryMaxTxPwr @ 0x141388
// size: 128 bytes
//

char GetCuntryMaxTxPwr(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  
  cVar1 = *(char *)(param_3 + 0x1a);
  uVar2 = HcGetBandByWdev(param_3);
  pcVar3 = (char *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  if ((byte)pcVar3[0x49c] == 0) {
    return '\x1e';
  }
  if (*pcVar3 == cVar1) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    pcVar4 = pcVar3;
    do {
      uVar5 = uVar5 + 1;
      if (uVar5 == (byte)pcVar3[0x49c]) {
        return '\x1e';
      }
      pcVar4 = pcVar4 + 0x14;
    } while (*pcVar4 != cVar1);
  }
  return pcVar3[uVar5 * 0x14 + 4];
}

