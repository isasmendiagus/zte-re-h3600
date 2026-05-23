// module: mt7915.ko
// function: hqa_write_bulk_eeprom_v1 @ 0x24ad90
// size: 140 bytes
//

undefined4 hqa_write_bulk_eeprom_v1(int param_1,int param_2)

{
  undefined4 uVar1;
  ushort local_18;
  ushort local_16;
  int local_14 [2];
  
  local_14[0] = param_2 + 0xc;
  local_18 = 0;
  local_16 = 0;
  FUN_002474f4(1,2,local_14,&local_18);
  FUN_002474f4(1,2,local_14,&local_16);
  *(uint *)(param_1 + 0x1f24) = (uint)local_18;
  *(uint *)(param_1 + 0x1f28) = (uint)local_16;
  uVar1 = FUN_00247154(param_1,param_2 + 0x10);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

