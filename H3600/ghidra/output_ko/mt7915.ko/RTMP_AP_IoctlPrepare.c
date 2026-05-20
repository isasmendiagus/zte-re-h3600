// module: mt7915.ko
// function: RTMP_AP_IoctlPrepare @ 0x15012c
// size: 984 bytes
//

undefined4 RTMP_AP_IoctlPrepare(int *param_1,int *param_2)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined1 auStack_28 [4];
  char *local_24 [2];
  
  iVar6 = *param_1;
  local_24[0] = (char *)0x0;
  if ((param_2[2] == 0x100) && ((param_1[0x28e7e1] & 2U) == 0)) {
    if (param_2[3] == 0) {
      return 0;
    }
    iVar3 = RtPrivIoctlSetVal();
    if (iVar3 != param_2[5]) {
      return 0xffffff9c;
    }
    os_alloc_mem(param_1,local_24,param_2[4] + 1);
    if (local_24[0] == (char *)0x0) {
      return 0xfffffff4;
    }
    uVar8 = param_2[4];
    uVar9 = *(uint *)(((uint)auStack_28 & 0xffffe000) + 8);
    if (!CARRY4(param_2[3],uVar8) && param_2[3] + uVar8 <= uVar9) {
      uVar9 = 0;
    }
    if (uVar9 == 0) {
      iVar3 = __copy_from_user();
      pcVar2 = local_24[0];
      if (iVar3 != 0) {
        local_24[0][param_2[4]] = '\0';
        uVar8 = param_2[4];
joined_r0x00150410:
        local_24[0] = pcVar2;
        if (7 < uVar8) {
          os_free_mem(pcVar2);
          return 0xfffffff2;
        }
        pcVar7 = strstr(pcVar2,"OpMode");
        if (pcVar7 != (char *)0x0) {
          os_free_mem(pcVar2);
          return 0xfffffff2;
        }
        goto LAB_00150440;
      }
      local_24[0][param_2[4]] = '\0';
      uVar8 = param_2[4];
    }
    else {
      if (uVar8 != 0) {
        __memzero(local_24[0],uVar8);
        local_24[0][param_2[4]] = '\0';
        uVar8 = param_2[4];
        pcVar2 = local_24[0];
        goto joined_r0x00150410;
      }
      *local_24[0] = '\0';
      uVar8 = param_2[4];
      pcVar2 = local_24[0];
    }
    local_24[0] = pcVar2;
    if (uVar8 < 8) {
      pcVar7 = strstr(pcVar2,"OpMode");
      if (pcVar7 == (char *)0x0) {
LAB_00150440:
        os_free_mem(pcVar2);
        return 0xffffff9c;
      }
      os_free_mem(pcVar2);
    }
    else {
      os_free_mem(pcVar2);
    }
  }
  iVar3 = 0;
  *(undefined4 *)(iVar6 + 0x40) = 0;
  iVar4 = param_2[2];
  if (iVar4 == 0x100) {
    *(undefined4 *)(iVar6 + 0x38) = 0x100;
    *(undefined4 *)(iVar6 + 0x3c) = 0;
    *(int **)(iVar6 + 0x40) = param_1 + 0xadc9d;
  }
  else if (iVar4 == 0x200) {
    *(undefined4 *)(iVar6 + 0x38) = 0x200;
    pcVar7 = (char *)param_2[6];
    pcVar2 = (char *)RtmpOsGetNetDevName(param_1[1]);
    iVar3 = strcmp(pcVar7,pcVar2);
    if (iVar3 == 0) {
      *(undefined4 *)(iVar6 + 0x3c) = 0;
      iVar3 = 0;
    }
    else {
      uVar8 = (uint)*(byte *)((int)param_1 + 0x2b7242);
      if (uVar8 < 2) {
        uVar9 = 1;
      }
      else {
        if (param_1[0xaf29f] == *param_2) {
          uVar10 = 1;
          uVar9 = 1;
        }
        else {
          piVar5 = param_1 + 0xb08ac;
          uVar1 = 2;
          do {
            uVar10 = uVar1;
            uVar9 = uVar10 & 0xffff;
            if (uVar10 == (uVar8 - 2 & 0xffff) + 2) goto LAB_00150334;
            iVar3 = *piVar5;
            piVar5 = piVar5 + 0x160d;
            uVar1 = uVar10 + 1;
          } while (*param_2 != iVar3);
        }
        *(uint *)(iVar6 + 0x3c) = uVar10;
        *(int **)(iVar6 + 0x40) = param_1 + uVar10 * 0x160d + 0xadc9d;
        uVar8 = (uint)*(byte *)((int)param_1 + 0x2b7242);
      }
LAB_00150334:
      if (uVar9 == uVar8) {
        return 0xffffff9c;
      }
      iVar3 = *(int *)(iVar6 + 0x3c);
    }
    iVar4 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    if ((iVar4 <= iVar3) || (iVar3 = *(int *)(iVar6 + 0x3c), 0x1f < iVar3)) {
      if (-1 < DebugLevel) {
        printk("%s> Error! apidx = %d > MAX_MBSSID_NUM!\n","RTMP_AP_IoctlPrepare",
               *(undefined4 *)(iVar6 + 0x3c));
      }
      iVar3 = 0;
      *(undefined4 *)(iVar6 + 0x3c) = 0;
    }
  }
  else {
    if (iVar4 != 0x400) {
      return 0xffffffa1;
    }
    *(undefined4 *)(iVar6 + 0x38) = 0x400;
    if (param_1[0xdb6d6] == *param_2) {
      iVar3 = 0;
    }
    else {
      if (*param_2 != param_1[0x1604c2]) {
        iVar3 = *(int *)(iVar6 + 0x3c);
        if (1 < iVar3) {
          *(undefined4 *)(iVar6 + 0x3c) = 0;
          if (DebugLevel < 0) {
            iVar3 = 0;
          }
          else {
            printk("%s> Error! apcli-idx > MAX_APCLI_NUM!\n","RTMP_AP_IoctlPrepare");
            iVar3 = *(int *)(iVar6 + 0x3c);
          }
        }
        goto LAB_001501d0;
      }
      iVar3 = 1;
    }
    *(int *)(iVar6 + 0x3c) = iVar3;
    *(int **)(iVar6 + 0x40) = param_1 + iVar3 * 0x84dec + 0xdb6e1;
  }
LAB_001501d0:
  param_2[7] = iVar3;
  return 0;
}

