// module: mt7915.ko
// function: Set_EECMD_Proc @ 0x25f670
// size: 696 bytes
//

undefined4 Set_EECMD_Proc(int param_1,int param_2)

{
  undefined2 uVar1;
  ushort uVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  ushort local_1c;
  ushort local_1a;
  
  local_1c = os_str_tol(param_2,0,10);
  if (local_1c == 1) {
    if (*(int *)(param_1 + 0x286280) == 4) {
      if ((0 < DebugLevel) && (printk("EEPROM reset to default......\n"), 0 < DebugLevel)) {
        printk("The last byte of MAC address will be re-generated...\n");
      }
      iVar3 = FUN_0025ed80(param_1,*(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4));
      if (iVar3 == 0) {
        rtmp_ee_flash_read(param_1,8,&local_1a);
        local_1a = (ushort)(byte)local_1a;
        uVar2 = RandomByte(param_1);
        local_1a = local_1a | (uVar2 & 0xf8) << 8;
        if (0 < DebugLevel) {
          printk("Addr45 = %4x\n",local_1a);
        }
        rtmp_ee_flash_write(param_1,8,local_1a);
        rtmp_ee_flash_read(param_1,0,&local_1c);
        if ((local_1c + 0xd7a0 & 0xffdf) == 0) {
          return 1;
        }
        if (-1 < DebugLevel) {
          printk("Set_EECMD_Proc: invalid eeprom\n");
          return 0;
        }
      }
      else if (-1 < DebugLevel) {
        printk("Set_EECMD_Proc: rtmp_ee_flash_reset() failed\n");
        return 0;
      }
      return 0;
    }
  }
  else if (local_1c == 0) {
    local_1c = 0;
    uVar5 = 0;
    do {
      uVar6 = uVar5 + 2;
      chip_eeprom_read16(param_1,uVar5,&local_1a);
      if (((0 < DebugLevel) && (printk("%4.4x ",local_1a), (uVar6 & 0x1f) == 0)) && (0 < DebugLevel)
         ) {
        printk(&_LC9);
      }
      uVar5 = uVar6;
    } while (uVar6 != 0x400);
  }
  else if (local_1c == 2) {
    uVar1 = os_str_tol(param_2 + 2,0,10);
    uVar5 = (uint)*(byte *)(param_2 + 4);
    pbVar4 = (byte *)(param_2 + 4);
    if (uVar5 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = 0;
      do {
        if (uVar5 - 0x30 < 10) {
          uVar6 = (uVar5 + uVar6 * 0x10) - 0x30 & 0xffff;
        }
        else if (uVar5 - 0x61 < 6) {
          uVar6 = (uVar5 + uVar6 * 0x10) - 0x57 & 0xffff;
        }
        else if (uVar5 - 0x41 < 6) {
          uVar6 = (uVar5 + uVar6 * 0x10) - 0x37 & 0xffff;
        }
        pbVar4 = pbVar4 + 1;
        uVar5 = (uint)*pbVar4;
      } while (uVar5 != 0);
    }
    iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar3 + 0xc) != (code *)0x0) {
      (**(code **)(iVar3 + 0xc))(param_1,uVar1,uVar6);
      return 1;
    }
  }
  return 1;
}

