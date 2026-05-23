// module: mt7915.ko
// function: sae_derive_k_ecc @ 0x208390
// size: 280 bytes
//

undefined4 sae_derive_k_ecc(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *local_28;
  undefined4 local_24 [2];
  
  uVar3 = *(undefined4 *)(param_1 + 0x5c);
  uVar1 = *(undefined4 *)(param_1 + 0x58);
  uVar2 = *(undefined4 *)(param_1 + 0x70);
  local_28 = (undefined4 *)0x0;
  local_24[0] = 0x42;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_k_ecc");
  }
  ecc_point_mul_windowed(uVar3,*(undefined4 *)(param_1 + 0x28),uVar2,&local_28);
  ecc_point_add(local_28,uVar1,uVar2,&local_28);
  ecc_point_mul_windowed(local_28,*(undefined4 *)(param_1 + 0x60),uVar2,&local_28);
  if (local_28 == (undefined4 *)0x0) {
    uVar1 = 0;
    if (-1 < DebugLevel) {
      printk("%s(): K should not be point-at-infinity\n","sae_derive_k_ecc");
    }
  }
  else {
    ecc_point_3d_to_2d(uVar2,local_28);
    Bignum_BI2Bin_with_pad(*local_28,param_2,local_24,*(undefined4 *)(param_1 + 100));
    hex_dump_with_lvl(&_LC27,param_2,local_24[0],SAE_DEBUG_LEVEL2);
    ecc_point_free(&local_28);
    uVar1 = 1;
  }
  return uVar1;
}

