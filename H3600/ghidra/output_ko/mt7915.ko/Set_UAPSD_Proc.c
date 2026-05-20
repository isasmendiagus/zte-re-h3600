// module: mt7915.ko
// function: Set_UAPSD_Proc @ 0x2b240
// size: 84 bytes
//

undefined4 Set_UAPSD_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*param_1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
  uVar2 = uVar2 & 0xff;
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + uVar2 * 0x160d + 0xadec8) = 0;
  }
  else {
    *(undefined1 *)(param_1 + uVar2 * 0x160d + 0xadec8) = 1;
  }
  return 1;
}

