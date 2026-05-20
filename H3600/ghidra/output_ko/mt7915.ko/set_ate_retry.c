// module: mt7915.ko
// function: set_ate_retry @ 0x262338
// size: 220 bytes
//

undefined4 set_ate_retry(undefined4 param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  if (*param_2 == '\0') {
    if (-1 < DebugLevel) {
      printk("%s: Invalid string\n","set_ate_retry");
    }
    return 1;
  }
  sscanf(param_2,"%u",local_14);
  if (0 < DebugLevel) {
    iVar1 = net_ad_wrap_service(param_1);
    printk("%s: TX PPDU Retry = %s, control_band_idx = %d\n","set_ate_retry",param_2,
           *(undefined1 *)(iVar1 + 0x4cc));
  }
  iVar1 = net_ad_wrap_service(param_1);
  iVar2 = net_ad_wrap_service(param_1);
  *(char *)((uint)*(byte *)(iVar2 + 0x4cc) * 0xd18 + iVar1 + 0x1104) = (char)local_14[0];
  return 1;
}

