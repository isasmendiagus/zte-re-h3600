// module: mt7915.ko
// function: set_ate_max_pe @ 0x261fac
// size: 196 bytes
//

undefined4 set_ate_max_pe(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  if (0 < DebugLevel) {
    iVar2 = net_ad_wrap_service();
    printk("%s: Max Packet Extension = %s, control_band_idx = %d\n","set_ate_max_pe",param_2,
           *(undefined1 *)(iVar2 + 0x4cc));
  }
  bVar1 = simple_strtol(param_2,0,10);
  if (2 < bVar1) {
    if (-1 < DebugLevel) {
      printk("%s : %d is invalid (0: 0us, 1:8 us, 2:16 us)\n","set_ate_max_pe",bVar1);
    }
    return 0;
  }
  iVar2 = net_ad_wrap_service(param_1);
  iVar3 = net_ad_wrap_service(param_1);
  *(byte *)((uint)*(byte *)(iVar3 + 0x4cc) * 0xd18 + iVar2 + 0x1150) = bVar1;
  return 1;
}

