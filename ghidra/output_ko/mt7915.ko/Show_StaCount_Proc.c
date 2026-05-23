// module: mt7915.ko
// function: Show_StaCount_Proc @ 0x2dda8
// size: 644 bytes
//

undefined4 Show_StaCount_Proc(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  uint *puVar6;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    iVar1 = wlan_operate_get_addht(iVar1);
    if ((2 < DebugLevel) &&
       (printk("\nHT Operating Mode : %d\n",*(byte *)(iVar1 + 2) & 3), 2 < DebugLevel)) {
      printk("\n\n%-19s%-4s%-12s%-12s%-12s%-12s%-12s%-12s\n",&_LC252,&_LC253,"TxPackets","RxPackets"
             ,"TxBytes","RxBytes","TP(Tx)","TP(Rx)");
    }
    puVar6 = (uint *)(param_1 + 0x28c21);
    piVar5 = param_1 + 0x28786;
    for (iVar1 = 0; iVar2 = HcGetMaxStaNum(param_1), iVar1 < iVar2; iVar1 = iVar1 + 1) {
      uVar4 = piVar5[-0x3e];
      if (((((uVar4 == 2 || (uVar4 - 0x20001 & 0xfffdffff) == 0) && (piVar5[1] == 2)) ||
           ((uVar4 & 4) != 0)) &&
          ((((2 < DebugLevel &&
             (printk("%02x:%02x:%02x:%02x:%02x:%02x  ",(char)piVar5[-3],
                     *(undefined1 *)((int)piVar5 + -0xb),*(undefined1 *)((int)piVar5 + -10),
                     *(undefined1 *)((int)piVar5 + -9),(char)piVar5[-2],
                     *(undefined1 *)((int)piVar5 + -7)), 2 < DebugLevel)) &&
            ((printk(&_LC261,(short)*piVar5), 2 < DebugLevel &&
             ((printk("%-12u",puVar6[-0x19]), 2 < DebugLevel &&
              (printk("%-12u",puVar6[-0x17]), 2 < DebugLevel)))))) &&
           (printk("%-12u",puVar6[-0x15]), 2 < DebugLevel)))) &&
         (((printk("%-12u",puVar6[-0x13]), 2 < DebugLevel &&
           (printk("%lu %-12s",puVar6[-1] >> 0x11,&_LC264), 2 < DebugLevel)) &&
          (printk("%lu %-12s",*puVar6 >> 0x11,&_LC264), 2 < DebugLevel)))) {
        printk(&_LC220);
      }
      puVar6 = puVar6 + 0x530;
      piVar5 = piVar5 + 0x530;
    }
    uVar3 = 1;
  }
  return uVar3;
}

