// module: mt7915.ko
// function: PMF_RsnCapableValidation @ 0x21a180
// size: 1208 bytes
//

undefined4
PMF_RsnCapableValidation
          (undefined4 param_1,undefined4 param_2,int param_3,int param_4,uint param_5,byte param_6,
          uint *param_7)

{
  ushort uVar1;
  bool bVar2;
  ushort *puVar3;
  void *pvVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  char local_2d;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  puVar3 = (ushort *)WPA_ExtractSuiteFromRSNIE();
  if (puVar3 == (ushort *)0x0) {
    if (DebugLevel < 0) {
      if (param_4 != 0) {
        return 0x1f;
      }
    }
    else {
      printk("[PMF]%s : Peer\'s MPFC isn\'t used.\n","PMF_RsnCapableValidation");
      if (param_4 != 0) {
        if (DebugLevel < 0) {
          return 0x1f;
        }
        printk("[PMF]%s : PMF policy violation.\n","PMF_RsnCapableValidation");
        return 0x1f;
      }
    }
  }
  else {
    uVar1 = *puVar3;
    local_24 = CONCAT22(local_24._2_2_,uVar1);
    uVar6 = local_24;
    local_24._0_1_ = (byte)uVar1;
    uVar7 = -((int)((uint)uVar1 << 0x19) >> 0x1f);
    bVar2 = (bool)((byte)local_24 >> 7);
    local_24 = uVar6;
    if (bVar2 < (param_3 == 1)) {
      if (uVar7 < (param_4 == 1)) {
        if (DebugLevel < 0) {
          return 0x1f;
        }
        printk("[PMF]%s : PMF policy violation for case 4\n","PMF_RsnCapableValidation");
        return 0x1f;
      }
      if (uVar7 == 1) {
        if (DebugLevel < 0) {
          return 0x1f;
        }
        printk("[PMF]%s : PMF policy violation for case 7\n","PMF_RsnCapableValidation");
        return 0x1f;
      }
    }
    if ((param_3 == 1 & bVar2) == 0) {
      if (bVar2 < ((*param_7 & 0x6000) != 0)) {
        if (-1 < DebugLevel) {
          printk("[PMF]%s: SAE connection fail due to not PMF connection(peer MFPR = %d, MFPC = %d)\n"
                 ,"PMF_RsnCapableValidation");
        }
        return 0x1f;
      }
    }
    else {
      if (-1 < DebugLevel) {
        printk("[PMF]%s: PMF Connection\n","PMF_RsnCapableValidation");
      }
      *(undefined1 *)((int)param_7 + 0x3e6) = 1;
    }
  }
  pvVar4 = (void *)WPA_ExtractSuiteFromRSNIE(param_1,param_2,2,&local_2d);
  if (pvVar4 != (void *)0x0 && param_3 == 1) {
    local_2c = 0x5ac0f00;
    local_28 = 0x6ac0f00;
    local_24 = 0x8ac0f00;
    for (; local_2d != '\0'; local_2d = local_2d + -1) {
      iVar5 = memcmp(pvVar4,&local_2c,4);
      if (iVar5 == 0) {
LAB_0021a2a8:
        iVar5 = DebugLevel;
        *(undefined1 *)(param_7 + 0xa1) = 1;
        if (-1 < iVar5) {
          printk("[PMF]%s : SHA256 Support\n","PMF_RsnCapableValidation");
        }
      }
      else {
        iVar5 = memcmp(pvVar4,&local_28,4);
        if ((iVar5 == 0) || (iVar5 = memcmp(pvVar4,&local_24,4), iVar5 == 0)) goto LAB_0021a2a8;
      }
      pvVar4 = (void *)((int)pvVar4 + 4);
    }
  }
  if (*(char *)((int)param_7 + 0x3e6) != '\x01') {
    return 0;
  }
  if (param_6 < 6) {
    if ((param_5 & 0x200) != 0) {
      *(uint *)((int)param_7 + 999) = param_5;
      return 0;
    }
    if (DebugLevel < 0) {
      return 0x2e;
    }
    printk("[PMF]%s : The peer Group_mgmt_cipher_suite(default) is mismatch\n",
           "PMF_RsnCapableValidation");
  }
  else {
    pvVar4 = (void *)WPA_ExtractSuiteFromRSNIE(param_1,param_2,5,&local_2d);
    if (pvVar4 == (void *)0x0) {
      if (DebugLevel < 0) {
        return 0x2e;
      }
      printk("[PMF]%s : The peer RSNIE doesn\'t include Group_mgmt_cipher_suite\n",
             "PMF_RsnCapableValidation");
    }
    else {
      iVar5 = memcmp(pvVar4,&OUI_PMF_BIP_CMAC_128_CIPHER,4);
      if (iVar5 == 0) {
        uVar7 = 0x200;
        *(undefined1 *)((int)param_7 + 999) = 0;
        *(undefined1 *)((int)param_7 + 0x3e9) = 0;
        *(undefined1 *)((int)param_7 + 0x3ea) = 0;
        *(undefined1 *)(param_7 + 0xfa) = 2;
      }
      else {
        iVar5 = memcmp(pvVar4,&OUI_PMF_BIP_CMAC_256_CIPHER,4);
        if (iVar5 == 0) {
          *(undefined1 *)((int)param_7 + 999) = 0;
          *(undefined1 *)((int)param_7 + 0x3e9) = 0;
          uVar7 = 0x400;
          *(undefined1 *)((int)param_7 + 0x3ea) = 0;
          *(undefined1 *)(param_7 + 0xfa) = 4;
        }
        else {
          iVar5 = memcmp(pvVar4,&OUI_PMF_BIP_GMAC_128_CIPHER,4);
          if (iVar5 == 0) {
            *(undefined1 *)((int)param_7 + 999) = 0;
            *(undefined1 *)((int)param_7 + 0x3e9) = 0;
            uVar7 = 0x800;
            *(undefined1 *)((int)param_7 + 0x3ea) = 0;
            *(undefined1 *)(param_7 + 0xfa) = 8;
          }
          else {
            iVar5 = memcmp(pvVar4,&OUI_PMF_BIP_GMAC_256_CIPHER,4);
            if (iVar5 != 0) {
              if (-1 < DebugLevel) {
                printk("[PMF]%s : unknown peer Group_mgmt_cipher_suite\n","PMF_RsnCapableValidation"
                      );
              }
              hex_dump("peer Group_mgmt_cipher_suite",pvVar4,4);
              return 0x2e;
            }
            *(undefined1 *)((int)param_7 + 999) = 0;
            *(undefined1 *)((int)param_7 + 0x3e9) = 0;
            uVar7 = 0x1000;
            *(undefined1 *)((int)param_7 + 0x3ea) = 0;
            *(undefined1 *)(param_7 + 0xfa) = 0x10;
          }
        }
      }
      if ((uVar7 & param_5) != 0) {
        return 0;
      }
      if (-1 < DebugLevel) {
        uVar6 = GetEncryModeStr(uVar7);
        printk("[PMF]%s : peer Group_mgmt_cipher_suite(%s) is mismatch\n","PMF_RsnCapableValidation"
               ,uVar6);
      }
      *(undefined1 *)((int)param_7 + 999) = 0;
      *(undefined1 *)(param_7 + 0xfa) = 0;
      *(undefined1 *)((int)param_7 + 0x3e9) = 0;
      *(undefined1 *)((int)param_7 + 0x3ea) = 0;
    }
  }
  return 0x2e;
}

