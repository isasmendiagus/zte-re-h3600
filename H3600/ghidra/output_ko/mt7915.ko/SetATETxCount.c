// module: mt7915.ko
// function: SetATETxCount @ 0x261ce0
// size: 124 bytes
//

undefined4 SetATETxCount(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar2 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: TxCount = %s, control_band_idx = %d\n","SetATETxCount",param_2,(uint)bVar1);
  }
  iVar2 = simple_strtol(param_2,0,10);
  if (iVar2 == 0) {
    iVar2 = -1;
  }
  iVar3 = net_ad_wrap_service(param_1);
  *(int *)((uint)bVar1 * 0xd18 + iVar3 + 0x1118) = iVar2;
  return 1;
}

