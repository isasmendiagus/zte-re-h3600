// module: mt7915.ko
// function: ATEManualParsingParam @ 0x264950
// size: 6524 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 ATEManualParsingParam(int *param_1,char *param_2,char *param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  byte *__s;
  uint uVar6;
  undefined4 uVar7;
  byte bVar8;
  undefined1 uVar9;
  undefined2 uVar10;
  uint uVar11;
  char *pcVar12;
  char cVar13;
  uint uVar14;
  bool bVar15;
  bool bVar16;
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  local_2e = 0;
  local_2a = 0;
  if (iVar2 == 0 || (param_3 == (char *)0x0 || param_2 == (char *)0x0)) {
    return 0;
  }
  iVar3 = strcmp("mac",param_2);
  if (iVar3 == 0) {
    local_30 = 0x3a;
    sVar4 = strlen(param_3);
    if ((0x10 < sVar4) && (__s = (byte *)rstrtok(param_3,&local_30), __s != (byte *)0x0)) {
      iVar3 = 0;
      do {
        sVar4 = strlen((char *)__s);
        iVar5 = (int)&local_2e + iVar3;
        iVar3 = iVar3 + 1;
        if (((sVar4 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        break;
        AtoH(__s,iVar5);
        __s = (byte *)rstrtok(0,&local_30);
        if (__s == (byte *)0x0) {
          if (iVar3 == 6) {
            if (DebugLevel < 1) goto LAB_0026512c;
            uVar11 = local_2e >> 0x18;
            uVar14 = (uint)(byte)local_2a;
            uVar6 = (uint)local_2a._1_1_;
            printk("\n%02x:%02x:%02x:%02x:%02x:%02x\n",(undefined1)local_2e,local_2e._1_1_,
                   local_2e._2_1_,uVar11,uVar14,uVar6);
            if (DebugLevel < 3) goto LAB_0026512c;
            printk("\t%s: Invalid MAC address(%s), use default\n","ATEManualParsingParam",param_3,
                   DebugLevel,uVar11,uVar14,uVar6);
            goto LAB_00265a64;
          }
          break;
        }
      } while (iVar3 != 7);
    }
    __memzero(&local_2e,6);
    if (DebugLevel < 3) {
LAB_0026512c:
      param_1[0x29e195] = local_2e;
      *(undefined2 *)(param_1 + 0x29e196) = local_2a;
    }
    else {
      printk("\t%s Invalid MAC address(%s), use default\n","ATEManualParsingParam",param_3);
LAB_00265a64:
      iVar3 = DebugLevel;
      param_1[0x29e195] = local_2e;
      *(undefined2 *)(param_1 + 0x29e196) = local_2a;
      if (2 < iVar3) {
        printk("%s: MAC=%02x:%02x:%02x:%02x:%02x:%02x\n","ATEManualParsingParam",
               (undefined1)local_2e,local_2e._1_1_,local_2e._2_1_,local_2e._3_1_,(byte)local_2a,
               local_2a._1_1_);
      }
    }
  }
  iVar3 = strcmp("type",param_2);
  if (iVar3 == 0) {
    iVar3 = strcmp(param_3,"ap");
    if (iVar3 == 0) {
      uVar9 = 1;
    }
    else {
      iVar3 = strcmp(param_3,"sta");
      if (iVar3 == 0) {
        uVar9 = 0;
      }
      else {
        if (DebugLevel < 3) {
          *(undefined1 *)((int)param_1 + 0xa7865b) = 0;
          goto LAB_00264a18;
        }
        printk("\t%s: Invalid type(%s), use default\n","ATEManualParsingParam",param_3);
        uVar9 = 0;
      }
    }
    iVar3 = DebugLevel;
    *(undefined1 *)((int)param_1 + 0xa7865b) = uVar9;
    if (2 < iVar3) {
      printk("%s: TYPE=%d\n","ATEManualParsingParam",uVar9);
    }
  }
LAB_00264a18:
  iVar3 = strcmp("wtbl",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
LAB_00264a50:
        *(undefined1 *)((int)param_1 + 0xa7865d) = 1;
        goto LAB_00264a60;
      }
      printk("\t%s: Invalid wtbl idx(%s), use default\n","ATEManualParsingParam",param_3);
      uVar6 = 1;
      uVar11 = uVar6;
    }
    else {
      uVar11 = simple_strtol(param_3,0,10);
      if (uVar11 - 1 < 0x7f) {
        uVar6 = uVar11 & 0xff;
      }
      else {
        if (DebugLevel < 3) goto LAB_00264a50;
        printk("\t%s: Invalid wtbl idx(%s), use default\n","ATEManualParsingParam",param_3);
        uVar6 = 1;
        uVar11 = 1;
      }
    }
    iVar3 = DebugLevel;
    *(char *)((int)param_1 + 0xa7865d) = (char)uVar6;
    if (2 < iVar3) {
      printk("%s: WTBL_IDX=%d\n","ATEManualParsingParam",uVar11);
    }
  }
LAB_00264a60:
  iVar3 = strcmp("ownmac",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      uVar9 = 0;
      if (DebugLevel < 3) {
LAB_00264a98:
        *(undefined1 *)(param_1 + 0x29e197) = uVar9;
        goto LAB_00264aa4;
      }
      printk("\t%s: Invalid wtbl idx(%s), use default\n","ATEManualParsingParam",param_3);
      uVar11 = 0;
      uVar9 = 0;
    }
    else {
      uVar11 = simple_strtol(param_3,0,10);
      uVar6 = uVar11 - 0x10;
      bVar16 = 0xe < uVar6;
      bVar15 = uVar6 == 0xf;
      if (0xf < uVar6) {
        bVar16 = 3 < uVar11;
        bVar15 = uVar11 == 4;
      }
      if (bVar16 && !bVar15) {
        if (DebugLevel < 3) {
          uVar9 = 1;
          goto LAB_00264a98;
        }
        uVar9 = 1;
        printk("\t%s: Invalid OwnMac idx(%s), use default\n","ATEManualParsingParam",param_3);
        uVar11 = 1;
      }
      else {
        uVar9 = (undefined1)uVar11;
      }
    }
    iVar3 = DebugLevel;
    *(undefined1 *)(param_1 + 0x29e197) = uVar9;
    if (2 < iVar3) {
      printk("%s: OWN_MAC_IDX=%d\n","ATEManualParsingParam",uVar11);
    }
  }
