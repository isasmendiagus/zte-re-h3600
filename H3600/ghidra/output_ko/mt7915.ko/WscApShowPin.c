// module: mt7915.ko
// function: WscApShowPin @ 0x1ee0e0
// size: 1016 bytes
//

undefined4 WscApShowPin(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar7 = *(uint *)(*param_1 + 0x3c);
  if (*(int *)(*param_1 + 0x38) != 0x400) {
    if (DebugLevel < 3) {
      return 1;
    }
    uVar7 = uVar7 & 0xff;
    printk("IF(ra%d) WPS Information:\n",uVar7);
    if ((char)param_1[uVar7 * 0x160d + 0xae153] == '\b') {
      if (DebugLevel < 3) {
        return 1;
      }
      printk("Enrollee PinCode(ra%d)           %08u\n",uVar7,param_1[uVar7 * 0x160d + 0xae152]);
      iVar3 = DebugLevel;
    }
    else {
      if (DebugLevel < 3) {
        return 1;
      }
      printk("Enrollee PinCode(ra%d)           %04u\n",uVar7,param_1[uVar7 * 0x160d + 0xae152]);
      iVar3 = DebugLevel;
    }
    goto LAB_001ee1a4;
  }
  uVar7 = uVar7 & 0xff;
  if (DebugLevel < 1) {
LAB_001ee138:
    iVar3 = uVar7 * 0x20;
    if (param_1[uVar7 * 0x84dec + 0xdc2b3] == 0) {
      return 1;
    }
  }
  else {
    printk("IF(apcli%d) WPS Information:\n",uVar7);
    if ((char)param_1[uVar7 * 0x84dec + 0xdbb97] == '\b') {
      if (0 < DebugLevel) {
        printk("Enrollee PinCode(ApCli%d)        %08u\n",uVar7,param_1[uVar7 * 0x84dec + 0xdbb96]);
        goto LAB_001ee458;
      }
      goto LAB_001ee138;
    }
    if (DebugLevel < 1) goto LAB_001ee138;
    printk("Enrollee PinCode(ApCli%d)        %04u\n",uVar7,param_1[uVar7 * 0x84dec + 0xdbb96]);
LAB_001ee458:
    if (DebugLevel < 1) goto LAB_001ee138;
    printk("Ap Client WPS Profile Count     = %d\n",param_1[uVar7 * 0x84dec + 0xdc2b3]);
    iVar3 = DebugLevel;
    if (param_1[uVar7 * 0x84dec + 0xdc2b3] == 0) goto LAB_001ee1a4;
    iVar3 = uVar7 << 5;
  }
  uVar6 = 0;
  iVar1 = iVar3 * 4 + uVar7 * 5;
  iVar3 = DebugLevel;
  do {
    if (0 < iVar3) {
      printk("Profile[%d]:\n",uVar6);
      if (DebugLevel < 1) {
LAB_001ee2c0:
        iVar3 = DebugLevel;
        if ((*(short *)(&DAT_00370b3c + (int)(param_1 + uVar6 * 0x1d + iVar1 * 0xffc)) != 0) &&
           (0 < DebugLevel)) {
          printk("Key                             = %s\n",
                 param_1 + uVar7 * 0x84dec + uVar6 * 0x1d + 0xdc2bf);
          iVar3 = DebugLevel;
        }
      }
      else {
        printk("SSID                            = %s\n",
               param_1 + uVar6 * 0x1d + iVar1 * 0xffc + 0xdc2b6);
        iVar3 = DebugLevel;
        if (0 < DebugLevel) {
          uVar2 = WscGetAuthTypeStr(*(undefined2 *)
                                     (&DAT_00370af8 + (int)(param_1 + uVar6 * 0x1d + iVar1 * 0xffc))
                                   );
          printk("AuthType                        = %s\n",uVar2);
          iVar3 = DebugLevel;
          if (0 < DebugLevel) {
            uVar5 = *(ushort *)(&DAT_00370afa + (int)(param_1 + uVar6 * 0x1d + iVar1 * 0xffc)) - 1 &
                    0xffff;
            if (uVar5 < 8) {
              pcVar4 = *(char **)(&DAT_002a10d8 + uVar5 * 4);
            }
            else {
              pcVar4 = "TKIPAES";
            }
            printk("EncrypType                      = %s\n",pcVar4);
            iVar3 = DebugLevel;
            if (0 < DebugLevel) {
              printk("KeyIndex                        = %d\n",
                     (&DAT_00370b44)[(int)(param_1 + uVar6 * 0x1d + iVar1 * 0xffc)]);
              goto LAB_001ee2c0;
            }
          }
        }
      }
    }
    uVar6 = uVar6 + 1 & 0xff;
  } while (uVar6 < (uint)param_1[iVar1 * 0xffc + 0xdc2b3]);
LAB_001ee1a4:
  if (2 < iVar3) {
    printk(&_LC13);
  }
  return 1;
}

