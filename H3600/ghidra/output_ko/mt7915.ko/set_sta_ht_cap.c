// module: mt7915.ko
// function: set_sta_ht_cap @ 0x137c94
// size: 428 bytes
//

void set_sta_ht_cap(int param_1,int param_2,byte *param_3)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x4000000;
  iVar2 = wlan_config_get_ht_gi(*(undefined4 *)(param_2 + 8));
  uVar4 = (uint)*param_3;
  if (iVar2 == 1) {
    if ((*param_3 & 0x20) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x10;
      uVar4 = (uint)*param_3;
    }
    if ((uVar4 & 0x40) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x20;
      uVar4 = (uint)*param_3;
    }
  }
  if (uVar4 >> 7 != 0) {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x40;
  }
  if ((param_3[1] & 3) != 0) {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x80;
  }
  bVar3 = param_3[0x14];
  if ((bVar3 & 4) != 0) {
    *(uint *)(param_2 + 0xb8) = *(uint *)(param_2 + 0xb8) | 0x100;
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x100;
    bVar3 = param_3[0x14];
  }
  if ((*(char *)(param_1 + 0x79507d) != '\0') && ((bVar3 & 8) != 0)) {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x200;
    bVar3 = param_3[0x14];
  }
  if ((bVar3 & 3) == 3) {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x400;
  }
  iVar2 = wlan_config_get_ht_ldpc(*(undefined4 *)(param_2 + 8));
  if (((iVar2 != 0) && ((*(uint *)(iVar1 + 0x2c) & 0x40) != 0)) && ((*param_3 & 1) != 0)) {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x1000000;
  }
  iVar1 = wlan_config_get_ba_enable(*(undefined4 *)(param_2 + 8));
  iVar2 = wlan_config_get_amsdu_en(*(undefined4 *)(param_2 + 8));
  if (iVar1 == 0 && iVar2 != 0) {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 8;
  }
  *(byte *)(param_2 + 0xd04) = (byte)(((uint)param_3[2] << 0x1b) >> 0x1d);
  *(byte *)(param_2 + 0xd05) = (byte)(((uint)param_3[2] << 0x1e) >> 0x1e);
  *(byte *)(param_2 + 0xd10) = (byte)(((uint)*param_3 << 0x1c) >> 0x1e);
  bVar3 = param_3[1];
  *(byte *)(param_2 + 0xd06) = (byte)(((uint)bVar3 << 0x1c) >> 0x1f);
  uVar4 = (uint)*(ushort *)((int)&ht_max_mpdu_size + ((int)((uint)bVar3 << 0x1c) >> 0x1f) * -2);
  *(uint *)(param_2 + 0xd08) = uVar4;
  *(uint *)(param_2 + 0xd0c) = uVar4;
  return;
}

