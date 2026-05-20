// module: mt7915.ko
// function: ExtEventWifiSpectrumUnSolicitRawDataHandler @ 0x1a5cd8
// size: 1124 bytes
//

void ExtEventWifiSpectrumUnSolicitRawDataHandler(int param_1,int param_2)

{
  int *piVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  size_t sVar6;
  char *__format;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined1 auStack_b4 [12];
  char acStack_a8 [64];
  char acStack_68 [68];
  
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar2 = *(byte *)(iVar4 + 400);
  iVar11 = *(int *)(iVar4 + 0x18c);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","ExtEventWifiSpectrumUnSolicitRawDataHandler");
  }
  if ((*(int *)(param_1 + 0xa78a94) == 0) || (*(int *)(param_1 + 0xa78a98) == 0)) {
    if (-1 < DebugLevel) {
      printk(&_LC40,"ExtEventWifiSpectrumUnSolicitRawDataHandler");
    }
  }
  else if (*(uint *)(param_1 + 0xa78a58) < *(uint *)(param_2 + 4)) {
    if (-1 < DebugLevel) {
      printk(&_LC41,"ExtEventWifiSpectrumUnSolicitRawDataHandler");
    }
  }
  else {
    iVar9 = 0;
    RtmpOSFSInfoChange(auStack_b4,1);
    do {
      uVar10 = *(uint *)(param_2 + (iVar9 + 0xc) * 4);
      os_zero_mem(acStack_a8,0x40);
      os_zero_mem(acStack_68,0x40);
      iVar5 = Get_System_CapNode_Info(param_1);
      if ((((*(int *)(iVar4 + 0x194) == iVar5) || (*(int *)(iVar4 + 0x198) == iVar5)) ||
          (*(int *)(iVar4 + 0x19c) == iVar5)) || (*(int *)(iVar4 + 0x1a0) == iVar5)) {
        if (2 < DebugLevel) {
          printk("%s : Dump 1-way RXADC\n","ExtEventWifiSpectrumUnSolicitRawDataHandler");
          if (*(char *)(iVar11 + 0x11) != '\n') goto LAB_001a5e1c;
LAB_001a5e80:
          uVar3 = (ushort)((uVar10 << 0xc) >> 0x10);
          uVar7 = uVar3 >> 6;
          uVar8 = (uint)(short)(ushort)((uVar10 << 0x16) >> 0x16);
          if (0x1ff < uVar8) {
            uVar8 = (uVar10 & 0x3ff) - 0x400;
          }
          if (0x1ff < (uVar10 << 0xc) >> 0x16) {
            uVar7 = (uVar3 >> 6) - 0x400;
          }
          __format = "%+04d\t%+04d\n";
          goto LAB_001a5eac;
        }
        if (*(char *)(iVar11 + 0x11) == '\n') goto LAB_001a5e80;
      }
      else {
        if (((((*(int *)(iVar4 + 0x1a4) == iVar5) || (*(int *)(iVar4 + 0x1a8) == iVar5)) ||
             ((*(int *)(iVar4 + 0x1ac) == iVar5 ||
              ((*(int *)(iVar4 + 0x1b0) == iVar5 || (*(int *)(iVar4 + 0x1b4) == iVar5)))))) ||
            (*(int *)(iVar4 + 0x1b8) == iVar5)) ||
           ((*(int *)(iVar4 + 0x1bc) == iVar5 || (*(int *)(iVar4 + 0x1c0) == iVar5)))) {
          if (DebugLevel < 3) {
            if (*(char *)(iVar11 + 0x12) != '\f') goto LAB_001a5e28;
          }
          else {
            printk("%s : Dump 1-way RXIQC\n","ExtEventWifiSpectrumUnSolicitRawDataHandler");
            if (*(char *)(iVar11 + 0x12) != '\f') goto LAB_001a5e1c;
          }
          uVar3 = (ushort)(uVar10 >> 8);
          uVar7 = uVar3 >> 4;
          uVar8 = (uint)(short)(ushort)((uVar10 << 0x14) >> 0x14);
          if (0x7ff < uVar8) {
            uVar8 = (uVar10 & 0xfff) - 0x1000;
          }
          if (0x7ff < (uVar10 << 8) >> 0x14) {
            uVar7 = (uVar3 >> 4) - 0x1000;
          }
          __format = "%+05d\t%+05d\n";
LAB_001a5eac:
          sprintf(acStack_a8,__format,(int)(short)uVar7,uVar8);
          sVar6 = strlen(acStack_a8);
          RtmpOSFileWrite(*(undefined4 *)(param_1 + 0xa78a94),acStack_a8,sVar6);
          sprintf(acStack_68,"%+04d\t%+04d\n",(uVar10 << 2) >> 0x1e,(uVar10 << 4) >> 0x1c);
          sVar6 = strlen(acStack_68);
          RtmpOSFileWrite(*(undefined4 *)(param_1 + 0xa78a98),acStack_68,sVar6);
        }
LAB_001a5e1c:
        if (2 < DebugLevel) {
          printk("%s : 0x%08x\n","ExtEventWifiSpectrumUnSolicitRawDataHandler",uVar10);
        }
      }
LAB_001a5e28:
      iVar9 = iVar9 + 1;
    } while (iVar9 != 0x100);
    RtmpOSFSInfoChange(auStack_b4,0);
    iVar9 = *(int *)(param_1 + 0xa78a58) + 1;
    *(int *)(param_1 + 0xa78a58) = iVar9;
    iVar11 = DebugLevel;
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) {
      if (iVar9 == 0x80) {
        *(undefined4 *)(param_1 + 0xa78a58) = 0;
        *(undefined4 *)(param_1 + 0xa78a4c) = 0;
        if (0 < iVar11) {
          printk(&_LC47,"ExtEventWifiSpectrumUnSolicitRawDataHandler");
        }
        complete(param_1 + 0xa78aac);
      }
    }
    else {
      iVar11 = *(int *)(iVar4 + 0x18c);
      iVar4 = *(int *)(param_1 + 0xa78a5c) * 0x1f;
      if (iVar9 == *(int *)(iVar11 + iVar4 + 0xc)) {
        if (*(int *)(param_1 + 0xa78a5c) + 1U == (uint)bVar2) {
          if (bVar2 == 0) {
            iVar4 = 0;
          }
          else {
            iVar9 = iVar11 + iVar4 + 0x1f;
            iVar4 = 0;
            do {
              piVar1 = (int *)(iVar11 + 0xc);
              iVar11 = iVar11 + 0x1f;
              iVar4 = iVar4 + *piVar1;
            } while (iVar11 != iVar9);
          }
          if (0 < DebugLevel) {
            printk(&_LC48,"ExtEventWifiSpectrumUnSolicitRawDataHandler",iVar4);
          }
          *(undefined4 *)(param_1 + 0xa78a4c) = 0;
        }
        *(undefined4 *)(param_1 + 0xa78a58) = 0;
        complete(param_1 + 0xa78aac);
      }
    }
    if ((0 < DebugLevel) &&
       (printk("%s:(Status = %d)\n","ExtEventWifiSpectrumUnSolicitRawDataHandler",
               *(undefined4 *)(param_1 + 0xa78a4c)), 2 < DebugLevel)) {
      printk("%s<-----------------\n","ExtEventWifiSpectrumUnSolicitRawDataHandler");
    }
  }
  return;
}

