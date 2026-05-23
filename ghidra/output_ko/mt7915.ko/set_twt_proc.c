// module: mt7915.ko
// function: set_twt_proc @ 0xdec44
// size: 1768 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 set_twt_proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  uint local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  local_44 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(uint *)(*param_1 + 0x3c) & 0xff,*(undefined4 *)(*param_1 + 0x38));
  if (iVar3 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: wdev=NULL, please check\n","set_twt_proc");
    return 0;
  }
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
LAB_000decb0:
    if ((((2 < DebugLevel) && (printk("Format error! correct format:\n"), 2 < DebugLevel)) &&
        (printk("iwpriv ra0 set twt=[para_id]:[value]\n"), 2 < DebugLevel)) &&
       ((printk("\t 1. Dump twt parameters, para_id=0\n"), 2 < DebugLevel &&
        (printk("\t 2. Write twt parameters to FW, para_id=1\n"), 2 < DebugLevel)))) {
      printk("\t 2. Update twt parameters, para_id=6~24:value\n");
    }
    return 0;
  }
  iVar4 = sscanf(param_2,"%u:%u:%u:%u:%u:%u:%u:%u:%u",&local_44,&local_38,&local_34,&local_30,
                 &local_2c,&local_28,&local_24,&local_20,local_1c);
  if (2 < DebugLevel) {
    printk("para_num=%d, para_id=%d\n",iVar4,local_44);
  }
  if (local_44 < 6 && iVar4 != 1) goto LAB_000decb0;
  if (local_44 - 6 < 0x12) {
    if (iVar4 != 2) goto LAB_000decb0;
  }
  else if (local_44 == 0x18 && iVar4 != 9) goto LAB_000decb0;
  uVar1 = (undefined1)local_38;
  uVar2 = (undefined2)local_38;
  switch(local_44) {
  case 0:
    if (2 < DebugLevel) {
      printk("agrt_tbl_idx=%d\n",__LANCHOR3 & 0xff);
      if (DebugLevel < 3) {
LAB_000def3c:
        if (DebugLevel < 3) {
LAB_000defcc:
          if (DebugLevel < 3) {
LAB_000df05c:
            if (DebugLevel < 3) {
LAB_000df0ec:
              if (2 < DebugLevel) {
                printk("sta_list[%d,%d,%d,%d,%d,%d,%d,%d]\n",DAT_005f361c & 0xffff,
                       DAT_005f361c._2_2_,DAT_005f3620 & 0xffff,DAT_005f3620 >> 0x10,
                       DAT_005f3624 & 0xffff,DAT_005f3624 >> 0x10,DAT_005f3628 & 0xffff,
                       DAT_005f3628 >> 0x10);
                return 1;
              }
            }
            else {
              printk("reserved_a=%d\n",DAT_005f3615);
              if (2 < DebugLevel) {
                printk("reserved_b=%d\n",DAT_005f3616);
LAB_000df0a4:
                if ((2 < DebugLevel) &&
                   (printk("grp_member_cnt=%d\n",_DAT_005f3618 & 0xff), 2 < DebugLevel)) {
                  printk("reserved_d=%d\n",DAT_005f361a);
                  goto LAB_000df0ec;
                }
              }
            }
          }
          else {
            printk("agrt_sp_wake_intvl_mantissa=%d\n",_DAT_005f3610 & 0xffff);
            if (2 < DebugLevel) {
              printk("agrt_sp_wake_intvl_exponent=%d\n",DAT_005f3612);
LAB_000df014:
              if (DebugLevel < 3) goto LAB_000df0a4;
              printk("is_role_ap=%d\n",DAT_005f3613);
              if (2 < DebugLevel) {
                printk("agrt_para_bitmap=%d\n",_DAT_005f3614 & 0xff);
                goto LAB_000df05c;
              }
            }
          }
        }
        else {
          printk("agrt_sp_duration=%d\n",DAT_005f3606);
          if (2 < DebugLevel) {
            printk("bss_idx=%d\n",DAT_005f3607);
LAB_000def84:
            if (DebugLevel < 3) goto LAB_000df014;
            printk("agrt_sp_start_tsf_low=%d\n",DAT_005f3608);
            if (2 < DebugLevel) {
              printk("agrt_sp_start_tsf_high=%d\n",DAT_005f360c);
              goto LAB_000defcc;
            }
          }
        }
      }
      else {
        printk("agrt_ctrl_flag=%d\n",DAT_005f3601);
        if (2 < DebugLevel) {
          printk("own_mac_idx=%d\n",DAT_005f3602);
          if (DebugLevel < 3) goto LAB_000def84;
          printk("flow_id=%d\n",DAT_005f3603);
          if (2 < DebugLevel) {
            printk("peer_id_grp_id=%d\n",_DAT_005f3604 & 0xffff);
            goto LAB_000def3c;
          }
        }
      }
    }
  default:
switchD_000ded7c_caseD_4:
    break;
  case 1:
    mt_asic_twt_agrt_update
              (iVar3,__LANCHOR3,_DAT_005f3604,DAT_005f3608,DAT_005f360c,_DAT_005f3610,_DAT_005f3614,
               _DAT_005f3618,DAT_005f361c,DAT_005f3620,DAT_005f3624,DAT_005f3628);
    break;
  case 2:
    twt_resource_dump(iVar3);
    break;
  case 3:
    twt_get_current_tsf(iVar3,&local_40);
    if (2 < DebugLevel) {
      printk("current_tsf(0x%.8x, 0x%.8x)\n",local_3c,local_40);
      return 1;
    }
    goto switchD_000ded7c_caseD_4;
  case 6:
    __LANCHOR3 = CONCAT31(_DAT_005f3601,uVar1);
    break;
  case 7:
    __LANCHOR3 = CONCAT11(uVar1,_LANCHOR3);
    break;
  case 8:
    __LANCHOR3 = CONCAT12(uVar1,__LANCHOR3);
    break;
  case 9:
    __LANCHOR3 = CONCAT13(uVar1,__LANCHOR3);
    break;
  case 10:
    _DAT_005f3604 = CONCAT22(_DAT_005f3606,uVar2);
    break;
  case 0xb:
    _DAT_005f3604 = CONCAT12(uVar1,DAT_005f3604);
    break;
  case 0xc:
    _DAT_005f3604 = CONCAT13(uVar1,_DAT_005f3604);
    break;
  case 0xd:
    DAT_005f3608 = local_38;
    break;
  case 0xe:
    DAT_005f360c = local_38;
    break;
  case 0xf:
    _DAT_005f3610 = CONCAT22(_DAT_005f3612,uVar2);
    break;
  case 0x10:
    _DAT_005f3610 = CONCAT12(uVar1,DAT_005f3610);
    break;
  case 0x11:
    _DAT_005f3610 = CONCAT13(uVar1,_DAT_005f3610);
    break;
  case 0x12:
    _DAT_005f3614 = CONCAT31(_DAT_005f3615,uVar1);
    break;
  case 0x13:
    _DAT_005f3614 = CONCAT11(uVar1,DAT_005f3614);
    break;
  case 0x14:
    _DAT_005f3614 = CONCAT22(uVar2,_DAT_005f3614);
    break;
  case 0x15:
    _DAT_005f3618 = CONCAT31(_DAT_005f3619,uVar1);
    break;
  case 0x16:
    _DAT_005f3618 = CONCAT11(uVar1,DAT_005f3618);
    break;
  case 0x17:
    _DAT_005f3618 = CONCAT22(uVar2,_DAT_005f3618);
    break;
  case 0x18:
    os_move_mem(&DAT_005f361c,&local_38,0x10);
  }
  return 1;
}

