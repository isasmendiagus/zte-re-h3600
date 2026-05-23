// module: mt7915.ko
// function: NRPeerCurrentState @ 0x221d30
// size: 160 bytes
//

undefined1 NRPeerCurrentState(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  uVar1 = *(undefined1 *)(param_2 + 1);
  if (2 < DebugLevel) {
    printk("%s, MeasureReqToken=%d!\n","NRPeerCurrentState",uVar1);
  }
  iVar2 = MeasureReqLookUp(param_1,uVar1);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("%s, CurrentState=%d!\n","NRPeerCurrentState",*(undefined1 *)(iVar2 + 0xe));
    }
    return *(undefined1 *)(iVar2 + 0xe);
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s, invalid MeasureReqToken!\n","NRPeerCurrentState");
  return 1;
}

