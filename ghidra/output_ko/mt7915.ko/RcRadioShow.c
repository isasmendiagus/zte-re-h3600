// module: mt7915.ko
// function: RcRadioShow @ 0xac914
// size: 120 bytes
//

void RcRadioShow(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1f78) == '\0') {
    return;
  }
  uVar1 = 0;
  do {
    if (0 < DebugLevel) {
      printk("band\t: %d,rfic: %d, bf_cap: %d\n",uVar1,*(undefined1 *)(param_1 + uVar1 * 0x354),
             *(char *)(param_1 + uVar1 * 0x354 + 0x346) != '\0');
    }
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < *(byte *)(param_1 + 0x1f78));
  return;
}

