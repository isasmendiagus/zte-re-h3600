// module: mt7915.ko
// function: hqa_rdd_stop @ 0x24a12c
// size: 152 bytes
//

undefined4 hqa_rdd_stop(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = param_2 + 0xc;
  local_18 = 0;
  local_14 = 0;
  FUN_002474f4(1,4,&local_1c,&local_18);
  FUN_002474f4(1,4,&local_1c,&local_14);
  uVar1 = mt_serv_set_rdd_on_off(param_1,local_18,local_14,0);
  printk("%s: rdd_num: %d, rdd_sel: %d\n","hqa_rdd_stop",local_18,local_14);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

