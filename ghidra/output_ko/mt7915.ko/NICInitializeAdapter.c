// module: mt7915.ko
// function: NICInitializeAdapter @ 0x13a3d8
// size: 92 bytes
//

undefined4 NICInitializeAdapter(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = WfMacInit();
  if (iVar1 == 0) {
    if (0 < DebugLevel) {
      printk("MAC Init Done!\n");
    }
    iVar1 = WfPhyInit(param_1);
    if (iVar1 == 0) {
      uVar2 = NICInitializeAsic(param_1);
      return uVar2;
    }
  }
  return 1;
}

