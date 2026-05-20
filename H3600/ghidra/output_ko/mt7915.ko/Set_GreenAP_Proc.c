// module: mt7915.ko
// function: Set_GreenAP_Proc @ 0xdea4c
// size: 116 bytes
//

undefined4 Set_GreenAP_Proc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = os_str_tol(param_2,0,10);
  if ((iVar1 != 0) && (iVar1 != 1)) {
    return 0;
  }
  greenap_proc(param_1);
  if (DebugLevel < 3) {
    return 1;
  }
  uVar2 = greenap_get_capability(param_1);
  printk("Set_GreenAP_Proc::(greenap_cap=%d)\n",uVar2);
  return 1;
}

