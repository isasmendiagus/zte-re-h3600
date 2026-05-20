// module: mt7915.ko
// function: Show_RAInfo_Proc @ 0x27974
// size: 248 bytes
//

undefined4 Show_RAInfo_Proc(int param_1)

{
  if (DebugLevel < 1) {
    return 1;
  }
  printk("ITxBfEn: %d\n",((uint)*(byte *)(param_1 + 0x794ccd) << 0x1d) >> 0x1f);
  if (0 < DebugLevel) {
    printk("ITxBfTimeout: %ld\n",*(undefined4 *)(param_1 + 0x795994));
    if (DebugLevel < 1) {
      return 1;
    }
    printk("ETxBfTimeout: %ld\n",*(undefined4 *)(param_1 + 0x795998));
    if (DebugLevel < 1) {
      return 1;
    }
    printk("CommonCfg.ETxBfEnCond: %ld\n",*(undefined4 *)(param_1 + 0x79599c));
    if (DebugLevel < 1) {
      return 1;
    }
    printk("ETxBfNoncompress: %d\n",*(undefined1 *)(param_1 + 0x7959a4));
  }
  if ((0 < DebugLevel) &&
     (printk("ETxBfIncapable: %d\n",*(undefined1 *)(param_1 + 0x7959a5)), 0 < DebugLevel)) {
    printk("ucAutoSoundingCtrl: %d\n",*(undefined1 *)(param_1 + 0x7959a6));
  }
  return 1;
}

