// module: mt7915.ko
// function: ShowMuruLocalData @ 0x23b228
// size: 68 bytes
//

undefined4 ShowMuruLocalData(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  code *pcVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  pcVar2 = *(code **)(iVar1 + 0x2a0);
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(param_1,param_2,extraout_r2,pcVar2,param_4);
    return 1;
  }
  return 0;
}

