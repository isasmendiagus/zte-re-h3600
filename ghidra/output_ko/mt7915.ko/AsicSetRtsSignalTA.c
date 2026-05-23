// module: mt7915.ko
// function: AsicSetRtsSignalTA @ 0x135704
// size: 112 bytes
//

undefined4 AsicSetRtsSignalTA(int param_1,undefined4 param_2)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  pcVar2 = *(code **)(iVar1 + 0xc0);
  if (pcVar2 != (code *)0x0) {
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      (*pcVar2)(param_1,1,param_2);
      pcVar2 = *(code **)(iVar1 + 0xc0);
    }
    (*pcVar2)(param_1,0,param_2);
  }
  return 1;
}

