// module: mt7915.ko
// function: mtf_asic_rts_on_off @ 0x197138
// size: 64 bytes
//

undefined4 mtf_asic_rts_on_off(int param_1,int param_2,int param_3,uint param_4)

{
  undefined4 uVar1;
  
  uVar1 = 0x820f2070;
  if (param_2 != 1) {
    uVar1 = 0x820e2070;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,param_4 & 0xfffff | param_3 << 0x17,
                 param_4 & 0xfffff,param_4);
  return 0;
}

