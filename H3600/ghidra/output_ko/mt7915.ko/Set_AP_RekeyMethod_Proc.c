// module: mt7915.ko
// function: Set_AP_RekeyMethod_Proc @ 0x280c4
// size: 240 bytes
//

undefined4 Set_AP_RekeyMethod_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (*(byte *)((int)param_1 + 0x2b7242) <= uVar2) {
    return 0;
  }
  iVar1 = rtstrcasecmp(param_2,&_LC46);
  if (iVar1 == 1) {
    param_1[uVar2 * 0x160d + 0xadd39] = 1;
  }
  else {
    iVar1 = rtstrcasecmp(param_2,&_LC47);
    if (iVar1 == 1) {
      param_1[uVar2 * 0x160d + 0xadd39] = 2;
    }
  }
  if (DebugLevel < 3) {
    return 1;
  }
  printk("I/F(%s%d) GroupKey ReKeyMethod=%x\n",&_LC49,uVar2,param_1[uVar2 * 0x160d + 0xadd39]);
  return 1;
}

