// module: mt7915.ko
// function: RtmpDrvPciMapSingle @ 0x1c9154
// size: 156 bytes
//

int RtmpDrvPciMapSingle(int *param_1,int param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  
  if (param_4 == 1) {
    if (*(int *)(param_2 + 0x28) == 0) {
      return 0;
    }
    iVar1 = linux_pci_map_single
                      (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(param_2 + 0x30),
                       *(int *)(param_2 + 0x28),0,param_5);
    *(int *)(param_2 + 0x3c) = iVar1;
  }
  else {
    iVar1 = linux_pci_map_single(*(undefined4 *)(*param_1 + 0xc),param_2,param_3,0,param_5);
  }
  if (iVar1 == -1) {
    if (0 < DebugLevel) {
      printk("%s: dma mapping error,ret=%d\n","RtmpDrvPciMapSingle",1);
    }
    return 0;
  }
  return iVar1;
}

