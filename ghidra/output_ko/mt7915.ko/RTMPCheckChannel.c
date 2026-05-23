// module: mt7915.ko
// function: RTMPCheckChannel @ 0x12f558
// size: 248 bytes
//

bool RTMPCheckChannel(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  byte *pbVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  
  uVar2 = HcGetBandByWdev(param_4);
  iVar3 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  if (param_2 < param_3) {
    if (param_2 < 3) {
      return false;
    }
    param_3 = param_2 - 2 & 0xff;
    uVar5 = param_3;
  }
  else if (param_2 == param_3) {
    uVar5 = 0;
    param_3 = uVar5;
  }
  else {
    uVar5 = param_2 + 2 & 0xff;
  }
  if (*(char *)(iVar3 + 0x49c) == '\0') {
    cVar4 = '\0';
    bVar7 = false;
  }
  else {
    iVar6 = 0;
    cVar4 = '\0';
    do {
      pbVar1 = (byte *)(iVar3 + iVar6);
      iVar6 = iVar6 + 0x14;
      if (*pbVar1 == uVar5) {
        cVar4 = cVar4 + '\x01';
      }
      if (param_3 == *pbVar1) {
        cVar4 = cVar4 + '\x01';
      }
    } while (iVar6 != ((byte)(*(char *)(iVar3 + 0x49c) - 1) + 1) * 0x14);
    bVar7 = cVar4 == '\x02';
  }
  if (2 < DebugLevel) {
    printk("Total Channel in Channel List = [%d]\n",cVar4);
  }
  return bVar7;
}

