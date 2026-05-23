// module: mt7915.ko
// function: ExtEventWifiSpectrumUnSolicitIQDataHandler @ 0x1a6140
// size: 788 bytes
//

void ExtEventWifiSpectrumUnSolicitIQDataHandler(int param_1,int param_2)

{
  undefined4 uVar1;
  size_t sVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 local_104;
  undefined1 auStack_f4 [12];
  char acStack_e8 [64];
  char acStack_a8 [64];
  char acStack_68 [68];
  
  if (2 < DebugLevel) {
    printk("%s----------------->\n","ExtEventWifiSpectrumUnSolicitIQDataHandler");
  }
  uVar3 = *(uint *)(param_2 + 4);
  if (((*(int *)(param_1 + 0xa78a94) == 0) || (*(int *)(param_1 + 0xa78a98) == 0)) ||
     (*(int *)(param_1 + 0xa78a9c) == 0)) {
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC40,"ExtEventWifiSpectrumUnSolicitIQDataHandler");
    return;
  }
  uVar4 = *(uint *)(param_1 + 0xa78a58);
  if (uVar4 < uVar3) {
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC41,"ExtEventWifiSpectrumUnSolicitIQDataHandler");
    return;
  }
  if (*(int *)(param_2 + 0xc) == 0) {
LAB_001a61c8:
    if (uVar3 == uVar4) {
      if (0 < DebugLevel) {
        printk(&_LC54,"ExtEventWifiSpectrumUnSolicitIQDataHandler");
      }
      *(undefined4 *)(param_1 + 0xa78a58) = 0;
      *(undefined4 *)(param_1 + 0xa78a4c) = 0;
      complete(param_1 + 0xa78aac);
      goto LAB_001a61d8;
    }
  }
  else {
    RtmpOSFSInfoChange(auStack_f4,1);
    uVar3 = *(uint *)(param_1 + 0xa78a60) >> 0x1c;
    if (0 < DebugLevel) {
      printk(&_LC51,"ExtEventWifiSpectrumUnSolicitIQDataHandler",uVar3);
    }
    if (*(int *)(param_2 + 0xc) != 0) {
      local_104 = 0;
      uVar4 = 0;
      uVar8 = 0;
      uVar10 = 0;
      do {
        uVar6 = *(undefined4 *)(param_2 + (uVar4 + 0xc) * 4);
        uVar9 = uVar10;
        uVar1 = local_104;
        if (uVar3 == 4) {
          os_zero_mem(acStack_68,0x40);
          sprintf(acStack_68,"%08x\n",uVar6);
          sVar2 = strlen(acStack_68);
          RtmpOSFileWrite(*(undefined4 *)(param_1 + 0xa78a9c),acStack_68,sVar2);
          uVar7 = uVar8;
        }
        else {
          os_zero_mem(acStack_e8,0x40);
          os_zero_mem(acStack_a8,0x40);
          uVar5 = uVar4 & 3;
          uVar7 = uVar6;
          if (((uVar5 != 0) && (uVar7 = uVar8, uVar9 = uVar6, uVar5 != 1)) &&
             (uVar9 = uVar10, uVar1 = uVar6, uVar5 != 2)) {
            sprintf(acStack_e8,"%+05d\t%+05d\n",uVar8,uVar10);
            sVar2 = strlen(acStack_e8);
            RtmpOSFileWrite(*(undefined4 *)(param_1 + 0xa78a94),acStack_e8,sVar2);
            sprintf(acStack_a8,"%+04d\t%+04d\n",uVar6,local_104);
            sVar2 = strlen(acStack_a8);
            RtmpOSFileWrite(*(undefined4 *)(param_1 + 0xa78a98),acStack_a8,sVar2);
            uVar1 = local_104;
          }
        }
        local_104 = uVar1;
        if (2 < DebugLevel) {
          printk("%s : %d\n","ExtEventWifiSpectrumUnSolicitIQDataHandler",uVar6);
        }
        uVar4 = uVar4 + 1;
        uVar8 = uVar7;
        uVar10 = uVar9;
      } while (uVar4 < *(uint *)(param_2 + 0xc));
    }
    RtmpOSFSInfoChange(auStack_f4,0);
    if (*(int *)(param_2 + 0xc) == 0) {
      uVar3 = *(uint *)(param_2 + 4);
      uVar4 = *(uint *)(param_1 + 0xa78a58);
      goto LAB_001a61c8;
    }
    uVar4 = *(uint *)(param_1 + 0xa78a58);
  }
  *(uint *)(param_1 + 0xa78a58) = uVar4 + 1;
LAB_001a61d8:
  if ((0 < DebugLevel) &&
     (printk("%s:(Status = %d)\n","ExtEventWifiSpectrumUnSolicitIQDataHandler",
             *(undefined4 *)(param_1 + 0xa78a4c)), 2 < DebugLevel)) {
    printk("%s<-----------------\n","ExtEventWifiSpectrumUnSolicitIQDataHandler");
  }
  return;
}

