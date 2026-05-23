// module: mt7915.ko
// function: RTMPAPPrivIoctlSet @ 0x3596c
// size: 688 bytes
//

undefined4 RTMPAPPrivIoctlSet(undefined4 param_1,int param_2)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  char *__s;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  undefined4 uVar9;
  undefined4 local_38;
  undefined **local_34;
  char *local_30;
  char *local_2c [2];
  
  local_2c[0] = (char *)0x0;
  local_30 = (char *)0x0;
  os_alloc_mem(0,local_2c,*(ushort *)(param_2 + 0x14) + 1);
  if (local_2c[0] == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar6 = (uint)*(ushort *)(param_2 + 0x14);
  uVar7 = *(uint *)(((uint)&local_38 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar6) && *(uint *)(param_2 + 0x10) + uVar6 <= uVar7) {
    uVar7 = 0;
  }
  if (uVar7 == 0) {
    iVar5 = __copy_from_user();
    if (iVar5 == 0) {
      uVar7 = (uint)*(ushort *)(param_2 + 0x14);
      goto LAB_000359dc;
    }
  }
  else {
    uVar7 = 0;
    if (uVar6 == 0) {
LAB_000359dc:
      bVar3 = false;
      local_2c[0][uVar7] = '\0';
      uVar9 = 3;
      local_38 = 0;
      local_30 = local_2c[0];
      local_34 = &_LANCHOR3;
LAB_00035a0c:
      do {
        __s = strsep(&local_30,"");
        if (__s == (char *)0x0) {
LAB_00035bd0:
          os_free_mem(local_2c[0]);
          return local_38;
        }
      } while (*__s == '\0');
      pcVar4 = strchr(__s,0x3d);
      if (pcVar4 == (char *)0x0) {
LAB_00035b44:
        iVar5 = strcmp(__s,"WscStop");
        if (((iVar5 != 0) && (iVar5 = strcmp(__s,"ser"), iVar5 != 0)) &&
           (iVar5 = strcmp(__s,"WscGenPinCode"), iVar5 != 0)) goto LAB_00035a0c;
        pcVar8 = (char *)0x0;
      }
      else {
        pcVar8 = pcVar4 + 1;
        *pcVar4 = '\0';
        if (pcVar8 == (char *)0x0) goto LAB_00035b44;
        if ((pcVar4[1] == '\0') && (iVar5 = strcmp(__s,"AutoChannelSkip"), iVar5 != 0)) {
          bVar3 = true;
          uVar9 = 0;
        }
      }
      iVar5 = get_proc(param_1,__s,uVar9,1);
      bVar2 = bVar3;
      if (iVar5 != 0) {
        bVar2 = false;
      }
      if (bVar2) goto LAB_00035bd0;
      DAT_005f1848 = &DAT_0032b924;
      if (local_34[-0x295] != (undefined *)0x0) {
        while (iVar5 = rtstrcasecmp(__s), iVar5 != 1) {
          piVar1 = DAT_005f1848 + 2;
          DAT_005f1848 = DAT_005f1848 + 2;
          if (*piVar1 == 0) goto LAB_00035b98;
        }
        iVar5 = (*(code *)DAT_005f1848[1])(param_1,pcVar8);
        if (iVar5 == 0) {
          local_38 = 0xffffffea;
        }
        if (*DAT_005f1848 != 0) {
          if ((pcVar8 != (char *)0x0) && (*pcVar8 != '\0')) {
            get_proc(param_1,__s,3,0);
            uVar9 = 3;
          }
          goto LAB_00035a0c;
        }
      }
LAB_00035b98:
      if (DebugLevel < 3) {
        local_38 = 0xffffffea;
      }
      else {
        printk("IOCTL::(iwpriv) Command not Support [%s=%s]\n",__s,pcVar8);
        local_38 = 0xffffffea;
      }
      goto LAB_00035bd0;
    }
    __memzero(local_2c[0],uVar6);
  }
  os_free_mem(local_2c[0]);
  return 0xfffffff2;
}

