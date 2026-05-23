// module: mt7915.ko
// function: rtmp_read_country_region_from_eeporm @ 0x126904
// size: 88 bytes
//

undefined4 rtmp_read_country_region_from_eeporm(int param_1)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  
  uVar1 = (uint)(*(ushort *)("Set_IRR_ADC" + param_1 + 6) >> 8);
  uVar2 = *(ushort *)("Set_IRR_ADC" + param_1 + 6) & 0xff;
  bVar4 = 6 < uVar1;
  bVar3 = uVar1 == 7;
  if (7 < uVar1) {
    bVar4 = 1 < uVar1 - 0x1f;
    bVar3 = uVar1 - 0x1f == 2;
  }
  if (!bVar4 || bVar3) {
    *(byte *)(param_1 + 0x794c44) = ~((byte)~(byte)((uVar1 << 0x19) >> 0x18) >> 1);
  }
  if (uVar2 < 0x26) {
    *(byte *)(param_1 + 0x794c45) = ~((byte)~(byte)((uVar2 << 0x19) >> 0x18) >> 1);
  }
  return 1;
}

