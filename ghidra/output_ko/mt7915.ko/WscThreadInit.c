// module: mt7915.ko
// function: WscThreadInit @ 0x1eccbc
// size: 292 bytes
//

int WscThreadInit(int param_1)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk("-->WscThreadInit()\n");
  }
  iVar1 = param_1 + 0x794ae8;
  RtmpOSTaskInit(iVar1,"RtmpWscTask",param_1,param_1 + 0xa78454,param_1 + 0xa78478);
  iVar1 = RtmpOSTaskAttach(iVar1,wsc_write_dat_file_thread,iVar1);
  if (iVar1 == 0) {
    os_alloc_mem(0,param_1 + 0xa77c3c,0x800);
    if ((*(int *)(param_1 + 0xa77c3c) == 0) && (-1 < DebugLevel)) {
      printk("Wsc HmacData memory alloc failed!\n");
    }
    *(undefined4 *)(param_1 + 0x794b1c) = 0;
    os_alloc_mem(0,param_1 + 0x794b20,0x930);
  }
  if (2 < DebugLevel) {
    printk("<--WscThreadInit(), status=%d!\n",iVar1);
  }
  return iVar1;
}

