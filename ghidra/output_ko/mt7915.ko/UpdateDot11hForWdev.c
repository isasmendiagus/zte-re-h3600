// module: mt7915.ko
// function: UpdateDot11hForWdev @ 0x101538
// size: 176 bytes
//

void UpdateDot11hForWdev(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_3 == 0) {
    if (2 < DebugLevel) {
      printk("%s(): Detach wdev=%d_Dot11_H!\n","UpdateDot11hForWdev",*(undefined1 *)(param_2 + 0xc))
      ;
    }
    *(undefined4 *)(param_2 + 0x3fe4) = 0;
    *(undefined1 *)(param_2 + 0x944) = 0;
    *(undefined1 *)(param_2 + 0x29) = 0xff;
    return;
  }
  if (param_2 != 0) {
    iVar1 = HcGetBandByWdev(param_2);
    *(int *)(param_2 + 0x3fe4) = param_1 + iVar1 * 0x20 + 0xa37724;
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s(): no wdev!\n","UpdateDot11hForWdev",param_3,param_4);
  return;
}

