// module: mt7915.ko
// function: AsicUpdateRxWCIDTableDetail @ 0x135c1c
// size: 136 bytes
//

void AsicUpdateRxWCIDTableDetail
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x138) != (code *)0x0) {
    (**(code **)(iVar1 + 0x138))
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicUpdateRxWCIDTableDetail");
  return;
}

