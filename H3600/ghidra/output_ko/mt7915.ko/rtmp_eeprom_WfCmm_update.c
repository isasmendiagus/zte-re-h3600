// module: mt7915.ko
// function: rtmp_eeprom_WfCmm_update @ 0x12726c
// size: 272 bytes
//

undefined4
rtmp_eeprom_WfCmm_update
          (int param_1,int param_2,uint param_3,int param_4,byte param_5,byte param_6,
          undefined1 *param_7)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  byte local_3e [30];
  
  local_3e[10] = 8;
  local_3e[0xb] = 1;
  local_3e[0xc] = 1;
  local_3e[0xd] = 1;
  local_3e[0xe] = 3;
  local_3e[0xf] = 1;
  local_3e[0x10] = 1;
  local_3e[0x11] = 1;
  local_3e[4] = 0x1c;
  local_3e[5] = 0xe;
  local_3e[6] = 0x52;
  local_3e[7] = 0x12;
  local_3e[8] = 0x5e;
  local_3e[9] = 0x1e;
  local_3e[0x18] = 0x12;
  local_3e[0x19] = 4;
  local_3e[0x1a] = 0x11;
  local_3e[0x1b] = 0x11;
  if ((param_2 == 2) == 0) {
    iVar2 = *(int *)("Show_Rx_Statistic" + param_1 + 8);
  }
  else {
    iVar2 = *(int *)("Set_Rx_Vector_Control" + param_1);
  }
  bVar7 = 3 < param_3;
  bVar6 = param_3 == 4;
  if (param_3 < 5) {
    bVar7 = param_4 != 0;
    bVar6 = param_4 == 1;
  }
  local_3e[0x12] = 1;
  local_3e[0x13] = 1;
  local_3e[0x14] = 2;
  local_3e[0x15] = 2;
  local_3e[0x16] = 0xc;
  local_3e[0x17] = 0xc;
  local_3e[0x1c] = 0xc;
  local_3e[0x1d] = 0xc;
  local_3e[0] = 0;
  local_3e[1] = 0;
  local_3e[2] = 0x10;
  local_3e[3] = 2;
  uVar4 = (uint)param_5;
  uVar5 = (uint)param_6;
  if (((iVar2 == 0 || bVar7 && !bVar6) ||
      (iVar1 = (uint)(param_2 == 2) + param_3 * 2 + -0x20, local_3e[iVar1 + 0x2a] <= uVar4)) ||
     (local_3e[iVar1 + 0x34] <= uVar5)) {
    uVar3 = 1;
  }
  else {
    iVar2 = iVar2 + (uint)local_3e[iVar1 + 0x20];
    if (uVar4 != 0) {
      iVar2 = uVar4 * local_3e[iVar1 + 0x34] + iVar2;
    }
    if (param_4 == 1) {
      *(undefined1 *)(iVar2 + uVar5) = *param_7;
    }
    else {
      *param_7 = *(undefined1 *)(iVar2 + uVar5);
    }
    uVar3 = 0;
  }
  return uVar3;
}

