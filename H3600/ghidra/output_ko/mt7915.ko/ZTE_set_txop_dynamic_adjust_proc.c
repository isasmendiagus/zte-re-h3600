// module: mt7915.ko
// function: ZTE_set_txop_dynamic_adjust_proc @ 0x1592d4
// size: 60 bytes
//

undefined4
ZTE_set_txop_dynamic_adjust_proc
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  cVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  txop_dynamic_adjust_en = (int)cVar1;
  printk("%s set txop_dynamic_adjust_en=%d","ZTE_set_txop_dynamic_adjust_proc");
  return 1;
}

