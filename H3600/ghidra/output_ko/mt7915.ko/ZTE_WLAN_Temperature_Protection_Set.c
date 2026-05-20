// module: mt7915.ko
// function: ZTE_WLAN_Temperature_Protection_Set @ 0x15fbf0
// size: 236 bytes
//

undefined4 ZTE_WLAN_Temperature_Protection_Set(int *param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14[0] = 0;
  if (param_2 == (char *)0x0 || param_1 == (int *)0x0) {
    printk("\nparatermeter error\n");
  }
  else {
    get_wdev_by_ioctl_idx_and_iftype
              (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
    uVar2 = HcGetBandByWdev();
    if (uVar2 < 2) {
      sscanf(param_2,"%d-%d-%d-%d-%d-%d",&local_28,&local_24,&local_20,&local_1c,&local_18,local_14)
      ;
      iVar1 = uVar2 * 10;
      (&DAT_0034d52f)[iVar1] = (char)local_20;
      (&DAT_0034d52d)[iVar1] = (char)local_28;
      (&DAT_0034d52e)[iVar1] = (char)local_24;
      (&DAT_0034d530)[iVar1] = (char)local_1c;
      (&DAT_0034d531)[iVar1] = (char)local_18;
      (&DAT_0034d532)[iVar1] = (char)local_14[0];
      return 1;
    }
  }
  return 1;
}

