// module: wlan_debug_module.ko
// function: IPv6ToStr @ 0x12b4c
// size: 644 bytes
//

undefined4 IPv6ToStr(int param_1,char *param_2,uint param_3)

{
  ushort *puVar1;
  bool bVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  char *__s;
  int iVar9;
  bool bVar10;
  bool bVar11;
  short sStack_68;
  ushort local_66 [8];
  char local_56 [46];
  undefined1 auStack_28 [4];
  
  if (param_1 != 0 && (param_2 != (char *)0x0 && 4 < param_3)) {
    __memzero(local_66,0x10);
    iVar8 = 0;
    do {
      iVar3 = iVar8 + 2;
      *(ushort *)((int)local_66 + iVar8) =
           CONCAT11(*(undefined1 *)(param_1 + iVar8),((undefined1 *)(param_1 + iVar8))[1]);
      iVar8 = iVar3;
    } while (iVar3 != 0x10);
    psVar6 = &sStack_68;
    iVar9 = 0;
    iVar7 = 0;
    iVar8 = -1;
    iVar3 = -1;
    iVar5 = 0;
LAB_00012c04:
    do {
      psVar6 = psVar6 + 1;
      if (*psVar6 == 0) {
        iVar9 = iVar9 + 1;
        if (iVar3 == -1) {
          iVar9 = 1;
          iVar3 = iVar7;
        }
      }
      else if (iVar3 != -1) {
        if (iVar5 < iVar9 || iVar8 == -1) {
          iVar7 = iVar7 + 1;
          iVar8 = iVar3;
          iVar3 = -1;
          iVar5 = iVar9;
          if (iVar7 == 8) break;
          goto LAB_00012c04;
        }
        iVar3 = -1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 8);
    if ((iVar3 == -1) || ((iVar8 != -1 && (iVar9 <= iVar5)))) {
      iVar3 = iVar8;
      iVar9 = iVar5;
    }
    bVar11 = SCARRY4(iVar3,1);
    iVar8 = iVar3 + 1;
    bVar10 = iVar3 == -1;
    if (!bVar10) {
      bVar11 = SBORROW4(iVar9,1);
      iVar8 = iVar9 + -1;
    }
    if ((bVar10 || iVar9 == 1) || iVar8 < 0 != bVar11) {
      iVar3 = -1;
    }
    bVar2 = false;
    if (((!bVar10 && iVar9 != 1) && iVar8 < 0 == bVar11) && (bVar2 = false, iVar3 != -1)) {
      bVar2 = true;
    }
    iVar8 = 0;
    __s = local_56;
    do {
      while( true ) {
        bVar11 = bVar2;
        if (iVar8 < iVar3) {
          bVar11 = false;
        }
        if ((bVar11) && (iVar8 < iVar9 + iVar3)) break;
        if (iVar8 != 0) {
          *__s = ':';
          __s = __s + 1;
          if ((iVar8 == 6 && iVar3 == 0) && ((iVar9 == 6 || ((iVar9 == 5 && (local_66[5] == -1))))))
          {
            iVar8 = IPToStr(param_1 + 0xc,__s,(uint)(auStack_28 + -(int)__s) & 0xffff);
            if (iVar8 == 0) {
              return 0;
            }
            sVar4 = strlen(__s);
            __s = __s + sVar4;
            goto LAB_00012d80;
          }
        }
        puVar1 = local_66 + iVar8;
        iVar8 = iVar8 + 1;
        iVar5 = sprintf(__s,"%x",(uint)*puVar1);
        __s = __s + iVar5;
        if (iVar8 == 8) goto LAB_00012d78;
      }
      bVar11 = iVar3 == iVar8;
      iVar8 = iVar8 + 1;
      if (bVar11) {
        *__s = ':';
        __s = __s + 1;
      }
    } while (iVar8 != 8);
LAB_00012d78:
    if (bVar2) {
LAB_00012d80:
      if (iVar9 + iVar3 == 8) {
        *__s = ':';
        __s = __s + 1;
      }
    }
    *__s = '\0';
    if (((uint)(__s + (1 - (int)local_56)) & 0xffff) <= param_3) {
      strncpy(param_2,local_56,param_3);
      return 1;
    }
  }
  return 0;
}

