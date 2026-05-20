// module: mt7915.ko
// function: Set_TpcEnable_Proc @ 0x14052c
// size: 108 bytes
//

undefined4 Set_TpcEnable_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  cVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if (0 < DebugLevel) {
    printk("%s(): %d -> %d\n","Set_TpcEnable_Proc",*(undefined1 *)(param_1 + 0x79507c),cVar1 != '\0'
          );
  }
  *(bool *)(param_1 + 0x79507c) = cVar1 != '\0';
  return 1;
}

