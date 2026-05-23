// module: mt7915.ko
// function: chip_set_mgmt_pkt_txpwr @ 0x1367e8
// size: 64 bytes
//

void chip_set_mgmt_pkt_txpwr(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x2f8) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136824. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x2f8))(param_1,param_2,param_3);
  return;
}