LAB_00264aa4:
  iVar3 = strcmp("pfmuId",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        *(undefined2 *)((int)param_1 + 0xa78662) = 0;
        goto LAB_00264aec;
      }
      printk("\t%s: Invalid PFMU idx(%s), use default\n","ATEManualParsingParam",param_3);
      uVar7 = 0;
      uVar10 = 0;
    }
    else {
      uVar7 = simple_strtol(param_3,0,10);
      uVar10 = (undefined2)uVar7;
    }
    iVar3 = DebugLevel;
    *(undefined2 *)((int)param_1 + 0xa78662) = uVar10;
    if (2 < iVar3) {
      printk("%s: PFMU_IDX=%d\n","ATEManualParsingParam",uVar7);
    }
  }
LAB_00264aec:
  iVar3 = strcmp("aid",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        *(undefined2 *)((int)param_1 + 0xa78666) = 0;
        goto LAB_00264b34;
      }
      printk("\t%s: Invalid aid(%s), use default\n","ATEManualParsingParam",param_3);
      uVar7 = 0;
      uVar10 = 0;
    }
    else {
      uVar7 = simple_strtol(param_3,0,10);
      uVar10 = (undefined2)uVar7;
    }
    iVar3 = DebugLevel;
    *(undefined2 *)((int)param_1 + 0xa78666) = uVar10;
    if (2 < iVar3) {
      printk("%s: AID =%d\n","ATEManualParsingParam",uVar7);
    }
  }
LAB_00264b34:
  iVar3 = strcmp("speIdx",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        *(undefined1 *)(param_1 + 0x29e199) = 0x18;
        goto LAB_00264b7c;
      }
      printk("\t%s: Invalid SPE idx(%s), use default\n","ATEManualParsingParam",param_3);
      uVar6 = 0x18;
      uVar11 = uVar6;
    }
    else {
      uVar11 = simple_strtol(param_3,0,10);
      uVar6 = uVar11 & 0xff;
    }
    iVar3 = DebugLevel;
    *(char *)(param_1 + 0x29e199) = (char)uVar6;
    if (2 < iVar3) {
      printk("%s: SPE_IDX=%d\n","ATEManualParsingParam",uVar11);
    }
  }
