// module: mt7915.ko
// function: pci_rx_data_done_poll_func @ 0x1cb9c8
// size: 896 bytes
//

int pci_rx_data_done_poll_func(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined1 auStack_100 [164];
  int local_5c;
  int local_58;
  uint local_54;
  int local_50;
  undefined1 *local_4c;
  byte *local_48;
  uint local_44;
  int local_40;
  int local_3c;
  byte *local_38;
  int local_34;
  char local_2d;
  undefined1 auStack_2c [8];
  
  iVar5 = *(int *)(param_1 + 0x70);
  iVar8 = *(int *)(iVar5 + 0xd0);
  local_5c = param_1;
  local_40 = iVar5;
  local_34 = param_2;
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar8 + 0xb0));
  local_58 = iVar2 + 0xa79000;
  iVar3 = hc_get_arch_ops(*(undefined4 *)(iVar2 + 0xa797a0));
  iVar7 = local_40;
  local_54 = *(uint *)(iVar5 + 0x6c);
  iVar6 = *(int *)(iVar5 + 0x70);
  if (*(char *)(iVar2 + 0x2f5ec) == '\0') {
    local_50 = iVar5 + 0xc0;
  }
  else {
    iVar5 = local_40 + 0xc0;
    local_50 = iVar5;
    ba_timeout_flush(iVar2);
    uVar4 = _raw_spin_lock_irqsave(iVar5);
    if (((local_54 & *(uint *)(iVar7 + 0xc)) == 0) && ((local_54 & *(uint *)(iVar7 + 8)) == 0)) {
      _raw_spin_unlock_irqrestore(local_50,uVar4);
      napi_complete_done(local_5c,0);
      return 0;
    }
    _raw_spin_unlock_irqrestore(local_50,uVar4);
  }
  iVar7 = local_50;
  if ((*(uint *)(iVar2 + 0xa39f84) & 0x100) != 0) {
    uVar4 = _raw_spin_lock_irqsave(local_50);
    *(uint *)(local_40 + 8) = *(uint *)(local_40 + 8) & ~local_54;
    _raw_spin_unlock_irqrestore(iVar7,uVar4);
    napi_complete_done(local_5c,0);
    return 0;
  }
  uVar4 = _raw_spin_lock_irqsave(local_50);
  iVar5 = local_40;
  local_44 = *(uint *)(local_40 + 0xc);
  *(uint *)(local_40 + 0xc) = local_44 & ~local_54;
  _raw_spin_unlock_irqrestore(iVar7,uVar4);
  if (iVar6 == 0) {
    iVar7 = 0;
  }
  else {
    local_38 = (byte *)(iVar5 + 0x73);
    local_48 = (byte *)(iVar5 + iVar6 + 0x73);
    local_4c = &_LANCHOR1;
    iVar7 = 0;
    do {
      local_2d = '\0';
      local_38 = local_38 + 1;
      iVar5 = *(int *)(local_40 + 0x14) + (uint)*local_38 * 0xa0;
      local_3c = iVar5 + 0x54;
      _raw_spin_lock_bh(local_3c);
      if (((local_44 & *(uint *)(iVar5 + 100)) != 0) || (local_4c[2] != '\0')) {
        do {
          iVar6 = (**(code **)(iVar8 + ((uint)*(byte *)(iVar5 + 0x1f) +
                                       (uint)*(byte *)(iVar5 + 0x1d) * 2) * 4 + 100))
                            (iVar2,&local_2d,auStack_2c,*(undefined1 *)(iVar5 + 0x1c));
          if (iVar6 == 0) break;
          os_zero_mem(auStack_100,0x90);
          (**(code **)(iVar3 + 0x198))(iVar2,*(undefined1 *)(iVar5 + 0x1c),auStack_100,iVar6);
          iVar7 = iVar7 + 1;
        } while (iVar7 < local_34);
        if (*(short *)(iVar5 + 0x30) != 0) {
          hif_io_write32(*(undefined4 *)(local_58 + 0x7a0),*(undefined4 *)(iVar5 + 0x3c),
                         *(undefined4 *)(iVar5 + 0x34));
          *(undefined2 *)(iVar5 + 0x30) = 0;
        }
        if (local_2d != '\0') {
          local_4c[2] = 1;
        }
      }
      _raw_spin_unlock_bh(local_3c);
    } while (local_38 != local_48);
  }
  if (iVar7 < local_34) {
    napi_complete_done(local_5c,0);
    uVar4 = _raw_spin_lock_irqsave(local_50);
    cVar1 = DAT_005f48f2;
    if (((local_54 & *(uint *)(local_40 + 0xc)) == 0) && (DAT_005f48f2 == '\0')) {
      mt_int_enable(iVar2,local_40,local_54);
      _raw_spin_unlock_irqrestore(local_50,uVar4);
      DAT_005f48f2 = cVar1;
    }
    else {
      _raw_spin_unlock_irqrestore(local_50,uVar4);
      if ((-1 < *(int *)(local_5c + 8) << 0x1e) &&
         (iVar2 = _test_and_set_bit(0,local_5c + 8), iVar2 == 0)) {
        __napi_schedule(local_5c);
      }
    }
  }
  else {
    DAT_005f48f2 = '\x01';
  }
  return iVar7;
}

