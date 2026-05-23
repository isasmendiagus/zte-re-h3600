// module: mt7915.ko
// function: RtmpDrvAllRFPrint @ 0x244ab4
// size: 192 bytes
//

void RtmpDrvAllRFPrint(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uStack_18;
  
  uVar1 = (uint)&uStack_18 & 0xffffe000;
  uVar2 = *(undefined4 *)(uVar1 + 8);
  *(undefined4 *)(uVar1 + 8) = 0;
  uStack_18 = param_4;
  uVar1 = filp_open("RFDump.txt",0x41,0);
  if (uVar1 < 0xfffff001) {
    if (*(int *)(uVar1 + 0x14) != 0) {
      *(undefined4 *)(uVar1 + 0x40) = 0;
      *(undefined4 *)(uVar1 + 0x44) = 0;
      __vfs_write(uVar1,param_2,param_3);
    }
    filp_close(uVar1,0);
  }
  else if (2 < DebugLevel) {
    printk("-->2) %s: Error %ld opening %s\n","RtmpDrvAllRFPrint",-uVar1,"RFDump.txt");
  }
  *(undefined4 *)(((uint)&uStack_18 & 0xffffe000) + 8) = uVar2;
  return;
}

