// module: mt7915.ko
// function: WPAValidateRSNIE @ 0x11bec8
// size: 788 bytes
//

int WPAValidateRSNIE(uint *param_1,uint *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  byte bVar2;
  byte local_1a;
  char local_19;
  
  local_1a = 0;
  *(char *)(param_2 + 0x165) = (char)param_1[0x165];
  if (param_4 == 0) {
    return 0;
  }
  iVar1 = wpa_rsne_sanity(param_3,param_4,&local_1a);
  if (iVar1 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s : wpa_rsne_sanity fail\n","WPAValidateRSNIE");
    return 1;
  }
  if (2 < DebugLevel) {
    printk("%s : peer RSNE end field is %d\n","WPAValidateRSNIE",local_1a);
  }
  bVar2 = 0;
  if (local_1a == 0) {
LAB_0011bf3c:
    if ((param_1[0x8a] & 0x20) == 0) {
      if (DebugLevel < 0) {
        return 0x29;
      }
      printk("[ERROR]%s : invalid group cipher(peer use default cipher) !!!\n","WPAValidateRSNIE");
      return 0x29;
    }
    param_2[0x8a] = param_1[0x8a];
LAB_0011bf4c:
    if ((param_1[0x52] & 0x20) == 0) {
      if (DebugLevel < 0) {
        return 0x2a;
      }
      printk("[ERROR]%s : invalid pairwise cipher(peer use default cipher) !!!\n","WPAValidateRSNIE"
            );
      return 0x2a;
    }
    param_2[0x52] = param_1[0x52];
LAB_0011bf5c:
    if (2 < bVar2) {
      if (((4 < bVar2) && (local_19 = '\0', (*param_2 & 0x80) != 0)) &&
         (WPA_ExtractSuiteFromRSNIE(param_3,param_4,4,&local_19), bVar2 = local_1a, local_19 != '\0'
         )) {
        if (-1 < DebugLevel) {
          printk("[ERROR]%s : invalid PMKID !!!\n","WPAValidateRSNIE");
        }
        return 1;
      }
      goto LAB_0011bf84;
    }
  }
  else {
    iVar1 = WPACheckGroupCipher(param_1,param_2,param_3);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0x29;
      }
      printk("[ERROR]%s : invalid group cipher !!!\n","WPAValidateRSNIE");
      return 0x29;
    }
    bVar2 = local_1a;
    if (local_1a == 0) goto LAB_0011bf3c;
    if (local_1a < 2) goto LAB_0011bf4c;
    iVar1 = WPACheckUcast(param_1,param_2,param_3);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0x2a;
      }
      printk("[ERROR]%s : invalid pairwise cipher !!!\n","WPAValidateRSNIE");
      return 0x2a;
    }
    bVar2 = local_1a;
    if (local_1a < 2) goto LAB_0011bf4c;
    if (local_1a != 2) {
      iVar1 = WPACheckAKM(param_1,param_2,param_3);
      bVar2 = local_1a;
      if (iVar1 == 0) {
        if (DebugLevel < 0) {
          return 0x2b;
        }
        printk("[ERROR]%s : invalid AKM !!!\n","WPAValidateRSNIE");
        return 0x2b;
      }
      goto LAB_0011bf5c;
    }
  }
  if ((*param_1 & 0x40) == 0) {
    if (-1 < DebugLevel) {
      printk("[ERROR]%s : invalid AKM(peer use default akm) !!!\n","WPAValidateRSNIE");
    }
    return 0x2b;
  }
  *param_2 = *param_1;
LAB_0011bf84:
  iVar1 = PMF_RsnCapableValidation
                    (param_3,param_4,(char)param_1[0xf8],*(undefined1 *)((int)param_1 + 0x3e2),
                     *(undefined4 *)((int)param_1 + 999),bVar2,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("[PMF]%s : Invalid PMF Capability !!!\n","WPAValidateRSNIE");
    return iVar1;
  }
  return iVar1;
}

