// module: mt7915.ko
// function: ecc_calculate_test @ 0x1d7484
// size: 96 bytes
//

undefined4 ecc_calculate_test(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  if (0x13 < uVar1) {
    uVar1 = 0;
  }
  asic_calculate_ecc(param_1,0,0x13,group19_priv_pettern + uVar1 * 0x20,group19_generator_x,
                     group19_generator_y);
  return 1;
}

