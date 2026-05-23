// module: mt7915.ko
// function: SetATEPowerPercentCtrl @ 0x26c99c
// size: 208 bytes
//

undefined4
SetATEPowerPercentCtrl(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0xa39fd4);
  iVar2 = net_ad_wrap_service();
  cVar1 = *(char *)(iVar2 + 0x4cc);
  uVar3 = simple_strtol(param_2,0,10);
  if (DebugLevel < 1) {
    if (100 < uVar3) {
      return 0;
    }
  }
  else {
    printk("%s: PowerPercentLevel = %d\n","SetATEPowerPercentCtrl",uVar3,DebugLevel,param_4);
    if (100 < uVar3) goto LAB_0026ca44;
  }
  if (cVar1 == '\0') {
    *(uint *)(param_1 + 0xa3ba90) = uVar3;
  }
  else if (cVar1 == '\x01') {
    *(uint *)(param_1 + 0xa3abb8) = uVar3;
  }
  iVar2 = (**(code **)(iVar4 + 0x74))(param_1,uVar3);
  if (iVar2 == 0) {
    return 1;
  }
LAB_0026ca44:
  if (0 < DebugLevel) {
    printk("%s: Please input X which is 0~100\n","SetATEPowerPercentCtrl");
  }
  return 0;
}

