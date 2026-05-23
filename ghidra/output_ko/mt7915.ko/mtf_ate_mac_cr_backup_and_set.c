// module: mt7915.ko
// function: mtf_ate_mac_cr_backup_and_set @ 0x17239c
// size: 1256 bytes
//

undefined4 mtf_ate_mac_cr_backup_and_set(int param_1)

{
  uint local_24 [2];
  
  __memzero(param_1 + 0xa3b8c0,0x168);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    local_24[0] = 0;
    MtTestModeBkCr(param_1,0x820e206c,1);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e206c,local_24);
    local_24[0] = local_24[0] & 0xffffc0a8 | 0x8000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e206c);
    MtTestModeBkCr(param_1,0x820e2070,1);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2070,local_24);
    local_24[0] = 0xff8fffff;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2070,0xff8fffff);
    MtTestModeBkCr(param_1,0x820e205c,1);
    MtTestModeBkCr(param_1,0x820e2060,1);
    MtTestModeBkCr(param_1,0x820e2064,1);
    MtTestModeBkCr(param_1,0x820e2068,1);
    MtTestModeBkCr(param_1,0x820e2098,1);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2098,local_24);
    local_24[0] = local_24[0] & 0xe0ff003f | 0x1000080;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2098);
    MtTestModeBkCr(param_1,0x820e41e0,1);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e41e0,0);
    MtTestModeBkCr(param_1,0x820e4000,1);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e4000,local_24);
    local_24[0] = local_24[0] & 0xfdffffff;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e4000);
    MtTestModeBkCr(param_1,0x820e20f0,1);
    MtTestModeBkCr(param_1,0x820e20f4,1);
    MtTestModeBkCr(param_1,0x820e409c,1);
    MtTestModeBkCr(param_1,0x820e40a4,1);
    MtTestModeBkCr(param_1,0x820e3194,1);
    MtTestModeBkCr(param_1,0x820e3198,1);
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      MtTestModeBkCr(param_1,0x820f206c,1);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f206c,local_24);
      local_24[0] = local_24[0] & 0xffffc0a8 | 0x8000;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f206c);
      MtTestModeBkCr(param_1,0x820f2070,1);
      local_24[0] = 0xff8fffff;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2070,0xff8fffff);
      MtTestModeBkCr(param_1,0x820f205c,1);
      MtTestModeBkCr(param_1,0x820f2060,1);
      MtTestModeBkCr(param_1,0x820f2064,1);
      MtTestModeBkCr(param_1,0x820f2068,1);
      MtTestModeBkCr(param_1,0x820f2098,1);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2098,local_24);
      local_24[0] = local_24[0] & 0xe0ff003f | 0x1000080;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2098);
      MtTestModeBkCr(param_1,0x820f41e0,1);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f41e0,0);
      MtTestModeBkCr(param_1,0x820f4000,1);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4000,local_24);
      local_24[0] = local_24[0] & 0xfdffffff;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4000);
      MtTestModeBkCr(param_1,0x820f20f0,1);
      MtTestModeBkCr(param_1,0x820f20f4,1);
      MtTestModeBkCr(param_1,0x820f409c,1);
      MtTestModeBkCr(param_1,0x820f40a4,1);
      MtTestModeBkCr(param_1,0x820f3194,1);
      MtTestModeBkCr(param_1,0x820f3198,1);
      if (*(char *)(param_1 + 0x79504d) != '\0') {
        MtTestModeBkCr(param_1,0x820f409c,1);
        MtTestModeBkCr(param_1,0x820f40a4,1);
        MtTestModeBkCr(param_1,0x820f3194,1);
        MtTestModeBkCr(param_1,0x820f3198,1);
      }
    }
  }
  return 0;
}

