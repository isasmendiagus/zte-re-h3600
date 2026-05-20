// module: mt7915.ko
// function: Set_SecDefaultKeyID_Proc @ 0x113084
// size: 164 bytes
//

undefined4 Set_SecDefaultKeyID_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x40);
  if (iVar2 == 0) {
    if (0 < DebugLevel) {
      printk("%s:: pSecConfig == NULL, arg=%s\n","Set_SecDefaultKeyID_Proc",param_2);
      return 0;
    }
  }
  else {
    iVar1 = os_str_tol(param_2,0,10);
    if (iVar1 - 1U < 4) {
      *(char *)(iVar2 + 0x14c) = (char)(iVar1 - 1U);
      if (DebugLevel < 3) {
        return 1;
      }
      printk("%s ==> DefaultKeyId=%d\n","Set_SecDefaultKeyID_Proc");
      return 1;
    }
  }
  return 0;
}

