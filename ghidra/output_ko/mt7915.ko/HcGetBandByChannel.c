// module: mt7915.ko
// function: HcGetBandByChannel @ 0xa9d80
// size: 92 bytes
//

undefined4 HcGetBandByChannel(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RcGetHdevByChannel(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 0) {
    uVar2 = RcGetBandIdx();
    return uVar2;
  }
  if (3 < DebugLevel) {
    printk("%s(): no hdev parking on channel:%d!\n","HcGetBandByChannel",param_2);
  }
  return 0;
}

