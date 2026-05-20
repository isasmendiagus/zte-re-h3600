// module: mt7915.ko
// function: SetATETxLdpc @ 0x261e90
// size: 184 bytes
//

undefined4 SetATETxLdpc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  
  iVar3 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar3 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: Ldpc = %s, control_band_idx = %d\n","SetATETxLdpc",param_2,(uint)bVar1,param_4);
  }
  bVar2 = simple_strtol(param_2,0,10);
  if (1 < bVar2) {
    if (-1 < DebugLevel) {
      printk("%s: Out of range (%d)\n","SetATETxLdpc",bVar2,DebugLevel,param_4);
    }
    return 0;
  }
  iVar3 = net_ad_wrap_service(param_1);
  *(byte *)((uint)bVar1 * 0xd18 + iVar3 + 0x113b) = bVar2;
  return 1;
}

