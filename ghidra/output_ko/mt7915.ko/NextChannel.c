// module: mt7915.ko
// function: NextChannel @ 0x1030a4
// size: 156 bytes
//

uint NextChannel(int param_1,char *param_2,uint param_3,undefined4 param_4)

{
  bool bVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  
  uVar2 = HcGetBandByWdev(param_4);
  pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  if (0 < (int)(pbVar3[0x49c] - 1)) {
    iVar4 = 1;
    pbVar5 = pbVar3;
    do {
      if (*pbVar5 == param_3) {
        if (*param_2 != '\x04') {
          return (uint)pbVar3[iVar4 * 0x14];
        }
        param_3 = (uint)pbVar5[0x14];
        if (param_3 < 0xf) {
          return param_3;
        }
      }
      pbVar5 = pbVar5 + 0x14;
      bVar1 = iVar4 < (int)(pbVar3[0x49c] - 1);
      iVar4 = iVar4 + 1;
    } while (bVar1);
  }
  return 0;
}

