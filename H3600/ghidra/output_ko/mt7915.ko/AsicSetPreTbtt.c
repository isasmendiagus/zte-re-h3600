// module: mt7915.ko
// function: AsicSetPreTbtt @ 0x1329bc
// size: 84 bytes
//

undefined4 AsicSetPreTbtt(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x70) != (code *)0x0) {
    (**(code **)(iVar1 + 0x70))(param_1,param_2,param_3);
    return 1;
  }
  AsicNotSupportFunc(param_1,"AsicSetPreTbtt");
  return 0;
}

