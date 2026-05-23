// module: mt7915.ko
// function: hqa_rdd_start @ 0x24a1c8
// size: 168 bytes
//

undefined4 hqa_rdd_start(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iStack_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iStack_1c = param_2 + 0xc;
  local_18 = 0;
  local_14 = 0;
  printk(&_LC20,"hqa_rdd_start");
  FUN_002474f4(1,4,&iStack_1c,&local_18);
  FUN_002474f4(1,4,&iStack_1c,&local_14);
  uVar1 = mt_serv_set_rdd_on_off(param_1,local_18,local_14,1);
  printk("%s: rdd_num: %d, rdd_sel: %d\n","hqa_rdd_start",local_18,local_14);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

