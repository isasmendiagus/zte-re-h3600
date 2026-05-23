// module: mt7915.ko
// function: rtmp_ate_init @ 0x26c6c0
// size: 72 bytes
//

void rtmp_ate_init(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = ATEInit();
  if (iVar1 == 0) {
    return;
  }
  if (-1 < DebugLevel) {
    printk("%s: ATE initialization failed !\n","rtmp_ate_init");
  }
  MtTestModeExit(param_1);
  return;
}

