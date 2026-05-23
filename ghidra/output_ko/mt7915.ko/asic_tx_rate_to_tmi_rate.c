// module: mt7915.ko
// function: asic_tx_rate_to_tmi_rate @ 0x1343e4
// size: 108 bytes
//

undefined4
asic_tx_rate_to_tmi_rate
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x114) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134438. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x114))(param_2,param_3,param_4,param_5);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_tx_rate_to_tmi_rate");
  return 0;
}

