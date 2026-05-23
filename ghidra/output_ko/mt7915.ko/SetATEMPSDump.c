// module: mt7915.ko
// function: SetATEMPSDump @ 0x260d00
// size: 48 bytes
//

bool SetATEMPSDump(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = simple_strtol(param_2,0,10);
  iVar2 = MT_SetATEMPSDump(param_1,uVar1);
  return iVar2 == 0;
}

