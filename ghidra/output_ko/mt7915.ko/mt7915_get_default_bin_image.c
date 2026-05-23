// module: mt7915.ko
// function: mt7915_get_default_bin_image @ 0x17f310
// size: 48 bytes
//

undefined1 * mt7915_get_default_bin_image(void)

{
  if (0 < DebugLevel) {
    printk("Use the default iPAiLNA bin image!\n");
  }
  return MT7915_E2PImage_iPAiLNA;
}

