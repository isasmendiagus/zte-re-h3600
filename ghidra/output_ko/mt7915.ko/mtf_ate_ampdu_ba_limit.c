// module: mt7915.ko
// function: mtf_ate_ampdu_ba_limit @ 0x172884
// size: 400 bytes
//

undefined4 mtf_ate_ampdu_ba_limit(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  
  if (param_2 < 4) {
    if (2 < DebugLevel) {
      printk("%s: WmmIdx=%d\n","mtf_ate_ampdu_ba_limit",param_2,DebugLevel,param_4);
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),
                   *(undefined4 *)(bn0_agg_cnt_array + param_2 * 4),
                   param_3 << 0x10 | param_3 << 0x18 | param_3 | param_3 << 8);
  }
  else {
    if (-1 < DebugLevel) {
      printk("%s: invalid WmmIdx=%d, set to all!\n","mtf_ate_ampdu_ba_limit",param_2,DebugLevel,
             param_4);
      if (2 < DebugLevel) {
        printk("%s: WmmIdx=%d\n","mtf_ate_ampdu_ba_limit",0xff);
      }
    }
    uVar1 = param_3 << 0x10 | param_3 << 0x18 | param_3 | param_3 << 8;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2048,uVar1);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e204c,uVar1);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2050,uVar1);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2054,uVar1);
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e205c,0);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2060,0);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2064,0);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e2068,0);
  return 0;
}

