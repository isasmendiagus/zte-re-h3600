// module: mt7915.ko
// function: Set_IgmpSn_AddEntry_Proc @ 0x241590
// size: 1016 bytes
//

undefined4 Set_IgmpSn_AddEntry_Proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  bool bVar2;
  undefined4 uVar3;
  byte bVar4;
  char *__s;
  size_t sVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  byte *pbVar12;
  int iVar13;
  byte *pbVar14;
  undefined4 local_44;
  char *local_3c;
  byte abStack_38 [4];
  undefined4 local_34;
  undefined2 local_30;
  uint local_2e;
  undefined2 local_2a;
  
  uVar11 = (uint)*(byte *)(*param_1 + 0x3c);
  bVar2 = true;
  if (uVar11 == 0) {
    iVar9 = param_1[1];
  }
  else {
    iVar9 = param_1[uVar11 * 0x160d + 0xadc92];
  }
  local_44 = 0;
  local_3c = param_2;
  do {
    __s = strsep(&local_3c,"-");
    if (__s == (char *)0x0) {
      return 1;
    }
    if (bVar2) {
      sVar5 = strlen(__s);
      if (sVar5 == 0x11) goto LAB_002416fc;
      pbVar6 = (byte *)rstrtok(__s,&_LC28);
      if (pbVar6 == (byte *)0x0) {
        return 0;
      }
      if (*pbVar6 == 0) {
        return 0;
      }
      iVar7 = 0;
      pbVar14 = abStack_38;
      while( true ) {
        sVar5 = strlen((char *)pbVar6);
        if (3 < sVar5) {
          return 0;
        }
        if (sVar5 != 0) {
          if (((&_ctype)[*pbVar6] & 0x44) == 0) {
            return 0;
          }
          pbVar12 = pbVar6;
          while (pbVar12 = pbVar12 + 1, pbVar12 != pbVar6 + sVar5) {
            if (((&_ctype)[*pbVar12] & 0x44) == 0) {
              return 0;
            }
          }
        }
        iVar7 = iVar7 + 1;
        bVar4 = os_str_tol(pbVar6,0,10);
        *pbVar14 = bVar4;
        pbVar6 = (byte *)rstrtok(0,&_LC28);
        if (pbVar6 == (byte *)0x0) break;
        pbVar14 = pbVar14 + 1;
        if (*pbVar6 == 0) {
          return 0;
        }
      }
      if (iVar7 != 4) {
        return 0;
      }
      local_34._1_3_ = (uint3)(((uint)abStack_38[1] << 0x18) >> 8) & 0x7fffff;
      local_30 = CONCAT11(abStack_38[3],abStack_38[2]);
      local_34 = CONCAT31(local_34._1_3_,1);
      uVar3 = local_34;
      local_34._0_3_ = CONCAT12(0x5e,(short)uVar3);
LAB_002418c4:
      uVar10 = local_34 & 0xff;
      if (uVar10 == 0xff) {
        uVar8 = 0;
      }
      else {
        uVar8 = local_34 & 1;
      }
      local_2e = local_34;
      local_2a = local_30;
      if (uVar8 == 0) {
LAB_00241918:
        if (2 < DebugLevel) {
          printk("%s (%2X:%2X:%2X:%2X:%2X:%2X) is not a acceptable address.\n",
                 "Set_IgmpSn_AddEntry_Proc",uVar10,local_34._1_1_,local_34 >> 0x10 & 0xff,
                 local_34 >> 0x18,(undefined1)local_30,local_30._1_1_);
        }
        return 0;
      }
      AsicMcastEntryInsert
                (param_1,&local_2e,*(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b7be1),
                 local_44,0,iVar9,0);
LAB_0024181c:
      if (2 < DebugLevel) {
        printk("%s (%2X:%2X:%2X:%2X:%2X:%2X)\n","Set_IgmpSn_AddEntry_Proc",local_34 & 0xff,
               local_34._1_1_,local_34 >> 0x10 & 0xff,local_34 >> 0x18,(undefined1)local_30,
               local_30._1_1_);
      }
    }
    else {
      sVar5 = strlen(__s);
      if (sVar5 == 0x11) {
LAB_002416fc:
        pbVar6 = (byte *)rstrtok(__s,&_LC27);
        if (pbVar6 == (byte *)0x0) {
          return 0;
        }
        iVar7 = 0;
        do {
          iVar13 = iVar7 + 1;
          sVar5 = strlen((char *)pbVar6);
          if (sVar5 != 2) {
            return 0;
          }
          if (((&_ctype)[*pbVar6] & 0x44) == 0) {
            return 0;
          }
          if (((&_ctype)[pbVar6[1]] & 0x44) == 0) {
            return 0;
          }
          AtoH(pbVar6,(int)&local_34 + iVar7,1);
          pbVar6 = (byte *)rstrtok(0,&_LC27);
          iVar7 = iVar13;
        } while (pbVar6 != (byte *)0x0);
        if (iVar13 != 6) {
          return 0;
        }
        if (bVar2) goto LAB_002418c4;
        iVar7 = MacTableLookup(param_1,&local_34);
        if (((iVar7 != 0) && (param_1[uVar11 * 0x160d + 0xadc97] == 1)) &&
           (*(char *)(iVar7 + 0xe8) != '\0')) {
          local_44 = 0x80;
        }
        uVar10 = local_34 & 0xff;
        uVar8 = local_34 & 1 ^ 1;
        if (uVar10 == 0xff) {
          uVar8 = 1;
        }
        if (uVar8 == 0) goto LAB_00241918;
        uVar1 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b7be1);
        if (iVar7 != 0) {
          AsicMcastEntryInsert
                    (param_1,&local_2e,uVar1,local_44,&local_34,iVar9,*(undefined2 *)(iVar7 + 0xe0))
          ;
        }
        else {
          AsicMcastEntryInsert(param_1,&local_2e,uVar1,0,&local_34,iVar9,0);
        }
        goto LAB_0024181c;
      }
    }
    bVar2 = false;
  } while( true );
}

