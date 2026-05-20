// module: mt7915.ko
// function: Set_VhtDisallowNonVHT_Proc @ 0xdfb68
// size: 104 bytes
//

undefined4 Set_VhtDisallowNonVHT_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x79596c) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x79596c) = 1;
  }
  if (2 < DebugLevel) {
    printk("Set_VhtDisallowNonVHT_Proc::(bNonVhtDisallow=%d)\n",*(undefined1 *)(param_1 + 0x79596c))
    ;
  }
  return 1;
}

