// module: mt7915.ko
// function: set_ate_ru_rx_aid @ 0x262094
// size: 220 bytes
//

undefined4 set_ate_ru_rx_aid(undefined4 param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  if (*param_2 == '\0') {
    if (-1 < DebugLevel) {
      printk("%s: Invalid string\n","set_ate_ru_rx_aid");
    }
    return 1;
  }
  sscanf(param_2,"%d",local_14);
  if (0 < DebugLevel) {
    iVar1 = net_ad_wrap_service(param_1);
    printk("%s: RX MU PPDU Aid = %s, control_band_idx = %d\n","set_ate_ru_rx_aid",param_2,
           *(undefined1 *)(iVar1 + 0x4cc));
  }
  iVar1 = net_ad_wrap_service(param_1);
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined4 *)((uint)*(byte *)(iVar2 + 0x4cc) * 0xd18 + iVar1 + 0x1110) = local_14[0];
  return 1;
}

