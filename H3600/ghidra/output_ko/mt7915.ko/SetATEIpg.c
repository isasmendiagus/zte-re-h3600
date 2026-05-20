// module: mt7915.ko
// function: SetATEIpg @ 0x262854
// size: 172 bytes
//

undefined4 SetATEIpg(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_2 == 0) {
    uVar4 = 0;
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetATEIpg",param_3,DebugLevel,param_4);
    }
  }
  else {
    if (0 < DebugLevel) {
      printk("%s: IPG = %s\n","SetATEIpg",param_2,DebugLevel,param_4);
    }
    uVar4 = 1;
    uVar1 = simple_strtol(param_2,0,10);
    iVar2 = net_ad_wrap_service(param_1);
    iVar3 = net_ad_wrap_service(param_1);
    *(undefined4 *)((uint)*(byte *)(iVar3 + 0x4cc) * 0xd18 + iVar2 + 0x10f4) = uVar1;
  }
  return uVar4;
}

