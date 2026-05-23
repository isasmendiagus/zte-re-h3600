// module: mt7915.ko
// function: CheckNonOccupancyChannel @ 0x100dfc
// size: 200 bytes
//

bool CheckNonOccupancyChannel(int param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  
  uVar2 = HcGetBandByWdev(param_2);
  pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  if (param_3 == 0) {
    param_3 = (uint)*(byte *)(param_2 + 0x1a);
  }
  pbVar1 = pbVar3 + 0x49c;
  if (*pbVar1 != 0) {
    uVar5 = 0;
    do {
      uVar5 = uVar5 + 1;
      if ((*pbVar3 == param_3) &&
         ((*(short *)(pbVar3 + 0xc) != 0 || (*(short *)(pbVar3 + 10) != 0)))) {
        if (-1 < DebugLevel) {
          printk("ERROR: previous detection of a radar on this channel(Channel=%d).\n",param_3);
        }
        iVar4 = DfsStopWifiCheck(param_1,param_2);
        return iVar4 != 0;
      }
      pbVar3 = pbVar3 + 0x14;
    } while (*pbVar1 != uVar5);
  }
  return true;
}

