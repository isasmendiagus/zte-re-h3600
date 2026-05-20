// module: mt7915.ko
// function: fill_starec_he @ 0x205c30
// size: 504 bytes
//

void fill_starec_he(undefined4 param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  
  iVar3 = wlan_config_get_ppdu_caps();
  uVar4 = wlan_config_get_asic_caps(param_1);
  uVar5 = wlan_config_get_phy_caps(param_1);
  __memzero(param_3 + 0x9c,0x30);
  bVar6 = *(byte *)(iVar3 + 0x18);
  if (*(byte *)(param_2 + 0x1c) <= *(byte *)(iVar3 + 0x18)) {
    bVar6 = *(byte *)(param_2 + 0x1c);
  }
  *(byte *)(param_3 + 0xa1) = bVar6;
  uVar7 = *(uint *)(param_2 + 0x78);
  if (((uVar7 & 0x400000) != 0) && (*(char *)(iVar3 + 0x10) != '\0')) {
    *(undefined1 *)(param_3 + 0xa0) = 1;
    uVar7 = *(uint *)(param_2 + 0x78);
  }
  if ((uVar7 & 1) != 0) {
    *(undefined1 *)(param_3 + 0x9c) = 1;
    uVar7 = *(uint *)(param_2 + 0x78);
  }
  if ((uVar7 & 0x40000) != 0) {
    *(undefined1 *)(param_3 + 0x9d) = 1;
    uVar7 = *(uint *)(param_2 + 0x78);
  }
  if ((uVar7 & 0x20) != 0) {
    *(undefined1 *)(param_3 + 0x9e) = 1;
    uVar7 = *(uint *)(param_2 + 0x78);
  }
  if ((uVar7 & 0x800) != 0) {
    *(undefined1 *)(param_3 + 0x9f) = 1;
  }
  *(undefined1 *)(param_3 + 0xa2) = *(undefined1 *)(param_2 + 0x9b);
  if (((*(uint *)(param_2 + 0x7c) & 1) != 0) && ((uVar4 & 0x20) != 0)) {
    *(undefined1 *)(param_3 + 0xa3) = 1;
  }
  *(undefined1 *)(param_3 + 0xa4) = *(undefined1 *)(param_2 + 0x2b);
  if ((uVar5 & 0x1000) != 0) {
    *(undefined1 *)(param_3 + 0xa5) = *(undefined1 *)(param_2 + 0x2c);
  }
  *(undefined1 *)(param_3 + 0xa6) = *(undefined1 *)(param_2 + 0x9d);
  if ((*(uint *)(param_2 + 0x7c) & 2) != 0) {
    *(undefined1 *)(param_3 + 0xa7) = 1;
  }
  iVar3 = wlan_config_get_he_ldpc(param_1);
  uVar4 = (uint)(*(int *)(param_2 + 0x7c) << 0x1d) >> 0x1f;
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  if (uVar4 != 0) {
    *(undefined1 *)(param_3 + 0xa8) = 1;
  }
  cVar1 = wlan_config_get_he_tx_stbc(param_1);
  cVar2 = wlan_config_get_he_rx_stbc(param_1);
  if (cVar2 != '\0' || cVar1 != '\0') {
    *(char *)(param_3 + 0xa9) = (char)*(undefined4 *)(param_2 + 0x24);
  }
  *(char *)(param_3 + 0xaa) = (char)*(undefined4 *)(param_2 + 0x80);
  if ((*(uint *)(param_2 + 0x7c) & 0x80) != 0) {
    *(undefined1 *)(param_3 + 0xac) = 1;
  }
  *(undefined1 *)(param_3 + 0xab) = *(undefined1 *)(param_2 + 0x9f);
  if ((*(uint *)(param_2 + 0x7c) & 0x100) != 0) {
    *(undefined1 *)(param_3 + 0xae) = 1;
  }
  *(undefined1 *)(param_3 + 0xad) = *(undefined1 *)(param_2 + 0xa0);
  *(undefined1 *)(param_3 + 0xaf) = *(undefined1 *)(param_2 + 0xa1);
  uVar4 = *(uint *)(param_2 + 0x7c);
  if ((uVar4 & 0x100000) != 0) {
    *(undefined1 *)(param_3 + 0xb0) = 1;
    uVar4 = *(uint *)(param_2 + 0x7c);
  }
  if ((uVar4 & 0x200000) != 0) {
    *(undefined1 *)(param_3 + 0xb1) = 1;
    uVar4 = *(uint *)(param_2 + 0x7c);
  }
  if ((uVar4 & 0x400) != 0) {
    *(undefined1 *)(param_3 + 0xb2) = 1;
    uVar4 = *(uint *)(param_2 + 0x7c);
  }
  if ((uVar4 & 0x800) != 0) {
    *(undefined1 *)(param_3 + 0xb3) = 1;
  }
  os_move_mem((void *)(param_3 + 0xb4),(void *)(param_2 + 0x39),8);
  os_move_mem((void *)(param_3 + 0xc4),(void *)(param_2 + 0x49),8);
  os_move_mem((void *)(param_3 + 0xbc),(void *)(param_2 + 0x59),8);
  return;
}

