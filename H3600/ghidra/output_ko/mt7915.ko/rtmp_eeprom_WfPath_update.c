// module: mt7915.ko
// function: rtmp_eeprom_WfPath_update @ 0x127380
// size: 316 bytes
//

undefined4
rtmp_eeprom_WfPath_update
          (int param_1,int param_2,uint param_3,uint param_4,byte param_5,byte param_6,byte param_7,
          undefined1 *param_8)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  byte local_4c [40];
  
  bVar7 = 2 < param_4;
  bVar6 = param_4 == 3;
  if (param_4 < 4) {
    bVar7 = 4 < param_3;
    bVar6 = param_3 == 5;
  }
  local_4c[0] = 0;
  local_4c[1] = 0;
  local_4c[2] = 9;
  local_4c[3] = 1;
  local_4c[4] = 0x21;
  local_4c[5] = 4;
  local_4c[6] = 0x22;
  local_4c[7] = 5;
  local_4c[8] = 0x32;
  local_4c[9] = 8;
  local_4c[10] = 0x4a;
  local_4c[0xb] = 0xe;
  uVar4 = (uint)param_7;
  uVar5 = (uint)param_6;
  local_4c[0xc] = 3;
  local_4c[0xd] = 1;
  local_4c[0xe] = 8;
  local_4c[0xf] = 1;
  local_4c[0x10] = 1;
  local_4c[0x11] = 1;
  local_4c[0x12] = 8;
  local_4c[0x13] = 1;
  local_4c[0x14] = 4;
  local_4c[0x15] = 1;
  local_4c[0x16] = 8;
  local_4c[0x17] = 1;
  local_4c[0x18] = 3;
  local_4c[0x19] = 1;
  local_4c[0x1a] = 3;
  local_4c[0x1b] = 3;
  local_4c[0x1c] = 1;
  local_4c[0x1d] = 1;
  local_4c[0x1e] = 2;
  local_4c[0x1f] = 3;
  local_4c[0x20] = 6;
  local_4c[0x21] = 6;
  local_4c[0x22] = 2;
  local_4c[0x23] = 2;
  if (param_5 < 2 && (!bVar7 || bVar6)) {
    uVar1 = (uint)(param_2 == 2);
    iVar2 = uVar1 + param_3 * 2 + -0x28;
    if ((uVar5 < local_4c[iVar2 + 0x34]) && (uVar4 < local_4c[iVar2 + 0x40])) {
      if (uVar1 == 0) {
        iVar3 = *(int *)(param_1 + (param_4 + 0xa5b48) * 4 + 4);
      }
      else {
        iVar3 = *(int *)(param_1 + (param_4 + 0xa5b40) * 4 + 4);
      }
      if (iVar3 != 0) {
        iVar3 = iVar3 + (uint)local_4c[uVar1 + param_3 * 2];
        if (uVar5 != 0) {
          iVar3 = uVar5 * local_4c[iVar2 + 0x40] + iVar3;
        }
        if (param_5 == 1) {
          *(undefined1 *)(iVar3 + uVar4) = *param_8;
        }
        else {
          *param_8 = *(undefined1 *)(iVar3 + uVar4);
        }
        return 0;
      }
    }
  }
  return 1;
}

