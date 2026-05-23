// module: mt7915.ko
// function: Show_NOP_Of_ChList @ 0x237834
// size: 256 bytes
//

undefined4 Show_NOP_Of_ChList(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 uStack_10c;
  byte local_10b [243];
  
  os_zero_mem(&uStack_10c,0xf4);
  DfsProvideNopOfChList(param_1,&uStack_10c);
  if (0 < DebugLevel) {
    printk("[%s]\n","Show_NOP_Of_ChList");
  }
  iVar3 = 0;
  while( true ) {
    if (0 < DebugLevel) {
      printk("band_idx: %d\n",iVar3);
    }
    if (local_10b[iVar3] != 0) {
      uVar2 = 0;
      do {
        if (0 < DebugLevel) {
          iVar1 = (iVar3 * 0x1e + uVar2) * 4;
          printk("NopReportChList[%d].Channel = %d, Bw = %d, NOP = %d\n",uVar2,local_10b[iVar1 + 3],
                 local_10b[iVar1 + 4],*(undefined2 *)(local_10b + iVar1 + 5));
        }
        uVar2 = uVar2 + 1 & 0xff;
      } while (uVar2 < local_10b[iVar3]);
    }
    if (iVar3 == 1) break;
    iVar3 = 1;
  }
  return 1;
}