LAB_00264b7c:
  iVar3 = strcmp("mubfee",param_2);
  if (iVar3 == 0) {
    if ((*param_3 == '\0') || (bVar1 = simple_strtol(param_3,0,10), 1 < bVar1)) {
      if (2 < DebugLevel) {
        printk("\t%s: Invalid mubfee(%s), use default\n","ATEManualParsingParam",param_3);
      }
      uVar7 = 0;
    }
    else if (bVar1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
      *(byte *)(param_1 + 0x29e19e) = *(byte *)(param_1 + 0x29e19e) | 0x10;
    }
    if (2 < DebugLevel) {
      printk("%s: mubfee =%d\n","ATEManualParsingParam",uVar7);
    }
  }
  iVar3 = strcmp("sgi160",param_2);
  if (iVar3 == 0) {
    if ((*param_3 == '\0') || (bVar1 = simple_strtol(param_3,0,10), iVar3 = DebugLevel, 1 < bVar1))
    {
      if (2 < DebugLevel) {
        printk("\t%s: Invalid sgi160(%s), use default\n","ATEManualParsingParam",param_3);
      }
      uVar7 = 0;
      iVar3 = DebugLevel;
    }
    else if (bVar1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
      *(byte *)((int)param_1 + 0xa78676) = *(byte *)((int)param_1 + 0xa78676) | 0x40;
    }
    if (2 < iVar3) {
      printk("%s: sgi160 =%d\n","ATEManualParsingParam",uVar7);
    }
  }
  iVar3 = strcmp("sgi80",param_2);
  if (iVar3 == 0) {
    if ((*param_3 == '\0') || (bVar1 = simple_strtol(param_3,0,10), iVar3 = DebugLevel, 1 < bVar1))
    {
      if (2 < DebugLevel) {
        printk("\t%s: Invalid sgi80(%s), use default\n","ATEManualParsingParam",param_3);
      }
      uVar7 = 0;
      iVar3 = DebugLevel;
    }
    else if (bVar1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
      *(byte *)((int)param_1 + 0xa78676) = *(byte *)((int)param_1 + 0xa78676) | 0x20;
    }
    if (2 < iVar3) {
      printk("%s: sgi80 =%d\n","ATEManualParsingParam",uVar7);
    }
  }
  iVar3 = strcmp("sgi40",param_2);
  if (iVar3 == 0) {
    if ((*param_3 == '\0') || (bVar1 = simple_strtol(param_3,0,10), iVar3 = DebugLevel, 1 < bVar1))
    {
      if (2 < DebugLevel) {
        printk("\t%s: Invalid sgi40(%s), use default\n","ATEManualParsingParam",param_3);
      }
      uVar7 = 0;
      iVar3 = DebugLevel;
    }
    else if (bVar1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
      *(byte *)(param_1 + 0x29e19d) = *(byte *)(param_1 + 0x29e19d) | 0x40;
    }
    if (2 < iVar3) {
      printk("%s: sgi40 =%d\n","ATEManualParsingParam",uVar7);
    }
  }
  iVar3 = strcmp("sgi20",param_2);
  if (iVar3 == 0) {
    if ((*param_3 == '\0') || (bVar1 = simple_strtol(param_3,0,10), iVar3 = DebugLevel, 1 < bVar1))
    {
      if (2 < DebugLevel) {
        printk("\t%s: Invalid sgi20(%s), use default\n","ATEManualParsingParam",param_3);
      }
      uVar7 = 0;
      iVar3 = DebugLevel;
    }
    else if (bVar1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
      *(byte *)(param_1 + 0x29e19d) = *(byte *)(param_1 + 0x29e19d) | 0x20;
    }
    if (2 < iVar3) {
      printk("%s: sgi20 =%d\n","ATEManualParsingParam",uVar7);
    }
  }
  iVar3 = strcmp("rxmcsnss1",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        uVar11 = 0;
LAB_00264d14:
        *(byte *)((int)param_1 + 0xa7867a) =
             *(byte *)((int)param_1 + 0xa7867a) & 0xfc | (byte)uVar11;
        goto LAB_00264d28;
      }
      printk("\t%s: Invalid rxmcsnss1(%s), use default\n","ATEManualParsingParam",param_3);
      bVar1 = 0;
      uVar11 = 0;
    }
    else {
      uVar6 = simple_strtol(param_3,0,10);
      uVar11 = uVar6 & 0xff;
      if (uVar11 < 4) {
        bVar1 = (byte)uVar6 & 3;
      }
      else {
        if (DebugLevel < 3) {
          uVar11 = 3;
          goto LAB_00264d14;
        }
        printk("\t%s: Invalid rxmcsnss1(%s), use default\n","ATEManualParsingParam",param_3);
        uVar11 = 3;
        bVar1 = 3;
      }
    }
    iVar3 = DebugLevel;
    *(byte *)((int)param_1 + 0xa7867a) = *(byte *)((int)param_1 + 0xa7867a) & 0xfc | bVar1;
    if (2 < iVar3) {
      printk("%s: rxmcsnss1 =%d\n","ATEManualParsingParam",uVar11);
    }
  }
  else {
    uVar11 = 0;
  }
