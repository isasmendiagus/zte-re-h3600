// module: mt7915.ko
// function: BCNPeerCurrentState @ 0x223354
// size: 160 bytes
//

undefined1 BCNPeerCurrentState(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  uVar1 = *(undefined1 *)(param_2 + 1);
  if (2 < DebugLevel) {
    printk("%s, MeasureReqToken=%d!\n","BCNPeerCurrentState",uVar1);
  }
  iVar2 = MeasureReqLookUp(param_1,uVar1);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("%s, CurrentState=%d!\n","BCNPeerCurrentState",*(undefined1 *)(iVar2 + 0xe));
    }
    return *(undefined1 *)(iVar2 + 0xe);
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s, invalid MeasureReqToken!\n","BCNPeerCurrentState");
  return 0;
}

