// module: mt7915.ko
// function: BackgroundScanTimeout @ 0x22dff8
// size: 116 bytes
//

void BackgroundScanTimeout(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_2 + 0xa79754);
  if (2 < DebugLevel) {
    printk("%s ===> ScanTypeInfo=%d\n","BackgroundScanTimeout",uVar1);
  }
  MlmeEnqueue(param_2,0x2b,1,0,0,uVar1);
  RtmpOsMlmeUp(param_2 + 0x286298);
  return;
}

