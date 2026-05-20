// module: mt7915.ko
// function: SetMuMimoFixedRate @ 0xede28
// size: 68 bytes
//

undefined4 SetMuMimoFixedRate(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  code *pcVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  pcVar2 = *(code **)(iVar1 + 0x2c0);
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(param_1,param_2,extraout_r2,pcVar2,param_4);
    return 1;
  }
  return 0;
}

