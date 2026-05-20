// module: mt7915.ko
// function: Set_DfsRDDRegionShow_Proc @ 0x230a68
// size: 80 bytes
//

undefined4 Set_DfsRDDRegionShow_Proc(int param_1,undefined4 param_2)

{
  os_str_tol(param_2,0,10);
  if (0 < DebugLevel) {
    printk("RDD Region is %d\n",*(undefined1 *)(param_1 + 0x795075));
  }
  return 1;
}

