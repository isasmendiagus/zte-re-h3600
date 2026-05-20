// module: mt7915.ko
// function: Set_AP_RekeyInterval_Proc @ 0x29998
// size: 196 bytes
//

undefined4
Set_AP_RekeyInterval_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (*(byte *)((int)param_1 + 0x2b7242) <= uVar2) {
    return 0;
  }
  iVar1 = os_str_tol(param_2,0,10,(uint)*(byte *)((int)param_1 + 0x2b7242),param_4);
  if (iVar1 - 10U < 0x3fffff5) {
    param_1[uVar2 * 0x160d + 0xadd3a] = iVar1;
  }
  else {
    param_1[uVar2 * 0x160d + 0xadd3a] = 0xe10;
  }
  if (2 < DebugLevel) {
    printk("I/F(%s%d) GroupKey ReKeyInterval=%ld seconds\n",&_LC49,uVar2,
           param_1[uVar2 * 0x160d + 0xadd3a]);
    return 1;
  }
  return 1;
}

