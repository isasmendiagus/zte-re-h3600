// module: mt7915.ko
// function: ZTE_WLAN_Temperature_Protection_Set_Enable @ 0x15fcdc
// size: 200 bytes
//

undefined4 ZTE_WLAN_Temperature_Protection_Set_Enable(int *param_1,int param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  
  if (param_2 == 0 || param_1 == (int *)0x0) {
    printk("\nparatermeter error\n");
  }
  else {
    get_wdev_by_ioctl_idx_and_iftype
              (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
    uVar3 = HcGetBandByWdev();
    if (uVar3 < 2) {
      cVar2 = simple_strtol(param_2,0,10);
      iVar1 = uVar3 * 10;
      (&_LANCHOR0)[iVar1] = cVar2;
      if ((cVar2 == '\0') && ((&DAT_0034d533)[iVar1] != 'd')) {
        AsicThermalProtectAdmitDuty(param_1,uVar3,100,100,100,100);
        (&DAT_0034d533)[iVar1] = 100;
      }
    }
  }
  return 1;
}

