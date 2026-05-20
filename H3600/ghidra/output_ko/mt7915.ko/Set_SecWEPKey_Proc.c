// module: mt7915.ko
// function: Set_SecWEPKey_Proc @ 0x113974
// size: 156 bytes
//

undefined4 Set_SecWEPKey_Proc(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*(int *)(*param_1 + 0x40) == 0) {
    uVar1 = 0;
    if (0 < DebugLevel) {
      printk("%s:: pSecConfig == NULL, arg=%s\n","Set_SecWEPKey_Proc");
      return 0;
    }
  }
  else {
    uVar1 = ParseWebKey(*(int *)(*param_1 + 0x40),param_3,param_2,0);
    if (2 < DebugLevel) {
      printk("%s::KeyID=%d, key=%s\n","Set_SecWEPKey_Proc",param_2,param_3);
      return uVar1;
    }
  }
  return uVar1;
}

