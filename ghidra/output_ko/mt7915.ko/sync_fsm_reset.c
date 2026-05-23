// module: mt7915.ko
// function: sync_fsm_reset @ 0x10ba98
// size: 52 bytes
//

void sync_fsm_reset(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = HcGetBandByWdev(param_2);
  *(undefined4 *)(iVar1 * 0xaf5d8 + param_1 + 0x829300) = 0;
  return;
}

