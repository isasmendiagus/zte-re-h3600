// module: mt7915.ko
// function: halUmacVoWChargeBwToken @ 0x45a4c
// size: 128 bytes
//

undefined4 halUmacVoWChargeBwToken(uint param_1,uint param_2,uint param_3,int param_4)

{
  bool bVar1;
  bool bVar2;
  
  bVar2 = param_2 != 0;
  bVar1 = param_2 == 1;
  if (param_2 < 2) {
    bVar2 = 0xe < param_1;
    bVar1 = param_1 == 0xf;
  }
  if (bVar2 && !bVar1) {
    return 0;
  }
  mac_io_write32(*(undefined4 *)(pvow_pad + 0xa797a0),0x8340,param_3 | param_4 << 0x10);
  mac_io_write32(*(undefined4 *)(pvow_pad + 0xa797a0),0x8388,
                 param_1 & 0xf | 0x80000000 | ((param_2 & 1) << 3 | 0x81) << 0x10);
  return 1;
}

