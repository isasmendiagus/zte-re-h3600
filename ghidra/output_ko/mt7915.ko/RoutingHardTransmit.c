// module: mt7915.ko
// function: RoutingHardTransmit @ 0xa124c
// size: 68 bytes
//

void RoutingHardTransmit(int param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_2 + 0x904);
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar1 & 0x400) == 0) {
    UNRECOVERED_JUMPTABLE = (code *)*puVar2;
  }
  else {
    UNRECOVERED_JUMPTABLE = (code *)puVar2[1];
  }
                    /* WARNING: Could not recover jumptable at 0x000a128c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,param_3);
  return;
}

