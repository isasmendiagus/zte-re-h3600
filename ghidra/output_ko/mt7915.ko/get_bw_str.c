// module: mt7915.ko
// function: get_bw_str @ 0x133600
// size: 32 bytes
//

undefined * get_bw_str(uint param_1)

{
  undefined *puVar1;
  
  if (param_1 < 7) {
    puVar1 = (&PTR_DAT_00299114)[param_1];
  }
  else {
    puVar1 = &_LC22;
  }
  return puVar1;
}

