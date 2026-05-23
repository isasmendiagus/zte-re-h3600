// module: mt7915.ko
// function: net_ad_read_write_bulk_eeprom @ 0x25d9a8
// size: 376 bytes
//

undefined4 net_ad_read_write_bulk_eeprom(int param_1,int *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int extraout_r1;
  int extraout_r1_00;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  undefined2 local_22 [3];
  
  uVar8 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  iVar4 = (int)((ulonglong)uVar8 >> 0x20);
  iVar1 = (int)uVar8;
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else {
    iVar6 = *param_2;
    uVar7 = param_2[1];
    if (param_3 != 0) {
      iVar4 = *(int *)(*(int *)(iVar1 + 4) + 0x240);
      if (iVar4 == 0) {
        warn_slowpath_null("include/linux/netdevice.h",0xa06);
        printk(&_LC20);
      }
      else {
        _set_bit(0,iVar4 + 0x50);
      }
      if (uVar7 >> 1 != 0) {
        uVar5 = 0;
        do {
          iVar4 = uVar5 * 2;
          chip_eeprom_read16(iVar1,iVar4 + iVar6,local_22);
          uVar5 = uVar5 + 1;
          *(undefined2 *)(param_2[2] + iVar4) = local_22[0];
        } while (uVar5 != uVar7 >> 1);
      }
      _clear_bit(0,*(int *)(*(int *)(iVar1 + 4) + 0x240) + 0x50);
      return 0;
    }
    if (uVar7 == 0x10) {
      sys_ad_move_mem((void *)(*(int *)("Set_IRR_TTGOnOff" + iVar1 + 4) + iVar6),
                      (void *)(param_2[2] + iVar6 * 2),0x10);
      uVar2 = 0;
    }
    else {
      if (uVar7 == *(uint *)(param_1 + 0x50)) {
        rtmp_ee_flash_write_all(iVar1);
        iVar4 = extraout_r1_00;
      }
      if (uVar7 >> 1 != 0) {
        uVar5 = 0;
        do {
          local_22[0] = *(undefined2 *)(param_2[2] + uVar5 * 2);
          iVar3 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0),iVar4);
          iVar4 = iVar6 + uVar5 * 2;
          if (*(code **)(iVar3 + 0xc) != (code *)0x0) {
            (**(code **)(iVar3 + 0xc))(iVar1,iVar4,local_22[0]);
            iVar4 = extraout_r1;
          }
          uVar5 = uVar5 + 1 & 0xffff;
        } while (uVar5 < uVar7 >> 1);
      }
      uVar2 = 0;
    }
  }
  return uVar2;
}