LAB_00264d28:
  iVar3 = strcmp("rxmcsnss2",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        uVar6 = uVar11 & 3;
LAB_00264d64:
        *(byte *)((int)param_1 + 0xa7867a) =
             *(byte *)((int)param_1 + 0xa7867a) & 0xf3 | (byte)(uVar6 << 2);
        goto LAB_00264d78;
      }
      printk("\t%s: Invalid rxmcsnss2(%s), use default\n","ATEManualParsingParam",param_3);
      uVar6 = uVar11 & 3;
    }
    else {
      uVar11 = simple_strtol(param_3,0,10);
      if ((uVar11 & 0xff) < 4) {
        uVar6 = uVar11 & 3;
        uVar11 = uVar11 & 0xff;
      }
      else {
        if (DebugLevel < 3) {
          uVar6 = 3;
          uVar11 = uVar6;
          goto LAB_00264d64;
        }
        uVar6 = 3;
        printk("\t%s: Invalid rxmcsnss2(%s), use default\n","ATEManualParsingParam",param_3);
        uVar11 = uVar6;
      }
    }
    iVar3 = DebugLevel;
    *(byte *)((int)param_1 + 0xa7867a) =
         *(byte *)((int)param_1 + 0xa7867a) & 0xf3 | (byte)(uVar6 << 2);
    if (2 < iVar3) {
      printk("%s: rxmcsnss2 =%d\n","ATEManualParsingParam",uVar11);
    }
  }
LAB_00264d78:
  iVar3 = strcmp("rxmcsnss3",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        uVar6 = uVar11 & 3;
LAB_00264db4:
        *(byte *)((int)param_1 + 0xa7867a) =
             *(byte *)((int)param_1 + 0xa7867a) & 0xcf | (byte)(uVar6 << 4);
        goto LAB_00264dc8;
      }
      printk("\t%s: Invalid rxmcsnss3(%s), use default\n","ATEManualParsingParam",param_3);
      uVar6 = uVar11 & 3;
    }
    else {
      uVar11 = simple_strtol(param_3,0,10);
      if ((uVar11 & 0xff) < 4) {
        uVar6 = uVar11 & 3;
        uVar11 = uVar11 & 0xff;
      }
      else {
        if (DebugLevel < 3) {
          uVar6 = 3;
          uVar11 = uVar6;
          goto LAB_00264db4;
        }
        uVar6 = 3;
        printk("\t%s: Invalid rxmcsnss3(%s), use default\n","ATEManualParsingParam",param_3);
        uVar11 = uVar6;
      }
    }
    iVar3 = DebugLevel;
    *(byte *)((int)param_1 + 0xa7867a) =
         *(byte *)((int)param_1 + 0xa7867a) & 0xcf | (byte)(uVar6 << 4);
    if (2 < iVar3) {
      printk("%s: rxMcsNSS3 =%d\n","ATEManualParsingParam",uVar11);
    }
  }
