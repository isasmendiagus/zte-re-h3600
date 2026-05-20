// module: mt7915.ko
// function: SetATEQid @ 0x2608d4
// size: 120 bytes
//

undefined4 SetATEQid(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  iVar1 = DebugLevel;
  *(undefined2 *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0x50e) = uVar2;
  if (0 < iVar1) {
    printk("%s: QID:%u\n","SetATEQid",uVar2);
  }
  return 1;
}

