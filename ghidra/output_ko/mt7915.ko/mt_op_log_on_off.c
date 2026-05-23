// module: mt7915.ko
// function: mt_op_log_on_off @ 0x2574b0
// size: 188 bytes
//

undefined4
mt_op_log_on_off(undefined4 param_1,undefined4 *param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0x503;
  }
  if (param_4 != 0) {
    if (param_4 != 1) {
      printk("%s log type %d not supported\n","mt_op_log_on_off");
      return 0x500;
    }
    *(undefined1 *)((int)param_2 + 5) = 1;
    param_2[3] = param_5;
    if (param_2[5] == 0) {
      sys_ad_zero_mem(param_2,0x18);
      iVar1 = sys_ad_alloc_mem(param_2 + 5,param_5 * 0x1c);
      if (iVar1 == 0) {
        sys_ad_zero_mem(param_2[5],param_5 * 0x1c);
        *param_2 = 0;
        return 0;
      }
      printk("%s: allocated memory fail! size %u\n","mt_op_log_on_off",param_5);
      return 0x500;
    }
  }
  return 0;
}

