// module: mt7915.ko
// function: wdev_search_by_wcid @ 0x14e160
// size: 108 bytes
//

undefined4 wdev_search_by_wcid(int param_1,int param_2)

{
  if (param_1 + param_2 * 0x620 + 0x2f6a0 != 0) {
    return *(undefined4 *)(param_1 + param_2 * 0x620 + 0x2f6a4);
  }
  if (DebugLevel < 2) {
    return 0;
  }
  printk("%s: can not a valid wdev by wcid (%u)\n","wdev_search_by_wcid",param_2);
  return 0;
}

