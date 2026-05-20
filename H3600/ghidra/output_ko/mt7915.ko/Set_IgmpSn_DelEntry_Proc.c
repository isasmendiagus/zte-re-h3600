// module: mt7915.ko
// function: Set_IgmpSn_DelEntry_Proc @ 0x24198c
// size: 876 bytes
//

undefined4 Set_IgmpSn_DelEntry_Proc(int *param_1,char *param_2)

{
  bool bVar1;
  undefined4 uVar2;
  byte bVar3;
  char *__s;
  size_t sVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  uint uVar11;
  int local_44;
  char *local_3c;
  byte abStack_38 [4];
  undefined4 local_34;
  undefined2 local_30;
  uint local_2e;
  undefined2 local_2a;
  
  local_34 = 0;
  uVar11 = (uint)*(byte *)(*param_1 + 0x3c);
  local_30 = 0;
  bVar1 = true;
  if (uVar11 == 0) {
    iVar6 = param_1[1];
  }
  else {
    iVar6 = param_1[uVar11 * 0x160d + 0xadc92];
  }
  local_44 = 0;
  local_3c = param_2;
  do {
    __s = strsep(&local_3c,"-");
    if (__s == (char *)0x0) {
      if (local_44 == 0) {
        AsicMcastEntryDelete
                  (param_1,&local_2e,*(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b7be1),0,
                   iVar6,0);
      }
      if (2 < DebugLevel) {
        printk("%s (%2X:%2X:%2X:%2X:%2X:%2X)\n","Set_IgmpSn_DelEntry_Proc",local_34 & 0xff,
               local_34._1_1_,local_34 >> 0x10 & 0xff,local_34 >> 0x18,(undefined1)local_30,
               local_30._1_1_);
      }
      return 1;
    }
    if (bVar1) {
      sVar4 = strlen(__s);
      if (sVar4 == 0x11) goto LAB_00241af8;
      pbVar5 = (byte *)rstrtok(__s,&_LC28);
      if (pbVar5 == (byte *)0x0) {
        return 0;
      }
      if (*pbVar5 == 0) {
        return 0;
      }
      iVar8 = 0;
      pbVar10 = abStack_38;
      while( true ) {
        sVar4 = strlen((char *)pbVar5);
        if (3 < sVar4) {
          return 0;
        }
        if (sVar4 != 0) {
          if (((&_ctype)[*pbVar5] & 0x44) == 0) {
            return 0;
          }
          pbVar7 = pbVar5;
          while (pbVar7 = pbVar7 + 1, pbVar7 != pbVar5 + sVar4) {
            if (((&_ctype)[*pbVar7] & 0x44) == 0) {
              return 0;
            }
          }
        }
        iVar8 = iVar8 + 1;
        bVar3 = os_str_tol(pbVar5,0,10);
        *pbVar10 = bVar3;
        pbVar5 = (byte *)rstrtok(0,&_LC28);
        if (pbVar5 == (byte *)0x0) break;
        pbVar10 = pbVar10 + 1;
        if (*pbVar5 == 0) {
          return 0;
        }
      }
      if (iVar8 != 4) {
        return 0;
      }
      local_34._1_3_ = (uint3)(((uint)abStack_38[1] << 0x18) >> 8) & 0x7fffff;
      local_30 = CONCAT11(abStack_38[3],abStack_38[2]);
      local_34 = CONCAT31(local_34._1_3_,1);
      uVar2 = local_34;
      local_34._0_3_ = CONCAT12(0x5e,(short)uVar2);
      MacTableLookup(param_1,&local_34);
LAB_00241c48:
      local_2e = local_34;
      local_2a = local_30;
LAB_00241bbc:
      if (local_44 != 0) {
        AsicMcastEntryDelete
                  (param_1,&local_2e,*(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b7be1),
                   &local_34,iVar6);
      }
    }
    else {
      sVar4 = strlen(__s);
      if (sVar4 == 0x11) {
LAB_00241af8:
        pbVar5 = (byte *)rstrtok(__s,&_LC27);
        if (pbVar5 == (byte *)0x0) {
          return 0;
        }
        iVar8 = 0;
        do {
          sVar4 = strlen((char *)pbVar5);
          iVar9 = iVar8 + 1;
          if (sVar4 != 2) {
            return 0;
          }
          if (((&_ctype)[*pbVar5] & 0x44) == 0) {
            return 0;
          }
          if (((&_ctype)[pbVar5[1]] & 0x44) == 0) {
            return 0;
          }
          AtoH(pbVar5,(int)&local_34 + iVar8,1);
          pbVar5 = (byte *)rstrtok(0,&_LC27);
          iVar8 = iVar9;
        } while (pbVar5 != (byte *)0x0);
        if (iVar9 != 6) {
          return 0;
        }
        MacTableLookup(param_1,&local_34);
        if (bVar1) goto LAB_00241c48;
        local_44 = local_44 + 1;
        MacTableLookup(param_1,&local_34);
        goto LAB_00241bbc;
      }
    }
    bVar1 = false;
  } while( true );
}

