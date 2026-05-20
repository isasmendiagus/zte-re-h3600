// module: mt7915.ko
// function: Set_DebugCategory_Proc @ 0xda9b8
// size: 64 bytes
//

undefined4
Set_DebugCategory_Proc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  DebugCategory = os_str_tol(param_2,0,0x10,param_4,param_4);
  printk("%s(): Set DebugCategory = 0x%x\n","Set_DebugCategory_Proc",DebugCategory);
  return 1;
}

