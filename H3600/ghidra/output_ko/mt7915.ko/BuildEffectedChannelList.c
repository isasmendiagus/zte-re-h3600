// module: mt7915.ko
// function: BuildEffectedChannelList @ 0x103454
// size: 180 bytes
//

void BuildEffectedChannelList(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined1 auStack_1b [11];
  
  uVar2 = HcGetBandByWdev(param_2);
  pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  iVar4 = GetStaCfgByWdev(param_1,param_2);
  if (iVar4 != 0) {
    RTMPZeroMemory(auStack_1b,0xb);
    bVar1 = pbVar3[0x49c];
    if (bVar1 != 0) {
      pbVar5 = pbVar3;
      do {
        pbVar6 = pbVar5 + 0x14;
        if (*pbVar5 < 0xf) {
          pbVar5[1] = 1;
        }
        pbVar5 = pbVar6;
      } while (pbVar6 != pbVar3 + ((byte)(bVar1 - 1) + 1) * 0x14);
    }
    return;
  }
  printk(&_LC27,0x501);
  dump_stack();
  return;
}

