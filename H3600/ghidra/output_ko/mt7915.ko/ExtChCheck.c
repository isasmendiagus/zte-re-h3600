// module: mt7915.ko
// function: ExtChCheck @ 0x141140
// size: 44 bytes
//

bool ExtChCheck(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  if (param_3 == 1) {
    uVar2 = param_2 + 4;
  }
  else {
    uVar2 = param_2 - 4U & ~((int)(param_2 - 4U) >> 0x1f);
  }
  iVar1 = FUN_00140ed0(param_1,uVar2 & 0xff,param_4,param_4,param_4);
  return iVar1 != 0;
}

