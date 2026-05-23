// module: mt7915.ko
// function: Set_AP_WscPinCode_Proc @ 0x32310
// size: 644 bytes
//

undefined4 Set_AP_WscPinCode_Proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  int iVar7;
  size_t sVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  int unaff_r11;
  
  iVar9 = *param_1;
  uVar11 = *(uint *)(iVar9 + 0x3c);
  iVar7 = os_str_tol(param_2,0,10);
  uVar11 = uVar11 & 0xff;
  if (*(int *)(iVar9 + 0x38) == 0x400) {
    if (DebugLevel < 3) {
      unaff_r11 = 1;
    }
    piVar10 = param_1 + uVar11 * 0x84dec + 0xdbb8f;
    if (2 < DebugLevel) {
      unaff_r11 = 1;
      printk("IF(apcli%d) Set_WscPinCode_Proc:: This command is from apcli interface now.\n",uVar11)
      ;
    }
  }
  else {
    piVar10 = param_1 + uVar11 * 0x160d + 0xae14b;
    if (DebugLevel < 3) {
      unaff_r11 = 0;
      piVar10 = param_1 + uVar11 * 0x160d + 0xae14b;
    }
    else {
      unaff_r11 = 0;
      printk("IF(ra%d) Set_WscPinCode_Proc:: This command is from ra interface now.\n",uVar11);
    }
  }
  sVar8 = strlen(param_2);
  if ((sVar8 == 4) || (iVar9 = ValidateChecksum(iVar7), iVar9 != 0)) {
    if (((char)piVar10[0xa7d] == '\0') || (piVar10[0xa7c] != iVar7)) {
      piVar10[5] = iVar7;
      piVar10[0xa7c] = iVar7;
      *(undefined1 *)(piVar10 + 0xa7d) = 0;
      sVar8 = strlen(param_2);
      if (sVar8 == 4) {
        *(undefined1 *)(piVar10 + 6) = 4;
        *(undefined1 *)(piVar10 + 0x6bb) = 4;
        memmove(piVar10 + 0x6b9,param_2,4);
      }
      else {
        *(undefined1 *)(piVar10 + 6) = 8;
        if (*param_2 == '0') {
          *(undefined1 *)(piVar10 + 0x6bb) = 8;
          memmove(piVar10 + 0x6b9,param_2,8);
        }
        else {
          WscGetRegDataPIN(param_1,iVar7,piVar10);
        }
      }
      if (unaff_r11 == 0) {
        uVar1 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b7269);
        uVar5 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726a);
        uVar3 = (undefined1)param_1[uVar11 * 0x160d + 0xadc9b];
        uVar2 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726b);
        uVar4 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726d);
        uVar6 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726e);
      }
      else {
        uVar1 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db73);
        uVar2 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db75);
        uVar5 = (undefined1)param_1[uVar11 * 0x84dec + 0xdb6dd];
        uVar3 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db76);
        uVar4 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db77);
        uVar6 = (undefined1)param_1[uVar11 * 0x84dec + 0xdb6de];
      }
      if (2 < DebugLevel) {
        printk("IF(%02x:%02x:%02x:%02x:%02x:%02x) Set_WscPinCode_Proc::(PinCode=%d)\n",uVar1,uVar5,
               uVar2,uVar3,uVar4,uVar6,piVar10[5]);
        return 1;
      }
      return 1;
    }
    if (2 < DebugLevel) {
      printk("PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%s)\n"
             ,param_2);
    }
  }
  else if (2 < DebugLevel) {
    printk("Set failed!!(Set_WscPinCode_Proc=%s), PinCode Checksum invalid\n",param_2);
    return 0;
  }
  return 0;
}