LAB_00264dc8:
  iVar3 = strcmp("rxmcsnss4",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        uVar11 = uVar11 & 3;
LAB_00264e04:
        *(byte *)((int)param_1 + 0xa7867a) =
             *(byte *)((int)param_1 + 0xa7867a) & 0x3f | (byte)(uVar11 << 6);
        goto LAB_00264e18;
      }
      printk("\t%s: Invalid rxmcsnss4(%s), use default\n","ATEManualParsingParam",param_3);
      uVar6 = uVar11 & 3;
    }
    else {
      uVar11 = simple_strtol(param_3,0,10);
      if ((uVar11 & 0xff) < 4) {
        uVar6 = uVar11 & 3;
        uVar11 = uVar11 & 0xff;
      }
      else {
        if (DebugLevel < 3) {
          uVar11 = 3;
          goto LAB_00264e04;
        }
        uVar6 = 3;
        printk("\t%s: Invalid rxmcsnss4(%s), use default\n","ATEManualParsingParam",param_3);
        uVar11 = uVar6;
      }
    }
    iVar3 = DebugLevel;
    *(byte *)((int)param_1 + 0xa7867a) =
         *(byte *)((int)param_1 + 0xa7867a) & 0x3f | (byte)(uVar6 << 6);
    if (2 < iVar3) {
      printk("%s rxmcsnss4 =%d\n","ATEManualParsingParam",uVar11);
    }
  }
LAB_00264e18:
  iVar3 = strcmp("subfee",param_2);
  if (iVar3 == 0) {
    if ((*param_3 == '\0') || (bVar1 = simple_strtol(param_3,0,10), 1 < bVar1)) {
      if (2 < DebugLevel) {
        printk("\t%s: Invalid subfee(%s), use default\n","ATEManualParsingParam",param_3);
      }
      uVar7 = 0;
    }
    else if (bVar1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
      *(byte *)((int)param_1 + 0xa78677) = *(byte *)((int)param_1 + 0xa78677) | 0x10;
    }
    if (2 < DebugLevel) {
      printk("%s: subfee =%d\n","ATEManualParsingParam",uVar7);
    }
  }
  iVar3 = strcmp("bfeensts",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      cVar13 = '\0';
      if (DebugLevel < 3) {
LAB_00264e94:
        *(byte *)((int)param_1 + 0xa78677) = *(byte *)((int)param_1 + 0xa78677) & 0x1f | cVar13 << 5
        ;
        goto LAB_00264ea8;
      }
      printk("\t%s: Invalid bfeensts(%s), use default\n","ATEManualParsingParam",param_3);
      bVar1 = 0;
      bVar8 = 0;
    }
    else {
      bVar1 = simple_strtol(param_3,0,10);
      if (bVar1 < 5) {
        bVar8 = bVar1 & 7;
      }
      else {
        if (DebugLevel < 3) {
          cVar13 = '\x04';
          goto LAB_00264e94;
        }
        bVar8 = 4;
        printk("\t%s: Invalid bfeensts(%s), use default\n","ATEManualParsingParam",param_3);
        bVar1 = 4;
      }
    }
    iVar3 = DebugLevel;
    *(byte *)((int)param_1 + 0xa78677) = *(byte *)((int)param_1 + 0xa78677) & 0x1f | bVar8 << 5;
    if (2 < iVar3) {
      printk("%s: bfeensts =%d\n","ATEManualParsingParam",bVar1);
    }
  }
