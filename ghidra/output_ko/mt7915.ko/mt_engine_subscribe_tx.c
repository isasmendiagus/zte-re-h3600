// module: mt7915.ko
// function: mt_engine_subscribe_tx @ 0x255b90
// size: 2168 bytes
//

int mt_engine_subscribe_tx(int param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  uint *puVar2;
  char cVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  undefined1 local_4e;
  byte local_4d;
  undefined4 local_4c;
  undefined2 local_48;
  byte local_46;
  byte local_45;
  undefined1 local_44;
  undefined1 local_43;
  byte local_42;
  byte local_41;
  undefined1 local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  uint local_3c;
  uint local_34;
  
  iVar9 = 0;
  local_4c = 0;
  sys_ad_zero_mem(&local_48,0x20);
  iVar7 = *(int *)(param_3 + 0xc08);
  if (iVar7 != 0) {
    iVar12 = *(int *)(param_3 + 0xc14);
    iVar11 = *(int *)(param_3 + 0xc10);
    if (iVar12 == 0 && iVar11 == 0) {
      iVar7 = 0;
      printk("%s: there are no pkt_tx_time/ipg!! ","mt_engine_calc_duty_cycle");
      printk("use default setting and set duty_cycle=%d\n",0);
      iVar11 = 0;
    }
    else if (iVar11 != 0 && iVar12 == 0) {
      iVar9 = __aeabi_uidiv(iVar11 * 100,iVar7);
      iVar9 = iVar9 - iVar11;
      *(int *)(param_3 + 0xc14) = iVar9;
      iVar12 = mt_engine_calc_ipg_param_by_ipg(param_3);
      if (iVar12 != 0) {
        printk("%s: calculate ipg_param fail!!\n","mt_engine_calc_duty_cycle");
      }
    }
    else {
      iVar9 = iVar12;
      if (iVar12 == 0 || iVar11 != 0) {
        printk("%s: already existed pkt_tx_time/ipg, ","mt_engine_calc_duty_cycle");
        printk("can\'t set duty_cycle!! ");
        printk("expected duty_cycle=%d%%\n",iVar7);
        iVar7 = __aeabi_uidiv(iVar11 * 100,iVar11 + iVar12);
        printk("%s: real duty_cycle=%d%%\n","mt_engine_calc_duty_cycle",iVar7);
      }
      else {
        iVar11 = __aeabi_uidiv(iVar7 * iVar12,100 - iVar7);
      }
    }
    printk("%s: duty_cycle=%d%%, ipg=%dus, pkt_tx_time=%dus\n","mt_engine_calc_duty_cycle",iVar7,
           iVar9,iVar11);
    *(int *)(param_3 + 0xc10) = iVar11;
    *(int *)(param_3 + 0xc08) = iVar7;
  }
  local_45 = *(byte *)(param_3 + 0xc57);
  local_46 = *(byte *)(param_3 + 0xc55);
  uVar6 = (uint)local_46;
  local_34 = (uint)*(ushort *)(param_3 + 0x1f6);
  local_44 = *(undefined1 *)(param_3 + 0xc5a);
  if (4 < local_45) {
    local_45 = 3;
  }
  local_43 = *(undefined1 *)(param_3 + 0xc5b);
  bVar1 = 1 < uVar6 - 8;
  local_3c = *(uint *)(param_3 + 0x1fc);
  local_42 = *(byte *)(param_3 + 0xc5c);
  uVar5 = (uint)local_42;
  if (bVar1 && uVar6 != 0xb) {
    local_41 = local_42;
    if (uVar6 == 10) {
      if (uVar5 == 2) {
        local_41 = 2;
      }
      else {
        local_41 = 1;
      }
    }
LAB_00255c5c:
    if (uVar6 == 10) {
      local_3e = *(undefined1 *)(param_3 + 0xcec);
      local_3d = *(undefined1 *)(param_3 + 0xced);
      uVar13 = *(undefined4 *)(param_3 + (uint)*(byte *)(param_3 + 0x20f) * 4 + 0x24);
    }
    else {
      local_42 = 0;
LAB_00255c68:
      local_3e = *(undefined1 *)(param_3 + 0xcec);
      local_3d = *(undefined1 *)(param_3 + 0xced);
      uVar13 = *(undefined4 *)(param_3 + (uint)*(byte *)(param_3 + uVar6 + 0x205) * 4 + 0x24);
      if (uVar6 < 10) goto LAB_00255e88;
      if (uVar6 == 0xc) {
        local_46 = 4;
      }
    }
    pcVar8 = (char *)(param_3 + 0x53c);
    iVar9 = param_3 + 0x51;
    do {
      local_4c = 0;
      if (*pcVar8 != '\0') {
        if (0x1a < *(uint *)(pcVar8 + 0x20)) {
          local_3c = *(uint *)(pcVar8 + 0x20);
        }
        local_40 = (undefined1)*(undefined4 *)(pcVar8 + 0x10);
        local_3f = (undefined1)*(undefined4 *)(pcVar8 + 0x18);
        local_43 = (undefined1)*(undefined4 *)(pcVar8 + 0x14);
        local_48 = (undefined2)*(undefined4 *)(pcVar8 + 4);
        iVar7 = net_ad_alloc_wtbl(param_2,iVar9,uVar13,&local_4c,&local_48);
        if (iVar7 != 0) goto LAB_00255f00;
        FUN_00253dbc(param_1,param_2,param_3,uVar13,iVar9,local_4c,&local_48);
        if (local_46 == 0xb) {
          cVar3 = pcVar8[8];
          uVar5 = *(uint *)(pcVar8 + 0xc) >> 1;
          uVar6 = 0;
          if (1 < uVar5 - 0x43) {
            if (uVar5 < 0x41) {
              if (uVar5 < 0x3d) {
                if (uVar5 < 0x35) {
                  if (uVar5 < 0x25) {
                    if (uVar5 == 0x24) {
                      uVar6 = 3;
                    }
                    else {
                      uVar6 = (uint)((int)((ulonglong)uVar5 * 0x38e38e39 >> 0x20) << 0x17) >> 0x18;
                    }
                  }
                  else {
                    uVar6 = (uVar5 % 0x25) * 0x400000 >> 0x18;
                  }
                }
                else {
                  uVar6 = (uVar5 % 0x35) * 0x800000 >> 0x18;
                }
              }
              else {
                uVar6 = uVar5 % 0x3d;
              }
            }
            else {
              uVar6 = (uVar5 % 0x41) * 2;
            }
          }
          iVar7 = param_3 + (uVar6 + (*(uint *)(pcVar8 + 0xc) & 1) * 4 & 0xff);
          if (cVar3 != '\x7f' &&
              (*(char *)(iVar7 + 0xbfd) == -1 && cVar3 != *(char *)(iVar7 + 0xbfd))) {
            *(char *)(iVar7 + 0xbfd) = cVar3;
            if (cVar3 == -0x38) {
              *(undefined1 *)(iVar7 + 0xbfe) = 0x72;
            }
            else if (cVar3 == -0x30) {
              *(undefined1 *)(iVar7 + 0xbfe) = 0x73;
              *(undefined1 *)(iVar7 + 0xbff) = 0x73;
              *(undefined1 *)(iVar7 + 0xc00) = 0x73;
            }
          }
        }
        else {
          mt_engine_calc_phy(pcVar8,local_3c + 0xd,local_44,*(undefined1 *)(param_3 + 0xc5c),
                             *(undefined1 *)(param_3 + 0xc70));
        }
      }
      pcVar8 = pcVar8 + 0x6c;
      iVar9 = iVar9 + 6;
    } while (pcVar8 != (char *)(param_3 + 0xbfc));
    if (*(byte *)(param_3 + 0xc55) - 0xb < 2) {
      pcVar10 = (char *)(param_3 + 0xbfc);
      pcVar8 = pcVar10;
      do {
        pcVar8 = pcVar8 + 1;
        if (*pcVar8 == -1) {
          *pcVar8 = 'q';
        }
      } while (pcVar8 != (char *)(param_3 + 0xc04));
      iVar9 = 0;
      do {
        pcVar10 = pcVar10 + 1;
        iVar7 = iVar9 + 1;
        printk("%s: allocation[%d] = 0x%x\n","mt_engine_subscribe_tx",iVar9,*pcVar10);
        iVar9 = iVar7;
      } while (iVar7 != 8);
      if (((*(code **)(param_1 + 0xd4) != (code *)0x0) &&
          (iVar7 = (**(code **)(param_1 + 0xd4))(param_2,2), iVar7 != 0)) ||
         ((*(code **)(param_1 + 0xe0) != (code *)0x0 &&
          (iVar7 = (**(code **)(param_1 + 0xe0))(uVar13,param_2,param_3), iVar7 != 0))))
      goto LAB_00255f00;
    }
  }
  else {
    iVar9 = uVar5 - 1;
    switch(iVar9) {
    case 0:
    case 1:
      local_41 = (byte)iVar9;
      break;
    case 2:
    case 3:
      if (uVar5 != 3) goto switchD_00255c34_default;
      local_41 = 2;
      bVar4 = 2;
      if (bVar1) goto LAB_00256188;
      goto LAB_00255e64;
    default:
switchD_00255c34_default:
      local_41 = 0;
    }
    if (bVar1) {
LAB_00256188:
      if (uVar6 != 0xb) goto LAB_00255c5c;
      if ((uVar5 == 0) || (uVar5 == 3)) {
        local_42 = 2;
      }
      else {
        local_42 = 1;
      }
      goto LAB_00255c68;
    }
    switch(iVar9) {
    case 0:
    case 1:
      bVar4 = 1;
      break;
    case 2:
    case 3:
      bVar4 = 2;
      break;
    default:
      bVar4 = 0;
    }
LAB_00255e64:
    local_42 = bVar4;
    local_3e = *(undefined1 *)(param_3 + 0xcec);
    local_3d = *(undefined1 *)(param_3 + 0xced);
    uVar13 = *(undefined4 *)(param_3 + (uint)*(byte *)(param_3 + uVar6 + 0x205) * 4 + 0x24);
LAB_00255e88:
    if (*(code **)(param_1 + 0xd4) != (code *)0x0) {
      (**(code **)(param_1 + 0xd4))(param_2,5);
    }
    if (local_46 == 0) {
      bVar4 = *(byte *)(param_3 + 0xc58) & 8;
      if ((*(byte *)(param_3 + 0xc58) & 8) != 0) {
        bVar4 = 1;
      }
      net_ad_set_preamble(param_2,bVar4);
    }
    local_40 = *(undefined1 *)(param_3 + 0xc58);
    local_3f = *(undefined1 *)(param_3 + 0xc59);
    iVar9 = net_ad_alloc_wtbl(param_2,param_3 + 0x51,uVar13,&local_4c,&local_48);
    if (iVar9 != 0) {
      iVar7 = 0x607;
      goto LAB_00255f00;
    }
    FUN_00253dbc(param_1,param_2,param_3,uVar13,param_3 + 0x51,local_4c,&local_48);
  }
  if (*(int *)(param_1 + 0x174) != 0) {
    uVar6 = 0;
    local_4d = 0;
    if (*(char *)(param_3 + 0x215) == '\0') {
      uVar6 = 0;
    }
    else {
      iVar9 = param_3;
      do {
        puVar2 = (uint *)(iVar9 + 0x354);
        iVar9 = iVar9 + 0x20;
        if (uVar6 < *puVar2) {
          uVar6 = *puVar2;
        }
        uVar6 = uVar6 & 0xff;
      } while (iVar9 != param_3 + ((byte)(*(char *)(param_3 + 0x215) - 1) + 1) * 0x20);
    }
    iVar7 = net_ad_get_wmm_idx(uVar13,&local_4d);
    if ((iVar7 != 0) || (iVar7 = (**(code **)(param_1 + 0x174))(param_2,local_4d,uVar6), iVar7 != 0)
       ) goto LAB_00255f00;
    printk("%s: limit aggregation to %d for WMM%d\n","mt_engine_subscribe_tx",uVar6,local_4d);
  }
  if ((*(code **)(param_1 + 0x178) == (code *)0x0) ||
     (iVar7 = (**(code **)(param_1 + 0x178))(param_2), iVar7 == 0)) {
    uVar6 = *(uint *)(param_3 + 0xc48);
    local_4e = 0;
    local_4d = 0;
    net_ad_get_band_idx(*(undefined4 *)(param_3 + 700),&local_4e);
    if ((int)uVar6 < 0) {
      uVar5 = uVar6 & 0xff;
      local_4d = (byte)uVar6;
    }
    else {
      net_ad_get_speidx(param_2,uVar6 & 0xffff,&local_4d);
      uVar5 = (uint)local_4d;
    }
    iVar9 = *(int *)(param_3 + 0x27c);
    if ((iVar9 != 0) && (*(char *)(param_3 + 0x215) != '\0')) {
      uVar6 = 0;
      while( true ) {
        uVar6 = uVar6 + 1 & 0xff;
        net_ad_fill_spe_antid(param_2,iVar9,uVar5,0);
        iVar9 = *(int *)(param_3 + uVar6 * 4 + 0x27c);
        if ((iVar9 == 0) || (*(byte *)(param_3 + 0x215) <= uVar6)) break;
        uVar5 = (uint)local_4d;
      }
      uVar5 = (uint)local_4d;
    }
    (**(code **)(param_1 + 0x150))(param_2,local_4e,*(undefined1 *)(param_3 + 0xc55),uVar5);
    return 0;
  }
LAB_00255f00:
  printk("%s: err=0x%04x\n","mt_engine_subscribe_tx",iVar7);
  return iVar7;
}

