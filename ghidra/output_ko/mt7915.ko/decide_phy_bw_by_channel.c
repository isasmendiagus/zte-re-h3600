// module: mt7915.ko
// function: decide_phy_bw_by_channel @ 0x14e20c
// size: 148 bytes
//

uint decide_phy_bw_by_channel(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_2 < 0xf) {
    uVar6 = 1;
  }
  else {
    uVar6 = 2;
  }
  piVar4 = (int *)(param_1 + 8);
  uVar5 = 0;
  do {
    while( true ) {
      piVar4 = piVar4 + 1;
      iVar3 = *piVar4;
      if (((iVar3 == 0) || (iVar1 = wlan_operate_get_state(iVar3), iVar1 == 0)) ||
         (uVar2 = wmode_2_rfic(*(undefined2 *)(iVar3 + 0x18)), (uVar2 & uVar6) == 0)) break;
      uVar2 = wlan_operate_get_bw(iVar3);
      if (uVar2 < uVar5) {
        uVar2 = uVar5;
      }
      uVar5 = uVar2 & 0xff;
      if (piVar4 == (int *)(param_1 + 0x1a8)) goto LAB_0014e284;
    }
  } while (piVar4 != (int *)(param_1 + 0x1a8));
LAB_0014e284:
  if (1 < uVar5 && param_2 < 0xf) {
    uVar5 = 1;
  }
  return uVar5;
}

