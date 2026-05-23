// module: mt7915.ko
// function: Set_RBIST_Capture_Start @ 0xeac24
// size: 1080 bytes
//

undefined4 Set_RBIST_Capture_Start(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  code *pcVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  int iVar11;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_46;
  undefined4 *local_44;
  uint local_40 [7];
  
  local_44 = (undefined4 *)0x0;
  local_46 = 0;
  local_40[0] = 0;
  local_40[1] = 0;
  local_40[2] = 0;
  local_40[3] = 0;
  local_40[4] = 0;
  local_40[5] = 0;
  iVar1 = os_alloc_mem(param_1,&local_44,0x50);
  if (iVar1 == 0) {
    os_zero_mem(local_44,0x50);
    iVar1 = rstrtok(param_2,&_LC232);
    if (iVar1 == 0) {
      uVar2 = 0;
      uVar3 = 0;
      iVar4 = 0;
      uVar7 = 0;
      uVar5 = 0;
      local_6c = 0;
      local_68 = 0;
      local_64 = 0;
      local_60 = 0;
      local_5c = 0;
      local_58 = 0;
      local_54 = 0;
      local_50 = 0;
      local_4c = 0;
    }
    else {
      iVar8 = 0;
      uVar2 = 0;
      uVar3 = 0;
      iVar4 = 0;
      uVar7 = 0;
      uVar5 = 0;
      local_6c = 0;
      local_68 = 0;
      local_64 = 0;
      local_60 = 0;
      local_5c = 0;
      local_58 = 0;
      local_54 = 0;
      local_50 = 0;
      local_4c = 0;
      do {
        switch(iVar8) {
        case 0:
          iVar4 = simple_strtol(iVar1,0,0x10);
          break;
        case 1:
          local_6c = simple_strtol(iVar1,0,0x10);
          *local_44 = local_6c;
          break;
        case 2:
          uVar5 = simple_strtol(iVar1,0,0x10);
          local_44[1] = uVar5;
          break;
        case 3:
          local_68 = simple_strtol(iVar1,0,0x10);
          local_44[2] = local_68;
          break;
        case 4:
          local_64 = simple_strtol(iVar1,0,0x10);
          local_44[3] = local_64;
          break;
        case 5:
          local_60 = simple_strtol(iVar1,0,0x10);
          local_44[4] = local_60;
          break;
        case 6:
          local_5c = simple_strtol(iVar1,0,0x10);
          local_44[5] = local_5c;
          break;
        case 7:
          local_4c = simple_strtol(iVar1,0,0x10);
          local_44[10] = local_4c;
          break;
        case 8:
          local_58 = simple_strtol(iVar1,0,0x10);
          local_44[6] = local_58;
          break;
        case 9:
          puVar9 = local_40;
          iVar10 = iVar1;
          do {
            iVar11 = iVar10 + 2;
            RTMPMoveMemory(&local_46,iVar10);
            uVar3 = simple_strtol(&local_46,0,0x10);
            *puVar9 = uVar3;
            puVar9 = puVar9 + 1;
            iVar10 = iVar11;
          } while (iVar11 != iVar1 + 0xc);
          uVar3 = local_40[2] << 0x10 | local_40[1] << 8 | local_40[0] | local_40[3] << 0x18;
          uVar7 = local_40[4] | 0x10000 | local_40[5] << 8;
          local_44[7] = uVar3;
          local_44[8] = uVar7;
          break;
        case 10:
          local_50 = simple_strtol(iVar1,0,0x10);
          local_44[9] = local_50;
          break;
        case 0xb:
          local_54 = simple_strtol(iVar1,0,0x10);
          local_44[0xd] = local_54;
          break;
        case 0xc:
          uVar2 = simple_strtol(iVar1,0,0x10);
          local_44[0x11] = uVar2;
        }
        iVar8 = iVar8 + 1;
        iVar1 = rstrtok(0,&_LC232);
      } while (iVar1 != 0);
    }
    if (2 < DebugLevel) {
      printk("%s :\n Mode = 0x%08x\n Trigger = 0x%08x\n RingCapEn = 0x%08x\n TriggerEvent = 0x%08x\n CaptureNode = 0x%08x\n CaptureLen = 0x%08x\n CapStopCycle = 0x%08x\n BW = 0x%08x\n MACTriggerEvent = 0x%08x\n SourceAddrLSB = 0x%08x\n SourceAddrMSB = 0x%08x\n Band = 0x%08x\n PhyIdx = 0x%08x\n CapSrc = 0x%08x\n"
             ,"Set_RBIST_Capture_Start",iVar4,local_6c,uVar5,local_68,local_64,local_60,local_5c,
             local_4c,local_58,uVar3,uVar7,local_50,local_54,uVar2);
    }
    if (iVar4 == 0) {
      iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      pcVar6 = *(code **)(iVar1 + 0x188);
    }
    else {
      if (iVar4 != 1) goto LAB_000eac84;
      iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      pcVar6 = *(code **)(iVar1 + 0x1a0);
    }
    if (pcVar6 == (code *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s : The function is not hooked !!\n","Set_RBIST_Capture_Start");
      }
    }
    else {
      (*pcVar6)(param_1,local_44);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s : Not enough memory for dynamic allocating !!\n","Set_RBIST_Capture_Start");
  }
LAB_000eac84:
  if (local_44 != (undefined4 *)0x0) {
    os_free_mem();
  }
  return 1;
}

