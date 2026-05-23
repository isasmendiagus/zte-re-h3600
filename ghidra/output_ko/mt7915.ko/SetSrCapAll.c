// module: mt7915.ko
// function: SetSrCapAll @ 0x16ddb0
// size: 1360 bytes
//

int SetSrCapAll(int *param_1,int param_2)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  undefined1 uVar6;
  uint uVar7;
  undefined1 uVar8;
  uint uVar9;
  undefined1 uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  undefined1 local_40;
  char local_3f;
  undefined1 local_3e;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar3 != 0) {
    uVar2 = HcGetBandByWdev();
    os_zero_mem(&local_40,0x18);
    local_40 = 2;
    local_3f = '\f';
    local_3e = uVar2;
    if (param_2 == 0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Arg is Null\n","SetSrCapAll");
    }
    else {
      iVar3 = rstrtok(param_2,&_LC44);
      if (iVar3 == 0) {
        cVar4 = '\0';
        uVar2 = 0;
        uVar6 = 0;
        uVar8 = 0;
        uVar10 = 0;
        uVar12 = 0;
        uVar13 = 0;
        uVar14 = 0;
        uVar15 = 0;
        uVar16 = 0;
        uVar17 = 0;
        uVar18 = 0;
        uVar19 = 0;
LAB_0016e20c:
        if (local_3f == cVar4) {
          local_32 = (undefined1)uVar12;
          local_31 = (undefined1)uVar13;
          local_30 = (undefined1)uVar14;
          local_2f = (undefined1)uVar15;
          local_2e = (undefined1)uVar16;
          local_2d = (undefined1)uVar17;
          local_2c = (undefined1)uVar18;
          local_2b = (undefined1)uVar19;
          local_34 = uVar10;
          local_33 = uVar8;
          local_2a = uVar6;
          local_29 = uVar2;
          iVar3 = SrCmdSRUpdateCap(param_1,&local_40);
          if (iVar3 != 1) {
            return iVar3;
          }
        }
        else {
          if (DebugLevel < 0) {
            return 1;
          }
          printk("%s: Format Error! ArgNum = %d != %d\n","SetSrCapAll",cVar4,local_3f,uVar12,uVar13,
                 uVar14,uVar15,uVar16,uVar17,uVar18,uVar19);
        }
      }
      else {
        uVar5 = 0;
        uVar7 = 0;
        uVar9 = 0;
        uVar11 = 0;
        cVar4 = '\0';
        uVar19 = 0;
        uVar18 = 0;
        uVar17 = 0;
        uVar16 = 0;
        uVar15 = 0;
        uVar14 = 0;
        uVar13 = 0;
        uVar12 = 0;
        do {
          switch(cVar4) {
          case '\0':
            uVar11 = simple_strtol(iVar3,0,10);
            if (uVar11 < 2) {
LAB_0016e1d8:
              bVar1 = false;
            }
            else {
              if (DebugLevel < 0) goto LAB_0016debc;
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",0,uVar11);
              bVar1 = true;
            }
            break;
          case '\x01':
            uVar9 = simple_strtol(iVar3,0,10);
            if (uVar9 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",1,uVar9);
            bVar1 = true;
            break;
          case '\x02':
            uVar12 = simple_strtol(iVar3,0,10);
            if (uVar12 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",2,uVar12);
            bVar1 = true;
            break;
          case '\x03':
            uVar13 = simple_strtol(iVar3,0,10);
            if (uVar13 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",3,uVar13);
            bVar1 = true;
            break;
          case '\x04':
            uVar14 = simple_strtol(iVar3,0,10);
            if (uVar14 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",4,uVar14);
            bVar1 = true;
            break;
          case '\x05':
            uVar15 = simple_strtol(iVar3,0,10);
            if (uVar15 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",5,uVar15);
            bVar1 = true;
            break;
          case '\x06':
            uVar16 = simple_strtol(iVar3,0,10);
            if (uVar16 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",6,uVar16);
            bVar1 = true;
            break;
          case '\a':
            uVar17 = simple_strtol(iVar3,0,10);
            if (uVar17 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",7,uVar17);
            bVar1 = true;
            break;
          case '\b':
            uVar18 = simple_strtol(iVar3,0,10);
            if (uVar18 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",8,uVar18);
            bVar1 = true;
            break;
          case '\t':
            uVar19 = simple_strtol(iVar3,0,10);
            if (uVar19 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",9,uVar19);
            bVar1 = true;
            break;
          case '\n':
            uVar7 = simple_strtol(iVar3,0,10);
            if (uVar7 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",10,uVar7);
            bVar1 = true;
            break;
          case '\v':
            uVar5 = simple_strtol(iVar3,0,10);
            if (uVar5 < 2) goto LAB_0016e1d8;
            if (DebugLevel < 0) goto LAB_0016debc;
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",0xb,uVar5);
            bVar1 = true;
            break;
          default:
            if (DebugLevel < 0) {
LAB_0016debc:
              bVar1 = true;
            }
            else {
              bVar1 = true;
              printk("%s: set wrong parameters\n","SetSrCapAll");
            }
          }
          uVar2 = (undefined1)uVar5;
          uVar6 = (undefined1)uVar7;
          uVar8 = (undefined1)uVar9;
          uVar10 = (undefined1)uVar11;
          cVar4 = cVar4 + '\x01';
          iVar3 = rstrtok(0,&_LC44);
          if (iVar3 == 0) {
            if (!bVar1) goto LAB_0016e20c;
            break;
          }
        } while (!bVar1);
      }
    }
    if (-1 < DebugLevel) {
      printk("%s: iwpriv ra0 set srcap=[SrEn]-[SrgEn]-[NonSrgEn]-[SingleMdpuRtsctsEn]-[HdrDurEn]-[TxopDurEn]-[NonSrgInterPpduPresv]-[SrgInterPpduPresv]-[SrRemTimeEn]-[ProtInSrWinDis]-[TxCmdDlRateSelEn]-[AmpduTxCntEn]\n"
             ,"SetSrCapAll");
    }
  }
  return 1;
}

