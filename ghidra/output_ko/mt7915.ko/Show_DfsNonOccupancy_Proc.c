// module: mt7915.ko
// function: Show_DfsNonOccupancy_Proc @ 0x230ab8
// size: 256 bytes
//

undefined4 Show_DfsNonOccupancy_Proc(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  if (0 < DebugLevel) {
    printk("[%s]:\n","Show_DfsNonOccupancy_Proc");
  }
  iVar4 = 0;
  while( true ) {
    iVar1 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar4);
    if (0 < DebugLevel) {
      printk("band_idx: %d\n",iVar4);
    }
    uVar2 = (uint)*(byte *)(iVar1 + 0x49c);
    if (uVar2 != 0) {
      uVar3 = 0;
      do {
        if (0 < DebugLevel) {
          iVar5 = iVar1 + uVar3 * 0x14;
          printk("DfsChannelList[%d].Channel = %d, NonOccupancy = %d, NOPClrCnt = %d, NOPSetByBw = %d, NOPSaveForClear is %d, SupportBwBitMap is %d\n"
                 ,uVar3,*(undefined1 *)(iVar1 + uVar3 * 0x14),*(undefined2 *)(iVar5 + 0xc),
                 *(undefined1 *)(iVar5 + 7),*(undefined1 *)(iVar5 + 9),*(undefined2 *)(iVar5 + 10),
                 *(undefined1 *)(iVar5 + 8));
          uVar2 = (uint)*(byte *)(iVar1 + 0x49c);
        }
        uVar3 = uVar3 + 1 & 0xff;
      } while (uVar3 < uVar2);
    }
    if (iVar4 == 1) break;
    iVar4 = 1;
  }
  return 1;
}

