// module: mt7915.ko
// function: chip_parse_rxv_packet @ 0x136b28
// size: 56 bytes
//

void chip_parse_rxv_packet(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x21c) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136b5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x21c))(param_1,param_4);
  return;
}

