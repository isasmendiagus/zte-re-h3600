// module: mt7915.ko
// function: Set_SecAuthMode_Proc @ 0x112fc4
// size: 92 bytes
//

undefined4 Set_SecAuthMode_Proc(int *param_1,undefined4 param_2)

{
  if (*(int *)(*param_1 + 0x40) != 0) {
    SetWdevAuthMode(*(int *)(*param_1 + 0x40));
    return 1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("%s:: pSecConfig == NULL, arg=%s\n","Set_SecAuthMode_Proc",param_2);
  return 0;
}

