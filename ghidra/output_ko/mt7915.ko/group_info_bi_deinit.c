// module: mt7915.ko
// function: group_info_bi_deinit @ 0x2172d8
// size: 124 bytes
//

void group_info_bi_deinit(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)0x5dffc4;
  do {
    if (*(char *)((int)puVar1 + 0x21) == '\x01') {
      Bignum_Free(puVar1);
      Bignum_Free(puVar1 + 1);
      Bignum_Free(puVar1 + 2);
      Bignum_Free(puVar1 + 3);
      Bignum_Free(puVar1 + 4);
      Bignum_Free(puVar1 + 5);
      puVar1[6] = 0;
      if (puVar1[7] != 0) {
        os_free_mem();
        puVar1[7] = 0;
      }
      *(undefined1 *)((int)puVar1 + 0x21) = 0;
    }
    puVar1 = puVar1 + 10;
  } while (puVar1 != &OUI_PMF_BIP_CMAC_128_CIPHER);
  return;
}