LAB_00264ea8:
  iVar3 = strcmp("mode",param_2);
  if (iVar3 == 0) {
    cVar13 = *param_3;
    bVar1 = 0;
    iVar3 = DebugLevel;
    pcVar12 = param_3;
LAB_00264ed8:
    if (cVar13 != '\0') {
      while (cVar13 != 'b') {
        if (cVar13 == 'g') {
          cVar13 = pcVar12[1];
          if ((cVar13 == 'n') && (sVar4 = strlen(pcVar12), 1 < sVar4)) {
            cVar13 = pcVar12[2];
            bVar1 = bVar1 | 8;
            pcVar12 = pcVar12 + 2;
          }
          else {
            bVar1 = bVar1 | 4;
            pcVar12 = pcVar12 + 1;
          }
          goto LAB_00264ed8;
        }
        if (cVar13 == 'a') {
          cVar13 = pcVar12[1];
          if (cVar13 == 'n') {
            sVar4 = strlen(pcVar12);
            if (1 < sVar4) {
              cVar13 = pcVar12[2];
              bVar1 = bVar1 | 0x10;
              pcVar12 = pcVar12 + 2;
              goto LAB_00264ed8;
            }
          }
          else if ((cVar13 == 'c') && (sVar4 = strlen(pcVar12), 1 < sVar4)) {
            cVar13 = pcVar12[2];
            bVar1 = bVar1 | 0x20;
            pcVar12 = pcVar12 + 2;
            goto LAB_00264ed8;
          }
          bVar1 = bVar1 | 1;
          pcVar12 = pcVar12 + 1;
          goto LAB_00264ed8;
        }
        if (2 < iVar3) {
          printk("\t%s: Invalid phy_mode %c\n","ATEManualParsingParam");
          iVar3 = DebugLevel;
        }
        cVar13 = pcVar12[1];
        pcVar12 = pcVar12 + 1;
        if (cVar13 == '\0') goto LAB_00264f14;
      }
      cVar13 = pcVar12[1];
      bVar1 = bVar1 | 2;
      pcVar12 = pcVar12 + 1;
      goto LAB_00264ed8;
    }
LAB_00264f14:
    *(byte *)((int)param_1 + 0xa7865e) = bVar1;
    if (2 < iVar3) {
      printk("%s: phy_mode=%s, convert to PhyMode= 0x%x\n","ATEManualParsingParam",param_3,bVar1);
    }
  }
  iVar3 = strcmp("bw",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
        *(undefined1 *)((int)param_1 + 0xa7865f) = 0;
        goto LAB_00264f6c;
      }
      printk("\t%s: Invalid BW string(%s), use default!\n","ATEManualParsingParam",param_3);
      uVar9 = 0;
    }
    else {
      iVar3 = simple_strtol(param_3,0,10);
      if (iVar3 == 0x50) {
        uVar9 = 2;
      }
      else if (iVar3 == 0xa0) {
        uVar9 = 3;
      }
      else {
        uVar9 = 0;
        if (iVar3 == 0x28) {
          uVar9 = 1;
        }
      }
    }
    iVar3 = DebugLevel;
    *(undefined1 *)((int)param_1 + 0xa7865f) = uVar9;
    if (2 < iVar3) {
      printk("%s: BW=%d\n","ATEManualParsingParam",uVar9);
    }
  }
LAB_00264f6c:
  iVar3 = strcmp("nss",param_2);
  if (iVar3 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
LAB_00264fa4:
        *(undefined1 *)(param_1 + 0x29e198) = 1;
        goto LAB_00264fb4;
      }
      printk("\t%s: Invalid NSS setting, use default!\n","ATEManualParsingParam");
      uVar6 = 1;
      uVar11 = uVar6;
    }
    else {
      bVar1 = *(byte *)(param_1 + 0xa5b73) >> 4;
      uVar11 = simple_strtol(param_3,0,10);
      if (*(char *)((int)param_1 + 0x79504d) != '\0') {
        iVar2 = HcGetBandByWdev(iVar2);
        if (iVar2 == 0) {
          bVar1 = *(byte *)((int)param_1 + 0x296dce);
        }
        else {
          bVar1 = *(byte *)(param_1 + 0xa5b74);
        }
      }
      if ((int)(uint)bVar1 < (int)uVar11) {
        if (DebugLevel < 3) goto LAB_00264fa4;
        uVar6 = 1;
        printk("\t%s: Invalid NSS string(%s), use default!\n","ATEManualParsingParam",param_3);
        uVar11 = uVar6;
      }
      else {
        uVar6 = uVar11 & 0xff;
      }
    }
    iVar2 = DebugLevel;
    *(char *)(param_1 + 0x29e198) = (char)uVar6;
    if (2 < iVar2) {
      printk("%s: NSS=%d\n","ATEManualParsingParam",uVar11);
    }
  }
LAB_00264fb4:
  iVar2 = strcmp("rca2",param_2);
  if (iVar2 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
LAB_00264fec:
        *(undefined1 *)(param_1 + 0x29e19a) = 0;
        goto LAB_00264ffc;
      }
      printk("\t%s: Invalid RCA2 setting, use default!\n","ATEManualParsingParam");
      bVar1 = 0;
    }
    else {
      bVar1 = simple_strtol(param_3,0,10);
      if (1 < bVar1) {
        if (DebugLevel < 3) goto LAB_00264fec;
        printk("\t%s: Invalid RCA2 string(%s), use default!\n","ATEManualParsingParam",param_3);
        bVar1 = 0;
      }
    }
    iVar2 = DebugLevel;
    *(byte *)(param_1 + 0x29e19a) = bVar1;
    if (2 < iVar2) {
      printk("%s: RCA2=%d\n","ATEManualParsingParam");
    }
  }
