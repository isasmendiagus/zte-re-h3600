// module: mt7915.ko
// function: get_rate_he @ 0xe5220
// size: 92 bytes
//

void get_rate_he(uint param_1,uint param_2,uint param_3,int param_4,uint *param_5)

{
  int iVar1;
  uint uVar2;
  
  if (3 < param_3) {
    param_3 = 4;
  }
  if (2 < param_2) {
    param_2 = 3;
  }
  iVar1 = param_2 * 0x30 + (param_3 - 1 & 0xff) * 0xc;
  if (param_1 < 0xc) {
    iVar1 = iVar1 + param_1;
  }
  else {
    iVar1 = iVar1 + 0xb;
  }
  uVar2 = (uint)*(ushort *)(he_mcs_phyrate_mapping_table + iVar1 * 2);
  if (uVar2 != 0 && param_4 != 0) {
    uVar2 = (uint)(*(ushort *)(he_mcs_phyrate_mapping_table + iVar1 * 2) >> 1);
  }
  *param_5 = uVar2;
  return;
}

