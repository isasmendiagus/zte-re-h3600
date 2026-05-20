// module: mt7915.ko
// function: SetATETxLength @ 0x261c68
// size: 116 bytes
//

undefined4 SetATETxLength(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar2 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: TxLength = %s, control_band_idx = %d\n","SetATETxLength",param_2,(uint)bVar1);
  }
  uVar3 = simple_strtol(param_2,0,10);
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined4 *)((uint)bVar1 * 0xd18 + iVar2 + 0x6dc) = uVar3;
  return 1;
}

