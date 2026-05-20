// module: mt7915.ko
// function: halUmacVoWChargeBwDrrTime @ 0x45ae4
// size: 40 bytes
//

undefined4 halUmacVoWChargeBwDrrTime(uint param_1,uint param_2,int param_3)

{
  bool bVar1;
  bool bVar2;
  
  bVar2 = param_2 != 0;
  bVar1 = param_2 == 1;
  if (param_2 < 2) {
    bVar2 = 0xe < param_1;
    bVar1 = param_1 == 0xf;
  }
  if (!bVar2 || bVar1) {
    mac_io_write32(*(undefined4 *)(pvow_pad + 0xa797a0),0x8340,param_3 << 0x10);
    mac_io_write32(*(undefined4 *)(pvow_pad + 0xa797a0),0x8388,
                   param_1 & 0xf | 0x80000000 | param_2 << 0x18 | 0x820000);
    return 1;
  }
  return 0;
}

