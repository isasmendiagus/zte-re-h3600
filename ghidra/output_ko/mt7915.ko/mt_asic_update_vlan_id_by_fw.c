// module: mt7915.ko
// function: mt_asic_update_vlan_id_by_fw @ 0x199f98
// size: 148 bytes
//

undefined4 mt_asic_update_vlan_id_by_fw(int param_1,undefined4 param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint local_1c [2];
  
  if (param_3 < 0x10) {
    uVar1 = param_3 >> 1;
    iVar2 = -0x7df32ff0;
  }
  else {
    uVar1 = (int)(param_3 - 0x10) >> 1;
    iVar2 = -0x7df32fe8;
  }
  iVar2 = uVar1 * 4 + iVar2;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,local_1c);
  if ((param_3 & 1) == 0) {
    local_1c[0] = param_4 | local_1c[0] & 0xfffff000;
  }
  else {
    local_1c[0] = local_1c[0] & 0xf000ffff | param_4 << 0x10;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,local_1c[0]);
  return 0;
}

