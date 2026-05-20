// module: mt7915.ko
// function: Set_IEEE8021X_Proc @ 0x2afc4
// size: 184 bytes
//

undefined4 Set_IEEE8021X_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (*(byte *)((int)param_1 + 0x2b7242) <= uVar2) {
    return 0;
  }
  iVar1 = os_str_tol(param_2,0,10,(uint)*(byte *)((int)param_1 + 0x2b7242),param_4);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + uVar2 * 0x160d + 0xade02) = 0;
  }
  else {
    *(undefined1 *)(param_1 + uVar2 * 0x160d + 0xade02) = 1;
  }
  if (2 < DebugLevel) {
    printk("I/F(%s%d) IEEE8021X=%d\n",&_LC49,uVar2,(char)param_1[uVar2 * 0x160d + 0xade02]);
    return 1;
  }
  return 1;
}

