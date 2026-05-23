// module: mt7915.ko
// function: HwCtrlInit @ 0xb23c0
// size: 240 bytes
//

undefined4 HwCtrlInit(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 0x285ca8) = 0;
  _raw_spin_lock_bh(param_1 + 0x285ca8);
  *(undefined4 *)(param_1 + 0x285c9c) = 0;
  *(undefined4 *)(param_1 + 0x285ca4) = 1;
  *(undefined4 *)(param_1 + 0x285ca0) = 0;
  iVar2 = param_1 + 0x285cac;
  *(undefined4 *)(param_1 + 0x285c98) = 0;
  _raw_spin_unlock_bh(param_1 + 0x285ca8);
  *(undefined4 *)(param_1 + 0x285cdc) = 0;
  RtmpOSTaskInit(iVar2,"HwCtrlTask",param_1,param_1 + 0xa78454,param_1 + 0xa78478);
  iVar2 = RtmpOSTaskAttach(iVar2,HwCtrlThread,iVar2);
  if (iVar2 == 1) {
    uVar1 = 1;
    if (-1 < DebugLevel) {
      printk("%s: unable to start %s\n",*(undefined4 *)(param_1 + 4),"HwCtrlInit");
    }
  }
  else {
    ser_init(param_1);
    uVar1 = 0;
  }
  return uVar1;
}

