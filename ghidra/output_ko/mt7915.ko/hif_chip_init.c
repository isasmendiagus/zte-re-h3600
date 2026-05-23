// module: mt7915.ko
// function: hif_chip_init @ 0x1df6ec
// size: 36 bytes
//

void hif_chip_init(undefined4 param_1,short param_2)

{
  if (param_2 == 0x7916) {
    mt7916_hif_init();
    return;
  }
  if (param_2 != 0x7915) {
    return;
  }
  mt7915_hif_ctrl_chip_init();
  return;
}

