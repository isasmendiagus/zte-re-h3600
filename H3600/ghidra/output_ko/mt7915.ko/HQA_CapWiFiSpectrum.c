// module: mt7915.ko
// function: HQA_CapWiFiSpectrum @ 0x278040
// size: 2020 bytes
//

undefined4 HQA_CapWiFiSpectrum(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint *puVar7;
  uint local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 *local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  int local_3c;
  uint *local_38;
  int local_34;
  undefined4 local_30;
  byte local_2c;
  byte local_2b;
  
  iVar6 = param_3 + 0xc;
  iVar4 = *(int *)(param_1 + 0xa39fd4);
  local_4c = (undefined4 *)0x0;
  local_3c = 0;
  local_38 = (uint *)0x0;
  local_34 = iVar6;
  if (2 < DebugLevel) {
    printk(&_LC152,"HQA_CapWiFiSpectrum");
  }
  FUN_00276034(1,4,&local_34,&local_70);
  if (2 < DebugLevel) {
    printk("Control:%d\n",local_70);
  }
  if (local_70 == 1) {
    if (*(int *)(iVar4 + 0x108) == 0) {
      uVar5 = 1;
    }
    else {
      iVar6 = os_alloc_mem(param_1,&local_4c,0x50);
      if (iVar6 == 0) {
        os_zero_mem(local_4c,0x50);
        FUN_00276034(1,4,&local_34,&local_6c);
        if (2 < DebugLevel) {
          printk("Trigger:%d\n",local_6c);
        }
        FUN_00276034(1,4,&local_34,&local_68);
        if (2 < DebugLevel) {
          printk("RingCapEn:%d\n",local_68);
        }
        FUN_00276034(1,4,&local_34,&local_64);
        if (2 < DebugLevel) {
          printk("Event:%d\n",local_64);
        }
        FUN_00276034(1,4,&local_34,&local_60);
        if (2 < DebugLevel) {
          printk("Node:%d\n",local_60);
        }
        FUN_00276034(1,4,&local_34,&local_5c);
        if (2 < DebugLevel) {
          printk("Len:%d\n",local_5c);
        }
        FUN_00276034(1,4,&local_34,&local_58);
        if (2 < DebugLevel) {
          printk("StopCycle:%d\n",local_58);
        }
        FUN_00276034(1,4,&local_34,&local_54);
        if (2 < DebugLevel) {
          printk("BW:%d\n",local_54);
        }
        FUN_00276034(1,4,&local_34,&local_50);
        if (2 < DebugLevel) {
          printk("MACTriggerEvent:%d\n",local_50);
        }
        FUN_00276034(0,6,&local_34,&local_30);
        if (2 < DebugLevel) {
          printk("SourceAddress:%02x:%02x:%02x:%02x:%02x:%02x\n ",local_30 & 0xff,local_30._1_1_,
                 local_30._2_1_,local_30 >> 0x18,local_2c,local_2b);
        }
        FUN_00276034(1,4,&local_34,&local_48);
        if (2 < DebugLevel) {
          printk("Band:%d\n",local_48);
        }
        FUN_00276034(1,4,&local_34,&local_40);
        if (2 < DebugLevel) {
          printk("PhyIdx:%d\n",local_40);
        }
        FUN_00276034(1,4,&local_34,&local_44);
        if (2 < DebugLevel) {
          printk("CapSource:%d\n",local_44);
        }
        *local_4c = local_6c;
        local_4c[1] = local_68;
        local_4c[3] = local_60;
        local_4c[4] = local_5c;
        local_4c[2] = local_64;
        local_4c[5] = local_58;
        local_4c[10] = local_54;
        local_4c[6] = local_50;
        local_4c[9] = local_48;
        local_4c[0xd] = local_40;
        local_4c[7] = (local_30 >> 0x10 & 0xff) << 0x10 | (local_30 >> 8 & 0xff) << 8 |
                      local_30 & 0xff | local_30 & 0xff000000;
        local_4c[8] = local_2c | 0x10000 | (uint)local_2b << 8;
        local_4c[0x11] = local_44;
        (**(code **)(iVar4 + 0x108))(param_1,local_4c);
      }
      else if (-1 < DebugLevel) {
        printk("%s : Not enough memory for dynamic allocating !!\n","HQA_CapWiFiSpectrum");
      }
      if (local_4c == (undefined4 *)0x0) {
        uVar5 = 0;
      }
      else {
        uVar5 = 0;
        os_free_mem();
      }
    }
    FUN_0026cdd0(param_3,param_2,2,uVar5);
    return uVar5;
  }
  if (local_70 == 2) {
    uVar2 = 2;
    if (*(code **)(iVar4 + 0x10c) == (code *)0x0) {
      uVar5 = 1;
    }
    else {
      uVar5 = (**(code **)(iVar4 + 0x10c))(param_1);
      iVar4 = DebugLevel;
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) {
        uVar2 = *(uint *)(param_1 + 0xa3ae1d);
        *(uint *)(param_3 + 0xe) =
             uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18;
        uVar2 = *(uint *)(param_1 + 0xa3ae21);
        *(uint *)(param_3 + 0x12) =
             uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18;
        uVar2 = *(uint *)(param_1 + 0xa3ae25);
        *(uint *)(param_3 + 0x16) =
             uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18;
        uVar2 = *(uint *)(param_1 + 0xa3ae29);
        *(uint *)(param_3 + 0x1a) =
             uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18;
        uVar2 = *(uint *)(param_1 + 0xa3ae2d);
        *(uint *)(param_3 + 0x1e) =
             uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18;
        uVar2 = *(uint *)(param_1 + 0xa3ae31);
        local_48 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                   uVar2 >> 0x18;
        uVar2 = local_48;
        if (iVar4 < 3) {
          uVar2 = 0x1a;
        }
        *(uint *)(param_3 + 0x22) = local_48;
        local_34 = iVar6;
        if (2 < iVar4) {
          printk("%s, StartAddr1:%02x StartAddr2:%02x StartAddr3:%02x EndAddr:%02x StopAddr:%02x Wrap:%02x\n"
                 ,"HQA_CapWiFiSpectrum",*(undefined4 *)(param_1 + 0xa3ae1d),
                 *(undefined4 *)(param_1 + 0xa3ae21),*(undefined4 *)(param_1 + 0xa3ae25),
                 *(undefined4 *)(param_1 + 0xa3ae29),*(undefined4 *)(param_1 + 0xa3ae2d),
                 *(undefined4 *)(param_1 + 0xa3ae31));
          uVar2 = 0x1a;
        }
      }
      else if (2 < DebugLevel) {
        printk("%s : Status = %d","HQA_CapWiFiSpectrum",uVar5);
      }
    }
    FUN_0026cdd0(param_3,param_2,uVar2,uVar5);
    return uVar5;
  }
  if (local_70 != 3) {
    return 0;
  }
  if (*(int *)(iVar4 + 0x110) == 0) {
    iVar4 = 2;
    uVar5 = 1;
    goto LAB_00278244;
  }
  FUN_00276034(1,4,&local_34,&local_44);
  if (2 < DebugLevel) {
    printk("WF_Num:%d\n",local_44);
  }
  FUN_00276034(1,4,&local_34,&local_40);
  if (2 < DebugLevel) {
    printk("IQ_Type:%d\n",local_40);
  }
  iVar1 = os_alloc_mem(param_1,&local_38,4);
  if (iVar1 == 0) {
    os_zero_mem(local_38,4);
    iVar1 = os_alloc_mem(param_1,&local_3c,0x400);
    if (iVar1 != 0) goto LAB_00278208;
    os_zero_mem(local_3c,0x400);
    (**(code **)(iVar4 + 0x110))(param_1,local_3c,local_38,local_40,local_44);
    *(uint *)(param_3 + 0xe) =
         local_70 << 0x18 | (local_70 >> 8 & 0xff) << 0x10 | (local_70 >> 0x10 & 0xff) << 8 |
         local_70 >> 0x18;
    *(uint *)(param_3 + 0x12) =
         local_44 << 0x18 | (local_44 >> 8 & 0xff) << 0x10 | (local_44 >> 0x10 & 0xff) << 8 |
         local_44 >> 0x18;
    *(uint *)(param_3 + 0x16) =
         local_40 << 0x18 | (local_40 >> 8 & 0xff) << 0x10 | (local_40 >> 0x10 & 0xff) << 8 |
         local_40 >> 0x18;
    uVar2 = *local_38;
    local_48 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
               uVar2 >> 0x18;
    *(uint *)(param_3 + 0x1a) = local_48;
    if (*local_38 == 0) {
      iVar4 = 0x12;
    }
    else {
      iVar4 = 0x12;
      puVar7 = (uint *)(local_3c + -4);
      uVar2 = 0;
      do {
        puVar7 = puVar7 + 1;
        uVar3 = *puVar7;
        uVar2 = uVar2 + 1;
        local_30 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                   uVar3 >> 0x18;
        *(uint *)(iVar6 + iVar4) = local_30;
        iVar4 = iVar4 + 4;
      } while (uVar2 < *local_38);
    }
  }
  else {
LAB_00278208:
    if (DebugLevel < 0) {
      iVar4 = 2;
    }
    else {
      iVar4 = 2;
      printk("%s : Not enough memory for dynamic allocating !!\n","HQA_CapWiFiSpectrum");
    }
  }
  if (local_38 != (uint *)0x0) {
    os_free_mem(local_38);
  }
  if (local_3c == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    os_free_mem();
  }
LAB_00278244:
  FUN_0026cdd0(param_3,param_2,iVar4,uVar5);
  return uVar5;
}

