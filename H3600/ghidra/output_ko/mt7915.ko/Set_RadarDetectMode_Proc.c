// module: mt7915.ko
// function: Set_RadarDetectMode_Proc @ 0x234cf4
// size: 236 bytes
//

undefined4 Set_RadarDetectMode_Proc(int param_1,undefined4 param_2)

{
  byte bVar1;
  
  bVar1 = os_str_tol(param_2,0,10);
  if (bVar1 < 3) {
    if (0 < DebugLevel) {
      printk("In Set_RadarDetectMode_Proc, mode: %d\n",bVar1);
    }
    mtRddControl(param_1,2,0,0,bVar1);
  }
  else if (-1 < DebugLevel) {
    printk("In Set_RadarDetectMode_Proc, invalid mode: %d\n",bVar1);
  }
  if (bVar1 == 0) {
    *(undefined1 *)(param_1 + 0x7953ee) = 0;
    return 1;
  }
  if (bVar1 < 3) {
    *(undefined1 *)(param_1 + 0x7953ee) = 1;
    return 1;
  }
  *(undefined1 *)(param_1 + 0x7953ee) = 0;
  return 1;
}

