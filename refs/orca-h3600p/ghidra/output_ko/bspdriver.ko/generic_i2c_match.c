// module: bspdriver.ko
// function: generic_i2c_match @ 0x1029c
// size: 52 bytes
//

bool generic_i2c_match(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = i2c_verify_client();
  if (iVar1 != 0) {
    return *(ushort *)(iVar1 + 2) != 0xfffe && param_2 == *(ushort *)(iVar1 + 2);
  }
  return false;
}