LAB_00264ffc:
  iVar2 = strcmp("rv",param_2);
  if (iVar2 == 0) {
    if (*param_3 == '\0') {
      if (DebugLevel < 3) {
LAB_00265034:
        *(undefined1 *)((int)param_1 + 0xa78669) = 0;
        goto LAB_00265044;
      }
      printk("\t%s: Invalid RV setting, use default!\n","ATEManualParsingParam");
      bVar1 = 0;
    }
    else {
      bVar1 = simple_strtol(param_3,0,10);
      if (1 < bVar1) {
        if (DebugLevel < 3) goto LAB_00265034;
        printk("\t%s: Invalid RV string(%s), use default!\n","ATEManualParsingParam",param_3);
        bVar1 = 0;
      }
    }
    iVar2 = DebugLevel;
    *(byte *)((int)param_1 + 0xa78669) = bVar1;
    if (2 < iVar2) {
      printk("%s: RV=%d\n","ATEManualParsingParam");
    }
  }
LAB_00265044:
  iVar2 = strcmp("maxrate",param_2);
  if (iVar2 != 0) {
    return 1;
  }
  if (*param_3 == '\0') {
    if (2 < DebugLevel) {
      printk("\t%s: Invalid maxrate setting(%s), use default!\n","ATEManualParsingParam",param_3);
      uVar9 = 0;
      iVar2 = 0;
      iVar3 = DebugLevel;
      goto LAB_002658d8;
    }
    goto LAB_0026507c;
  }
  pcVar12 = (char *)rtstrchr(param_3,0x5f);
  if ((pcVar12 == (char *)0x0) || (sVar4 = strlen(pcVar12), sVar4 < 2)) {
    if (2 < DebugLevel) {
      iVar2 = 0;
      printk("\t%s: Invalid maxmcs setting(%s), use default!\n","ATEManualParsingParam",param_3);
      uVar9 = 0;
      iVar3 = DebugLevel;
      goto LAB_002658d8;
    }
    goto LAB_0026507c;
  }
  *pcVar12 = '\0';
  if (pcVar12[1] == '\0') {
    iVar2 = strcmp(param_3,"cck");
    iVar3 = DebugLevel;
    if (iVar2 == 0) {
      iVar2 = 0;
LAB_00265d08:
      uVar9 = 0;
      goto LAB_002658d8;
    }
    iVar2 = 0;
  }
  else {
    iVar2 = simple_strtol(pcVar12 + 1,0,10);
    if (2 < DebugLevel) {
      printk("\t%s: input MCS string(%s) =%d\n","ATEManualParsingParam",pcVar12 + 1,iVar2);
    }
    iVar3 = DebugLevel;
    iVar5 = strcmp(param_3,"cck");
    if (iVar5 == 0) {
      if (4 < iVar2) {
        iVar2 = 3;
        uVar9 = 0;
        goto LAB_002658d8;
      }
      goto LAB_00265d08;
    }
  }
  iVar5 = strcmp(param_3,"ofdm");
  if (iVar5 == 0) {
    uVar9 = 1;
    if (6 < iVar2) {
      iVar2 = 7;
    }
  }
  else {
    iVar5 = strcmp(param_3,"htmix");
    if (iVar5 == 0) {
      uVar9 = 2;
      if (0x1f < iVar2) {
        iVar2 = 0x20;
      }
    }
    else {
      iVar5 = strcmp(param_3,"htgf");
      if (iVar5 == 0) {
        uVar9 = 3;
        if (0x1f < iVar2) {
          iVar2 = 0x20;
        }
      }
      else {
        iVar5 = strcmp(param_3,"vht");
        if (iVar5 == 0) {
          uVar9 = 4;
          if (8 < iVar2) {
            iVar2 = 9;
          }
        }
        else {
          if (iVar3 < 3) {
LAB_0026507c:
            *(undefined1 *)((int)param_1 + 0xa7866a) = 0;
            param_1[0x29e19b] = 0;
            return 1;
          }
          iVar2 = 0;
          printk("%s: Invalid RateMode string(%s), use default!\n","ATEManualParsingParam",param_3);
          uVar9 = 0;
          iVar3 = DebugLevel;
        }
      }
    }
  }
LAB_002658d8:
  *(undefined1 *)((int)param_1 + 0xa7866a) = uVar9;
  param_1[0x29e19b] = iVar2;
  if (iVar3 < 3) {
    return 1;
  }
  printk("%s: MAXRATE=>MODE=%d,MCS=%d\n","ATEManualParsingParam",uVar9,iVar2);
  return 1;
}

