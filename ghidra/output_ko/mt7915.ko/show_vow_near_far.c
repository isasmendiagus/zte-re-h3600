// module: mt7915.ko
// function: show_vow_near_far @ 0x47624
// size: 208 bytes
//

undefined4 show_vow_near_far(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (-1 < DebugLevel) {
    printk("adjust_en = %d\n",*(undefined1 *)(param_1 + 0xa7a312),param_3,param_1 + 0xa7a000,param_4
          );
    if (-1 < DebugLevel) {
      printk("slow_phy_th = %d\n",*(undefined2 *)(param_1 + 0xa7a314));
      if (-1 < DebugLevel) {
        printk("fast_phy_th = %d\n",*(undefined2 *)(param_1 + 0xa7a316));
        if (-1 < DebugLevel) {
          printk("band(%d) near_far_txop_running = %d\n",0,*(undefined1 *)(param_1 + 0xa7c429),
                 DebugLevel,param_4);
        }
      }
    }
  }
  if (-1 < DebugLevel) {
    printk("band(%d) near_far_txop_running = %d\n",1,*(undefined1 *)(param_1 + 0xa7c439),DebugLevel,
           param_4);
  }
  return 1;
}

