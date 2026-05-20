// module: mt7915.ko
// function: RTMPConstructCCMPNonce @ 0xb6fa4
// size: 140 bytes
//

void RTMPConstructCCMPNonce
               (int param_1,int param_2,int param_3,int param_4,int param_5,byte *param_6,
               undefined4 *param_7)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (param_2 != 0 && param_3 != 0) {
    *param_6 = *(byte *)(param_1 + 0x1e) & 0xf;
  }
  if (param_2 == 0 && param_3 != 0) {
    *param_6 = *(byte *)(param_1 + 0x18) & 0xf;
  }
  if (param_4 != 0) {
    *param_6 = *param_6 | 0x10;
  }
  memmove(param_6 + 1,(void *)(param_1 + 10),6);
  pbVar1 = (byte *)(param_5 + 6);
  pbVar2 = param_6 + 6;
  do {
    pbVar1 = pbVar1 + -1;
    pbVar2 = pbVar2 + 1;
    *pbVar2 = *pbVar1;
  } while (pbVar2 != param_6 + 0xc);
  *param_7 = 0xd;
  return;
}

