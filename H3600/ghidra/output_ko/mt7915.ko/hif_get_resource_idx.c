// module: mt7915.ko
// function: hif_get_resource_idx @ 0xab370
// size: 76 bytes
//

undefined4 hif_get_resource_idx(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = HcGetBandByWdev(param_2);
  }
  if (*(code **)(param_1 + 0xacc) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab3b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xacc))(param_1,uVar1,param_3,param_4);
    return uVar1;
  }
  return 0;
}

