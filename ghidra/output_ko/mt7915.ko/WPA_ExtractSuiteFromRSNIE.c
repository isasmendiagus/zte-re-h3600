// module: mt7915.ko
// function: WPA_ExtractSuiteFromRSNIE @ 0x118ac0
// size: 1244 bytes
//

ushort * WPA_ExtractSuiteFromRSNIE(char *param_1,int param_2,int param_3,undefined1 *param_4)

{
  char cVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  *param_4 = 0;
  if (((int)(param_2 - 2U) < 1) || (uVar5 = (uint)(byte)param_1[1], uVar5 != param_2 - 2U)) {
    if (-1 < DebugLevel) {
      printk("%s : The length is invalid\n","WPA_ExtractSuiteFromRSNIE");
    }
    goto LAB_00118bf4;
  }
  cVar1 = *param_1;
  if (cVar1 == -0x23) {
    if (uVar5 < 0x10) {
      if (-1 < DebugLevel) {
        printk("%s : The length is too short for WPA\n","WPA_ExtractSuiteFromRSNIE");
      }
      goto LAB_00118bf4;
    }
    uVar2 = *(ushort *)(param_1 + 0xc);
    uVar6 = (uint)uVar2 * 4 + 0xc;
    if (uVar5 < uVar6) {
      if (-1 < DebugLevel) {
        printk("%s : The expected lenght(%d) exceed the remaining length(%d) for WPA-RSN\n",
               "WPA_ExtractSuiteFromRSNIE",uVar6,uVar5);
      }
      goto LAB_00118bf4;
    }
    if (param_3 == 0) {
      *param_4 = 1;
      return (ushort *)(param_1 + 8);
    }
    if (param_3 == 1) {
      if (2 < DebugLevel) {
        printk("%s : The count of pairwise cipher is %d\n","WPA_ExtractSuiteFromRSNIE",(uint)uVar2);
      }
      *param_4 = (char)uVar2;
      return (ushort *)(param_1 + 0xe);
    }
  }
  else {
    if (cVar1 != '0') {
      if (-1 < DebugLevel) {
        printk("%s : Unknown IE (%d)\n","WPA_ExtractSuiteFromRSNIE",cVar1);
      }
      goto LAB_00118bf4;
    }
    if (uVar5 < 0xc) {
      if (-1 < DebugLevel) {
        printk("%s : The length is too short for WPA2\n","WPA_ExtractSuiteFromRSNIE");
      }
      goto LAB_00118bf4;
    }
    uVar2 = *(ushort *)(param_1 + 8);
    uVar6 = (uint)uVar2 * 4 + 8;
    if (uVar5 < uVar6) {
      if (-1 < DebugLevel) {
        printk("%s : The expected lenght(%d) exceed the remaining length(%d) for WPA2-RSN\n",
               "WPA_ExtractSuiteFromRSNIE",uVar6,uVar5);
      }
      goto LAB_00118bf4;
    }
    if (param_3 == 0) {
      *param_4 = 1;
      return (ushort *)(param_1 + 4);
    }
    if (param_3 == 1) {
      if (2 < DebugLevel) {
        printk("%s : The count of pairwise cipher is %d\n","WPA_ExtractSuiteFromRSNIE",(uint)uVar2);
      }
      *param_4 = (char)uVar2;
      return (ushort *)(param_1 + 10);
    }
  }
  uVar5 = uVar5 - uVar6;
  puVar4 = (ushort *)(param_1 + uVar6 + 2);
  if (uVar5 < 6) {
    if (-1 < DebugLevel) {
      printk("%s : The length of AKM of RSN is too short\n","WPA_ExtractSuiteFromRSNIE");
    }
  }
  else {
    uVar2 = *puVar4;
    uVar6 = (uint)uVar2;
    iVar7 = uVar6 * 4 + 2;
    if ((int)uVar5 < iVar7) {
      if (-1 < DebugLevel) {
        printk("%s : The expected lenght(%d) exceed the remaining length(%d) for AKM\n",
               "WPA_ExtractSuiteFromRSNIE",iVar7);
      }
    }
    else {
      if (param_3 == 2) {
        if (2 < DebugLevel) {
          printk("%s : The count of AKM is %d\n","WPA_ExtractSuiteFromRSNIE",uVar6);
        }
        *param_4 = (char)uVar2;
        return puVar4 + 1;
      }
      if (cVar1 == -0x23) {
        if (2 < DebugLevel) {
          printk("%s : The remaining shall be ignored in WPA mode\n","WPA_ExtractSuiteFromRSNIE");
        }
      }
      else {
        puVar4 = puVar4 + uVar6 * 2 + 1;
        if (uVar5 - iVar7 < 2) {
          if (2 < DebugLevel) {
            printk("%s : The peer RSNIE doesn\'t include RSN-Cap\n","WPA_ExtractSuiteFromRSNIE");
          }
        }
        else {
          if (param_3 == 3) {
            if (2 < DebugLevel) {
              printk("%s : Extract RSN Capabilities\n","WPA_ExtractSuiteFromRSNIE");
            }
            *param_4 = 1;
            return puVar4;
          }
          uVar5 = (uVar5 - iVar7) - 2;
          if (uVar5 < 2) {
            if (2 < DebugLevel) {
              printk("%s : The peer RSNIE doesn\'t include PMKID list Count\n",
                     "WPA_ExtractSuiteFromRSNIE");
            }
          }
          else {
            uVar2 = puVar4[1];
            if (uVar2 == 0) {
              iVar7 = 2;
              puVar3 = (ushort *)0x0;
            }
            else {
              iVar7 = (uint)uVar2 * 0x10 + 2;
              if ((int)uVar5 < iVar7) {
                if (-1 < DebugLevel) {
                  printk("%s : The expected lenght(%d) exceed the remaining length(%d) in PMKID-field\n"
                         ,"WPA_ExtractSuiteFromRSNIE",iVar7);
                }
                goto LAB_00118bf4;
              }
              puVar3 = puVar4 + 2;
            }
            if (param_3 == 4) {
              *param_4 = (char)uVar2;
              return puVar3;
            }
            if ((int)(uVar5 - iVar7) < 4) {
              if (2 < DebugLevel) {
                printk("[PMF]%s : The peer RSNIE doesn\'t include Group_mgmt_cipher_suite\n",
                       "WPA_ExtractSuiteFromRSNIE");
              }
            }
            else if (param_3 == 5) {
              *param_4 = 1;
              return (ushort *)((int)(puVar4 + 1) + iVar7);
            }
          }
        }
      }
    }
  }
LAB_00118bf4:
  *param_4 = 0;
  return (ushort *)0x0;
}

