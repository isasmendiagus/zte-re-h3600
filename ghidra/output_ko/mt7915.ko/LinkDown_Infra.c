// module: mt7915.ko
// function: LinkDown_Infra @ 0x727d8
// size: 980 bytes
//

undefined4 LinkDown_Infra(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined *puVar9;
  int local_2c;
  
  iVar3 = GetStaCfgByWdev();
  iVar4 = GetAssociatedAPByWdev(param_1,param_2);
  bVar1 = *(byte *)(param_2 + 0xe);
  uVar5 = get_scan_tab_by_wdev(param_1,param_2);
  if (iVar3 == 0) {
    printk(&_LC1,0xdd0);
    dump_stack();
    if (iVar4 != 0) {
      return 0;
    }
    if (*(int *)(param_2 + 0x14) != 0x100) {
      return 0;
    }
  }
  else {
    if (iVar4 != 0) {
      local_2c = 0;
      goto LAB_00072830;
    }
    if (*(int *)(param_2 + 0x14) != 0x100) goto LAB_00072a90;
  }
  local_2c = *(int *)(param_2 + 4);
  uVar2 = *(ushort *)(*(int *)(local_2c + 0x4144) + 0xe0);
  uVar8 = HcGetMaxStaNum(param_1);
  if (uVar2 < uVar8) {
    iVar4 = *(int *)(local_2c + 0x4144);
    if (iVar3 == 0) {
      return 0;
    }
    if (iVar4 != 0) {
LAB_00072830:
      WLAN_EXTENDER_Report_LinkUpDown_Event(param_1,param_2,0xa42b);
      if ((2 < DebugLevel) && (printk("!!! LINK DOWN INFRA !!!\n"), 2 < DebugLevel)) {
        printk("!!! wdev_type = %u, Idx %d !!!\n",*(undefined4 *)(param_2 + 0x14),bVar1);
      }
      *(undefined1 *)(iVar3 + 0x2124ba) = 0;
      *(undefined1 *)(iVar3 + 0x2124bb) = 0;
      if (*(int *)(param_2 + 0x14) == 2) {
        *(uint *)(iVar3 + 0x212464) = *(uint *)(iVar3 + 0x212464) & 0xffffff7e;
      }
      *(byte *)(iVar3 + 0x212427) = *(byte *)(iVar3 + 0x212426);
      memmove((void *)(iVar3 + 0x21242e),(void *)(iVar3 + 0x212406),
              (uint)*(byte *)(iVar3 + 0x212426));
      *(undefined4 *)(iVar3 + 0x21244e) = *(undefined4 *)(iVar3 + 0x212428);
      *(undefined2 *)(iVar3 + 0x212452) = *(undefined2 *)(iVar3 + 0x21242c);
      if (BN_mod_lshift1[iVar3] == (code)0x1) {
        if (2 < DebugLevel) {
          printk("NDIS_STATUS_MEDIA_DISCONNECT Event A!\n");
        }
        BN_mod_lshift1[iVar3] = (code)0x0;
      }
      else if ((*(char *)(param_2 + 0x888) == '\x01') || ((*(uint *)(param_2 + 0x2c) & 7) != 0)) {
        BssTableDeleteEntry(uVar5,(undefined4 *)(iVar3 + 0x212428),*(undefined1 *)(param_2 + 0x1a));
      }
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xfffffffb;
      iVar6 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar6 == 2) {
        *(undefined1 *)(iVar4 + 0x13c0) = 0;
      }
      if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
        if (bVar1 < 2) {
          if (*(int *)(param_2 + 0x14) != 0x100) {
            (&DAT_003678f8)[param_1] = (&DAT_003678f8)[param_1] + -1;
            *(undefined1 *)(iVar3 + 0x213336) = 0;
            OS_SET_BIT(0,iVar3 + 0x88c);
            *(undefined1 *)(iVar3 + 0x888) = 2;
            BssTableDeleteEntry(uVar5,iVar3 + 0x413a,*(undefined1 *)(param_2 + 0x1a));
            uVar5 = wlan_config_get_ht_bw(iVar3);
            uVar7 = wlan_config_get_ext_cha(iVar3);
            wlan_operate_set_ht_bw(iVar3,uVar5,uVar7);
            uVar5 = wlan_config_get_vht_bw(iVar3);
            wlan_operate_set_vht_bw(iVar3,uVar5);
            *(undefined1 *)(iVar3 + 0x213344) = 0;
            return 1;
          }
        }
        else if (*(int *)(param_2 + 0x14) != 0x100) {
          return 1;
        }
        puVar9 = &DAT_00367914 + param_1;
        _raw_spin_lock_bh(puVar9);
        if (local_2c != 0) {
          if (*(char *)(local_2c + 6) == '\x01') {
            if (-1 < DebugLevel) {
              printk("%s:wdev(type=%d,fun_idx=%d) in disconnecting, return\n","LinkDown_Infra",
                     *(undefined4 *)(param_2 + 0x14),*(undefined1 *)(param_2 + 0xe));
            }
            _raw_spin_unlock_bh(puVar9);
            return 0;
          }
          if (*(char *)(local_2c + 5) == '\x02') {
            *(undefined1 *)(local_2c + 6) = 1;
          }
        }
        _raw_spin_unlock_bh(puVar9);
        HW_REMOVE_REPT_ENTRY(param_1,*(undefined1 *)(param_2 + 0xe));
      }
      return 1;
    }
  }
  else if (iVar3 == 0) {
    return 0;
  }
LAB_00072a90:
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s():pEntry NULL, this is possible in this flow\n","LinkDown_Infra");
  return 0;
}

