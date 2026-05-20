// module: mt7915.ko
// function: STAMlmePeriodicExec @ 0x130090
// size: 1416 bytes
//

void STAMlmePeriodicExec(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  int *piVar6;
  undefined4 *__s1;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 == 0) {
    printk(&_LC14,0x9c7);
    dump_stack();
    return;
  }
  if (*(short *)(iVar1 + 0x2124a4) != 0) {
    *(short *)(iVar1 + 0x2124a4) = *(short *)(iVar1 + 0x2124a4) + -1;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x84) != (code *)0x0) {
    (**(code **)(iVar2 + 0x84))(param_1,iVar1 + 0x2131c8);
  }
  if (*(char *)(iVar1 + 0x2127b8) == '\0') {
    if ((*(byte *)(param_1 + 0xa77bcf) & 2) != 0) goto LAB_00130330;
LAB_00130124:
    if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
      hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    }
    uVar4 = *(uint *)(iVar1 + 0x212464);
  }
  else {
    if ((*(int *)(iVar1 + 0x2127b0) + 6000) - *(int *)(param_1 + 0x7960e8) < 0) {
      *(undefined1 *)(iVar1 + 0x2127b8) = 0;
    }
    if ((*(byte *)(param_1 + 0xa77bcf) & 2) == 0) goto LAB_00130124;
LAB_00130330:
    if (*(char *)(param_1 + 0xa77bd0) != '\x01') goto LAB_00130124;
    __s1 = (undefined4 *)(param_1 + 0x794b5b);
    iVar2 = memcmp(__s1,(undefined4 *)(param_1 + 0xa77bc9),6);
    if (iVar2 == 0) goto LAB_00130124;
    uVar4 = *(uint *)(iVar1 + 0x212464);
    if ((uVar4 & 1) != 0) {
      if (*(char *)(iVar1 + 0x4139) != '\0') {
        __memzero((void *)(param_1 + 0xa77bd1),0x20);
        memmove((void *)(param_1 + 0xa77bd1),(void *)(iVar1 + 0x4119),
                (uint)*(byte *)(iVar1 + 0x4139));
        *(undefined1 *)(param_1 + 0xa77bf1) = *(undefined1 *)(iVar1 + 0x4139);
      }
      BN_mod_lshift1[iVar1] = (code)0x1;
      __cntl_disconnect_request(param_2,1,iVar1 + 0x212428,8,"STAMlmePeriodicExec",0x9f9);
      goto LAB_00130124;
    }
    if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
      *__s1 = *(undefined4 *)(param_1 + 0xa77bc9);
      *(undefined2 *)(param_1 + 0x794b5f) = *(undefined2 *)(param_1 + 0xa77bcd);
      memmove((void *)(param_2 + 0x1b),__s1,6);
      wdev_attr_update(param_1,param_2);
      if (2 < DebugLevel) {
        printk("Write EthCloneMac to ASIC: =%02x:%02x:%02x:%02x:%02x:%02x\n",
               *(undefined1 *)(param_1 + 0x794b5b),*(undefined1 *)(param_1 + 0x794b5c),
               *(undefined1 *)(param_1 + 0x794b5d),*(undefined1 *)(param_1 + 0x794b5e),
               *(undefined1 *)(param_1 + 0x794b5f),*(undefined1 *)(param_1 + 0x794b60));
      }
      if (*(byte *)(param_1 + 0xa77bf1) != 0) {
        memmove((void *)(iVar1 + 0x4140),(void *)(param_1 + 0xa77bd1),
                (uint)*(byte *)(param_1 + 0xa77bf1));
        *(undefined1 *)(iVar1 + 0x4160) = *(undefined1 *)(param_1 + 0xa77bf1);
        memmove((void *)(iVar1 + 0x4119),(void *)(param_1 + 0xa77bd1),
                (uint)*(byte *)(param_1 + 0xa77bf1));
        *(undefined1 *)(iVar1 + 0x4139) = *(undefined1 *)(param_1 + 0xa77bf1);
      }
      goto LAB_00130124;
    }
  }
  iVar2 = *(int *)(param_1 + 0xa39e24) + *(int *)(param_1 + 0xa39e20) + *(int *)(param_1 + 0xa39e1c)
  ;
  if ((uVar4 & 0x80) == 0) {
LAB_0013019c:
    if ((*(uint *)(param_1 + 0xa39f84) & 0x4000) == 0) {
LAB_00130474:
      iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(code **)(iVar3 + 0x6c) != (code *)0x0) {
        (**(code **)(iVar3 + 0x6c))(param_1);
      }
      iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(code **)(iVar3 + 0x80) != (code *)0x0) {
        (**(code **)(iVar3 + 0x80))(param_1);
        *(int *)(param_1 + 0xa39e80) = iVar2;
        uVar4 = *(uint *)(iVar1 + 0x212464);
        goto joined_r0x001304b8;
      }
    }
  }
  else if ((*(uint *)(param_1 + 0xa39f84) & 0x4000) == 0) {
    if (*(char *)(param_2 + 0xbb4) == '\0') {
      iVar3 = GetAssociatedAPByWdev(param_1,param_2);
      if (iVar3 != 0) {
        MlmeCalculateChannelQuality(param_1,iVar3,*(undefined4 *)(param_1 + 0x7960e8));
      }
      goto LAB_0013019c;
    }
    goto LAB_00130474;
  }
  *(int *)(param_1 + 0xa39e80) = iVar2;
  uVar4 = *(uint *)(iVar1 + 0x212464);
