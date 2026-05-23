// module: mt7915.ko
// function: set_vht_cap @ 0x202ad4
// size: 356 bytes
//

void set_vht_cap(int param_1,int param_2,byte *param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x8000000;
  iVar3 = wlan_config_get_vht_ldpc(*(undefined4 *)(param_2 + 8));
  if ((iVar3 == 0) || ((*(uint *)(iVar2 + 0x2c) & 0x40) == 0)) {
    iVar3 = wlan_config_get_vht_sgi(*(undefined4 *)(param_2 + 8));
  }
  else {
    if ((*param_3 & 0x10) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x800000;
    }
    iVar3 = wlan_config_get_vht_sgi(*(undefined4 *)(param_2 + 8));
  }
  if (iVar3 == 1) {
    bVar5 = *param_3;
    if ((bVar5 & 0x20) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x10000;
      bVar5 = *param_3;
    }
    if ((bVar5 & 0x40) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x20000;
    }
  }
  iVar3 = wlan_config_get_vht_stbc(*(undefined4 *)(param_2 + 8));
  if (iVar3 != 0) {
    if ((*param_3 & 0x80) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x40000;
    }
    if ((param_3[1] & 7) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x80000;
    }
  }
  bVar5 = (param_3[3] & 3) << 1 | param_3[2] >> 7;
  if (bVar5 < *(byte *)(param_2 + 0xd05)) {
    bVar5 = *(byte *)(param_2 + 0xd05);
  }
  *(byte *)(param_2 + 0xd05) = bVar5;
  uVar4 = wlan_config_get_vht_max_mpdu_len(*(undefined4 *)(param_2 + 8));
  bVar5 = *(byte *)(iVar2 + 0x60);
  bVar1 = *param_3;
  *(byte *)(param_2 + 0xd06) = (byte)(((uint)bVar1 << 0x1e) >> 0x1e);
  if (bVar5 <= uVar4) {
    uVar4 = (uint)bVar5;
  }
  uVar6 = bVar1 & 3;
  if ((uVar4 & 0xff) < (*param_3 & 3)) {
    *(char *)(param_2 + 0xd06) = (char)uVar4;
    uVar6 = uVar4 & 0xff;
  }
  if (uVar6 < 3) {
    uVar4 = (uint)*(ushort *)((int)&vht_max_mpdu_size + uVar6 * 2);
  }
  else {
    uVar4 = 0;
  }
  *(uint *)(param_2 + 0xd08) = uVar4;
  *(uint *)(param_2 + 0xd0c) = uVar4;
  return;
}

