// module: mt7915.ko
// function: cfgmode_2_wmode @ 0xb8104
// size: 84 bytes
//

undefined2 cfgmode_2_wmode(uint param_1)

{
  int iVar1;
  
  if (0 < DebugLevel) {
    printk("cfg_mode=%d\n",param_1);
  }
  if (param_1 < 0x16) {
    iVar1 = param_1 * 2 + 1;
  }
  else {
    iVar1 = 0x2d;
  }
  return (&DAT_002942d0)[iVar1];
}

