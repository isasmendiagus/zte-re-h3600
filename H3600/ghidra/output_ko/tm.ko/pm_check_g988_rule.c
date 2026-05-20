// module: tm.ko
// function: pm_check_g988_rule @ 0x3464c
// size: 228 bytes
//

void pm_check_g988_rule(uint param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = *param_2;
  uVar2 = (param_1 << 0xe) >> 0x1d;
  uVar3 = (param_1 << 0xd) >> 0x1f;
  if (iVar1 == 0) {
    if ((param_2[4] != uVar2) || (param_2[3] != uVar3)) goto LAB_00034674;
  }
  else if (iVar1 == 1) {
    if (((param_2[4] != uVar2) || (param_2[3] != uVar3)) || (param_2[6] != (param_1 & 0xfff)))
    goto LAB_00034674;
  }
  else {
    if (iVar1 == 2) {
      if ((param_2[4] != uVar2) || (param_2[3] != uVar3)) goto LAB_00034674;
    }
    else if ((param_2[4] != uVar2) || ((param_2[3] != uVar3 || (param_2[6] != (param_1 & 0xfff)))))
    goto LAB_00034674;
    if (param_2[5] != (param_1 << 0x11) >> 0x1d) goto LAB_00034674;
  }
  if ((param_1 << 0xc) >> 0x1f == (uint)*(byte *)(param_2 + 2)) {
    *param_3 = 1;
    return;
  }
LAB_00034674:
  *param_3 = 0;
  return;
}

