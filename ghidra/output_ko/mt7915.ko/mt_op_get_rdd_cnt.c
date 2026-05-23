// module: mt7915.ko
// function: mt_op_get_rdd_cnt @ 0x2589e4
// size: 84 bytes
//

undefined4 mt_op_get_rdd_cnt(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4)

{
  printk(&_LC21,"mt_op_get_rdd_cnt",param_3,param_4,param_4);
  *param_2 = *(undefined4 *)(param_1 + 8);
  *param_3 = *(undefined4 *)(param_1 + 0xc);
  printk("%s: radar pulse number is %d, RDD buffer size is %d\n","mt_op_get_rdd_cnt",
         *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  return 0;
}

