// module: mt7915.ko
// function: TRTableResetEntry @ 0x14832c
// size: 180 bytes
//

void TRTableResetEntry(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  
  iVar4 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_2 || 0x11f < param_2) {
    return;
  }
  iVar2 = param_1 + param_2 * 0x620;
  if (*(int *)(iVar2 + 0x2f6a0) != 0) {
    *(undefined1 *)(iVar2 + 0x2f758) = 0;
    *(undefined1 *)(iVar2 + 0x2f759) = 0;
    pcVar3 = *(code **)(iVar4 + 8);
    if (pcVar3 != (code *)0x0) {
      iVar4 = param_1 + param_2 * 0x620;
      (*pcVar3)(param_1,*(undefined2 *)(iVar4 + 0x2f6a8),pcVar3,iVar4 + 0x2f5c0,param_4);
    }
    *(undefined4 *)(param_1 + param_2 * 0x620 + 0x2f6a0) = 0;
    return;
  }
  return;
}

