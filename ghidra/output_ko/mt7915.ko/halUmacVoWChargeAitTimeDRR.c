// module: mt7915.ko
// function: halUmacVoWChargeAitTimeDRR @ 0x45b0c
// size: 172 bytes
//

undefined4 halUmacVoWChargeAitTimeDRR(uint param_1,uint param_2,uint param_3,int param_4)

{
  uint uVar1;
  bool bVar2;
  bool bVar3;
  
  uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(pvow_pad + 0xa797a0));
  if (param_1 <= uVar1) {
    bVar3 = param_3 != 0;
    bVar2 = param_3 == 1;
    if (param_3 < 2) {
      bVar3 = 2 < param_2;
      bVar2 = param_2 == 3;
    }
    if (!bVar3 || bVar2) {
      mac_io_write32(*(undefined4 *)(pvow_pad + 0xa797a0),0x8340,param_4 << 0x10);
      mac_io_write32(*(undefined4 *)(pvow_pad + 0xa797a0),0x8388,
                     param_1 & 0xff | 0x80000000 | ((param_3 & 1) << 3 | 0x84) << 0x10 |
                     (param_2 & 0xf) << 8);
      return 1;
    }
  }
  return 0;
}

