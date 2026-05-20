// module: mt7915.ko
// function: get_phymode_str @ 0xb7e68
// size: 48 bytes
//

undefined * get_phymode_str(uint param_1)

{
  undefined *puVar1;
  
  if (param_1 < 5) {
    return (&PTR__LC6_00294290)[param_1];
  }
  if ((int)param_1 < 5) {
    puVar1 = &_LC63;
  }
  else {
    puVar1 = &_LC25;
  }
  return puVar1;
}

