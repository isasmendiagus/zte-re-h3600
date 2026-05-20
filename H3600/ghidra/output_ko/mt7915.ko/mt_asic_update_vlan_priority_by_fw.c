// module: mt7915.ko
// function: mt_asic_update_vlan_priority_by_fw @ 0x19a02c
// size: 140 bytes
//

undefined4
mt_asic_update_vlan_priority_by_fw(int param_1,undefined4 param_2,uint param_3,int param_4)

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
    local_1c[0] = local_1c[0] & 0xffff1fff | param_4 << 0xd;
  }
  else {
    local_1c[0] = local_1c[0] & 0x1fffffff | param_4 << 0x1d;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,local_1c[0]);
  return 0;
}