joined_r0x001304b8:
  if ((uVar4 & 1) == 0) {
    if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
      if (((((*(char *)(iVar1 + 0x213175) == '\0') ||
            ((*(int *)(iVar1 + 0x212804) + 3000) - *(int *)(param_1 + 0x7960e8) < 0)) &&
           (*(undefined1 *)(iVar1 + 0x213175) = 0, *(char *)(iVar1 + 0x213171) == '\x01')) &&
          ((iVar2 = IsHcRadioCurStatOffByWdev(iVar1), iVar2 == 0 &&
           ((*(uint *)(param_1 + 0xa39f84) & 0x10000000) != 0)))) &&
         (uVar4 = (uint)*(byte *)(iVar1 + 0x4160), uVar4 < 0x21)) {
        if (uVar4 == 0) {
LAB_001302dc:
          if (*(char *)(iVar1 + 0x1a) != '\0') {
            uVar4 = *(uint *)(param_1 + 0x82921c);
            if (uVar4 == (uVar4 / 3) * 3) {
              MlmeAutoReconnectLastSSID(param_1,iVar1,uVar4 * -0x55555555);
            }
          }
        }
        else if (0x1f < *(byte *)(iVar1 + 0x4140)) {
          pbVar5 = (byte *)(iVar1 + 0x4140);
          do {
            if (pbVar5 == (byte *)(iVar1 + uVar4 + 0x413f)) goto LAB_001302dc;
            pbVar5 = pbVar5 + 1;
          } while (0x1f < *pbVar5);
        }
      }
    }
    else {
      piVar6 = (int *)(param_1 + 0xa1d20);
      iVar2 = 0;
      while( true ) {
        iVar3 = HcGetMaxStaNum(param_1);
        if (iVar3 <= iVar2) break;
        if ((*piVar6 == 0x20001) && ((800 - *(int *)(param_1 + 0x7960e8)) + piVar6[0x47a] < 0)) {
          __MlmeDeAuthAction(param_1,piVar6,8,0,"STAMlmePeriodicExec",0xa78);
        }
        piVar6 = piVar6 + 0x530;
        iVar2 = iVar2 + 1;
      }
      if (*(short *)(param_1 + 0x285920) == 0) {
        *(uint *)(iVar1 + 0x212464) = *(uint *)(iVar1 + 0x212464) & 0xffffff7f;
        RTMP_IndicateMediaState(param_1);
      }
    }
  }
  if (*(char *)(param_1 + 0x79504c) != '\0') {
    sta_2040_coex_scan_check(param_1,param_2);
    return;
  }
  return;
}

