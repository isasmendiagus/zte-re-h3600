// module: mt7915.ko
// function: Set_NoForwardingBTNSSID_Proc @ 0x33f54
// size: 116 bytes
//

undefined4 Set_NoForwardingBTNSSID_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if ((iVar2 != 1) && (iVar2 != 0)) {
    return 0;
  }
  *(int *)(&DAT_003678f4 + param_1) = iVar2;
  if (iVar1 < 3) {
    return 1;
  }
  printk("Set_NoForwardingBTNSSID_Proc::(NoForwarding=%ld)\n",
         *(undefined4 *)(&DAT_003678f4 + param_1));
  return 1;
}

