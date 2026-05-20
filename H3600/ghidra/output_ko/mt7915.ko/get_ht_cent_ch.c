// module: mt7915.ko
// function: get_ht_cent_ch @ 0x137b10
// size: 192 bytes
//

bool get_ht_cent_ch(int param_1,undefined1 *param_2,undefined1 *param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  piVar4 = (int *)(param_1 + 8);
  iVar5 = 0;
  do {
    piVar4 = piVar4 + 1;
    iVar3 = *piVar4;
    if (((iVar3 != 0) && (*(byte *)(iVar3 + 0x1a) == param_4)) &&
       (iVar2 = wlan_operate_get_state(iVar3), iVar2 == 0)) {
      iVar2 = wlan_operate_get_ht_bw(iVar3);
      iVar5 = wlan_operate_get_ext_cha(iVar3);
      if (iVar2 == 1) {
        bVar1 = true;
        if (iVar5 == 1) {
          *param_2 = 1;
          *param_3 = 1;
          return true;
        }
        goto LAB_00137ba0;
      }
    }
  } while (piVar4 != (int *)(param_1 + 0x1a8));
  bVar1 = false;
LAB_00137ba0:
  if (param_4 < 3) {
    bVar1 = false;
  }
  if (iVar5 != 3) {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = 1;
    *param_3 = 3;
  }
  return bVar1;
}

