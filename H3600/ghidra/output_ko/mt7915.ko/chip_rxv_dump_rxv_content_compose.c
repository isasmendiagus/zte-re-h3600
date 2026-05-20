// module: mt7915.ko
// function: chip_rxv_dump_rxv_content_compose @ 0x136cc0
// size: 72 bytes
//

void chip_rxv_dump_rxv_content_compose
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x248) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136d04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x248))(param_1,param_2,param_3,param_4);
  return;
}

