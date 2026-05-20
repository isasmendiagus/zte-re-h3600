// module: mt7915.ko
// function: SetSrRcpiTblAll @ 0x17161c
// size: 568 bytes
//

int SetSrRcpiTblAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined1 *puVar5;
  uint uVar6;
  int *piVar7;
  undefined1 local_60;
  char local_5f;
  undefined1 local_5e;
  undefined1 uStack_55;
  undefined1 local_54 [12];
  int local_48 [13];
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 != 0) {
    uVar1 = HcGetBandByWdev();
    os_zero_mem(&local_60,0x18);
    local_60 = 8;
    local_5f = '\f';
    local_5e = uVar1;
    if (param_2 == 0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Arg is Null\n","SetSrRcpiTblAll");
    }
    else {
      iVar2 = rstrtok(param_2,&_LC44);
      if (iVar2 == 0) {
        cVar4 = '\0';
LAB_00171788:
        if (local_5f == cVar4) {
          puVar5 = &uStack_55;
          piVar7 = local_48;
          do {
            uVar1 = SRRcpiConv((int)(char)*piVar7);
            puVar5 = puVar5 + 1;
            *puVar5 = uVar1;
            piVar7 = piVar7 + 1;
          } while (puVar5 != local_54 + 0xb);
          iVar2 = SrCmdSRUpdateRcpiTbl(param_1,&local_60);
          if (iVar2 != 1) {
            return iVar2;
          }
        }
        else {
          if (DebugLevel < 0) {
            return 1;
          }
          printk("%s: Format Error! ArgNum = %d != %d\n","SetSrRcpiTblAll",cVar4);
        }
      }
      else {
        for (cVar4 = '\x01'; uVar6 = (uint)(byte)(cVar4 - 1), uVar6 < 0xc; cVar4 = cVar4 + '\x01') {
          iVar2 = simple_strtol(iVar2,0,10);
          local_48[uVar6] = -iVar2;
          if (iVar2 - 0x3eU < 0x31) {
            iVar2 = rstrtok(0,&_LC44);
            if (iVar2 == 0) goto LAB_00171788;
          }
          else {
            iVar3 = FUN_0016b374(-iVar2,uVar6,0xffffff92,0xffffffc2);
            iVar2 = rstrtok(0,&_LC44);
            if (iVar2 == 0) {
              if (iVar3 != 1) goto LAB_00171788;
              goto LAB_001716c8;
            }
            if (iVar3 == 1) goto LAB_001716c8;
          }
        }
        if (-1 < DebugLevel) {
          printk("%s: set wrong parameters\n","SetSrRcpiTblAll");
        }
        rstrtok(0,&_LC44);
      }
    }
LAB_001716c8:
    if (-1 < DebugLevel) {
      printk("%s: iwpriv ra0 set srrcpitbl=[RcpiTblMcs[0]]-...-[RcpiTblMcs[11]]\n","SetSrRcpiTblAll"
            );
    }
  }
  return 1;
}

