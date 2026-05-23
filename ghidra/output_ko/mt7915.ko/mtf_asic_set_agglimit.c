// module: mt7915.ko
// function: mtf_asic_set_agglimit @ 0x197178
// size: 172 bytes
//

undefined4 mtf_asic_set_agglimit(int param_1,int param_2,int param_3,int param_4,byte param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint local_14;
  
  if (param_4 != 0) {
    uVar2 = HcGetWmmIdx(param_1,param_4);
    iVar3 = -0x7df0dfb8;
    if (param_2 != 1) {
      iVar3 = -0x7df1dfb8;
    }
    iVar3 = iVar3 + (uVar2 & 0xff) * 4;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar3,&local_14);
    uVar2 = 0xff << (param_3 << 3 & 0xffU);
    uVar1 = (uint)param_5 << (param_3 << 3 & 0xffU);
    if ((uVar2 & local_14) != uVar1) {
      local_14 = local_14 & ~uVar2 | uVar1;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar3);
    }
    return 0;
  }
  return 1;
}

