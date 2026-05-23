// module: mt7915.ko
// function: Set_Wep_Key_Proc @ 0x59e60
// size: 124 bytes
//

undefined4 Set_Wep_Key_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = ParseWebKey(param_1 + *(int *)(*param_1 + 0x3c) * 0x84dec + 0xdb6e1,param_2,param_4,
                      param_3);
  if (2 < DebugLevel) {
    printk("%s:: KeyID=%d, key=%s\n","Set_Wep_Key_Proc",param_4,param_2);
  }
  return uVar1;
}

