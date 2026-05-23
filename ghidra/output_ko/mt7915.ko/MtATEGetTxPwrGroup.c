// module: mt7915.ko
// function: MtATEGetTxPwrGroup @ 0x28b0b8
// size: 64 bytes
//

undefined4 MtATEGetTxPwrGroup(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = MtATECh2Freq();
  if (((uint)txpwr_group_map._0_4_ < uVar1) && (uVar1 <= (uint)txpwr_group_map._4_4_)) {
    return *(undefined4 *)(txpwr_group_map + param_3 * 4 + 8);
  }
  return 0;
}

