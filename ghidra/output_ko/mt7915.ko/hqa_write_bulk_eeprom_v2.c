// module: mt7915.ko
// function: hqa_write_bulk_eeprom_v2 @ 0x24ad04
// size: 140 bytes
//

undefined4 hqa_write_bulk_eeprom_v2(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_1c = param_2 + 0xc;
  local_18 = 0;
  local_14[0] = 0;
  FUN_002474f4(1,4,&local_1c,&local_18);
  FUN_002474f4(1,4,&local_1c,local_14);
  *(undefined4 *)(param_1 + 0x1f24) = local_18;
  *(undefined4 *)(param_1 + 0x1f28) = local_14[0];
  uVar1 = FUN_00247154(param_1,param_2 + 0x14);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

