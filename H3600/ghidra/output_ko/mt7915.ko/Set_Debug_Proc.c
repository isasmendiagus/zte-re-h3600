// module: mt7915.ko
// function: Set_Debug_Proc @ 0xda464
// size: 1352 bytes
//

undefined4 Set_Debug_Proc(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  char cVar9;
  uint uVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined1 *puVar13;
  int *piVar14;
  char *local_24 [2];
  
  local_24[0] = param_2;
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) goto LAB_000da6d4;
  pcVar1 = strsep(local_24,":");
  if (local_24[0] == (char *)0x0) {
    iVar3 = rtstrcasecmp(pcVar1,&_LC233);
    uVar4 = os_str_tol(pcVar1,0,10);
    if (iVar3 == 1) goto LAB_000da7a8;
    iVar3 = 1;
    uVar5 = 0;
    uVar6 = 0;
    cVar9 = '\0';
  }
  else {
    pcVar2 = strsep(local_24,":");
    if (local_24[0] == (char *)0x0) {
      iVar3 = rtstrcasecmp(pcVar2,&_LC233);
      if (iVar3 == 1) {
        cVar9 = '\x02';
      }
      else {
        cVar9 = '\0';
      }
      uVar4 = os_str_tol(pcVar1,0,10);
      uVar5 = os_str_tol(pcVar2,0,10);
      iVar3 = 2;
      uVar6 = 0;
    }
    else {
      iVar3 = rtstrcasecmp(local_24[0],&_LC233);
      if (iVar3 == 1) {
        cVar9 = '\x03';
      }
      else {
        cVar9 = '\0';
      }
      uVar4 = os_str_tol(pcVar1,0,10);
      uVar5 = os_str_tol(pcVar2,0,10);
      uVar6 = os_str_tol(local_24[0],0,10);
      iVar3 = 3;
    }
    if (cVar9 == '\x01') {
LAB_000da7a8:
      piVar14 = (int *)0x2956b4;
      printk("usage and current state:\n");
      puVar13 = DebugSubCategory;
      uVar4 = 0;
      do {
        piVar14 = piVar14 + 1;
        if (*piVar14 == 0) break;
        iVar3 = 6;
        do {
          if (*(int *)(puVar13 + iVar3 * 0x80) != 0) {
            printk("%2d:%s(L%d",uVar4,*piVar14,iVar3);
            if (*(int *)(DebugSubCategory + (uVar4 + iVar3 * 0x20) * 4) != -1) {
              printk(&_LC236);
            }
            printk(&_LC237);
            break;
          }
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        uVar4 = uVar4 + 1;
        if ((uVar4 & 3) == 0) {
          printk(&_LC22);
        }
        puVar13 = puVar13 + 4;
      } while (uVar4 != 0x20);
      goto LAB_000da804;
    }
    if (cVar9 == '\x02') {
      piVar14 = (int *)0x2956b4;
      printk("usage and current state for DebugLevel %d:\n",uVar4);
      puVar8 = (undefined4 *)(&TYPEIPV6 + uVar4 * 0x40);
      uVar4 = 0;
      do {
        piVar14 = piVar14 + 1;
        if (*piVar14 == 0) break;
        puVar8 = puVar8 + 1;
        uVar5 = uVar4 + 1;
        printk("%2d:%s(0x%08x)\t",uVar4,*piVar14,*puVar8);
        if ((uVar5 & 3) == 0) {
          printk(&_LC22);
        }
        uVar4 = uVar5;
      } while (uVar5 != 0x20);
      goto LAB_000da804;
    }
  }
  if (cVar9 == '\x03') {
    printk("usage and current state for DebugLevel %d, Category %d(%s):\n",uVar4,uVar5,
           (&DAT_002956b8)[uVar5]);
    piVar14 = (int *)(&UNK_00295734 + uVar5 * 0x80);
    uVar6 = 0;
    do {
      piVar14 = piVar14 + 1;
      if (*piVar14 == 0) break;
      printk("%2d:%s(",uVar6);
      pcVar1 = "off)\t";
      uVar11 = uVar6 & 0xff;
      uVar6 = uVar6 + 1;
      if ((*(uint *)(DebugSubCategory + (uVar5 + uVar4 * 0x20) * 4) & 1 << uVar11) != 0) {
        pcVar1 = "on)\t";
      }
      printk(pcVar1);
      if ((uVar6 & 3) == 0) {
        printk(&_LC22);
      }
    } while (uVar6 != 0x20);
LAB_000da804:
    printk(&_LC22);
    return 1;
  }
  if (6 < uVar4) goto LAB_000da6d4;
  if (iVar3 == 1) {
    puVar8 = (undefined4 *)&TYPEIPV6;
    uVar5 = 0;
    DebugLevel = uVar4;
    do {
      puVar7 = puVar8 + 0x20;
      if (uVar4 < uVar5) {
        uVar12 = 0;
      }
      else {
        uVar12 = 0xffffffff;
      }
      do {
        puVar8 = puVar8 + 1;
        *puVar8 = uVar12;
      } while (puVar8 != puVar7);
      uVar5 = uVar5 + 1;
      uVar6 = uVar4;
    } while (uVar5 != 7);
  }
  else if (iVar3 == 2) {
    if (0x1f < uVar5) goto LAB_000da6d4;
    uVar11 = 0;
    do {
      if (uVar4 < uVar11) {
        uVar12 = 0;
      }
      else {
        uVar12 = 0xffffffff;
      }
      printk("%s(): change cat%d(level %d) from %x to ","Set_Debug_Proc",uVar5,uVar11,
             *(undefined4 *)(DebugSubCategory + uVar11 * 0x80 + uVar5 * 4));
      *(undefined4 *)(DebugSubCategory + uVar11 * 0x80 + uVar5 * 4) = uVar12;
      uVar11 = uVar11 + 1;
      printk(&_LC245,uVar12);
      uVar6 = DebugLevel;
    } while (uVar11 != 7);
  }
  else {
    if (0x1f < uVar6) {
LAB_000da6d4:
      printk("Format error! correct format:\n");
      printk("iwpriv ra0 set Debug=[DebugLevel]:[DebugCat]:[DebugSubCat]\n");
      printk("\t[DebugLevel]:0~6 or ?\n");
      printk("\t[DebugCat]:0~31 or ?, optional\n");
      printk("\t[DebugSubCat]:0~31 or ?, optional\n");
      printk("EX: 1.iwpriv ra0 set Debug=2\n");
      printk("\t DebugSubCategory[0~2][0~31] = 0xffffffff, DebugSubCategory[3~6][0~31] = 0\n");
      printk("    2.iwpriv ra0 set Debug=4:5\n");
      printk("\t DebugSubCategory[0~4][5] = 0xffffffff, DebugSubCategory[5~6][5] = 0\n");
      printk("    3.iwpriv ra0 set Debug=3:10:7\n");
      printk(
            "\t DebugSubCategory[0~3][10] |= (0x1 << 7), DebugSubCategory[4~6][10] &= ~(0x1 << 7)\n"
            );
      printk("    4.iwpriv ra0 set Debug=?\n");
      printk("\t query category list and current debuglevel value for each category\n");
      printk("    5.iwpriv ra0 set Debug=3:?\n");
      printk(
            "\t query category list and current subcategory bitmap value for each category at DebugLevel 3\n"
            );
      printk("    6.iwpriv ra0 set Debug=2:8:?\n");
      printk(
            "\t query subcategory list and current subcategory on/off state for category 8 at DebugLevel 2\n"
            );
      return 0;
    }
    uVar11 = 1 << (uVar6 & 0xff);
    uVar10 = 0;
    do {
      printk("%s(): change cat%d(level %d) from %x to ","Set_Debug_Proc",uVar5,uVar10,
             *(undefined4 *)(DebugSubCategory + uVar10 * 0x80 + uVar5 * 4));
      uVar6 = *(uint *)(DebugSubCategory + uVar10 * 0x80 + uVar5 * 4);
      if (uVar4 < uVar10) {
        uVar6 = uVar6 & ~uVar11;
      }
      else {
        uVar6 = uVar11 | uVar6;
      }
      *(uint *)(DebugSubCategory + uVar10 * 0x80 + uVar5 * 4) = uVar6;
      uVar10 = uVar10 + 1;
      printk(&_LC245);
      uVar6 = DebugLevel;
    } while (uVar10 != 7);
  }
  printk("%s(): (DebugLevel = %d)\n","Set_Debug_Proc",uVar6);
  return 1;
}

