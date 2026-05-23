// module: mt7915.ko
// function: ICapRawDataHandler @ 0x1a6458
// size: 68 bytes
//

undefined4 ICapRawDataHandler(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  pcVar2 = *(code **)(iVar1 + 0x19c);
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),pcVar2,param_4);
    return 0;
  }
  return 1;
}

