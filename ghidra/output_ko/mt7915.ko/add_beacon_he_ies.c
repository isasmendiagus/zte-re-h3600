// module: mt7915.ko
// function: add_beacon_he_ies @ 0x2050b4
// size: 100 bytes
//

int add_beacon_he_ies(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_00204e6c(param_1,param_2 + param_3);
  uVar1 = FUN_00204c34(param_1,uVar1);
  iVar2 = FUN_00204910(param_1,uVar1);
  uVar1 = FUN_0020477c(param_1,iVar2,iVar2 - param_2);
  uVar1 = FUN_0020494c(param_1,uVar1);
  iVar2 = FUN_00204a88(param_1,uVar1);
  return (iVar2 - param_2) - param_3;
}

