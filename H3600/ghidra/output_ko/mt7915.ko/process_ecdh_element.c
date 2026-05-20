// module: mt7915.ko
// function: process_ecdh_element @ 0x21bfd0
// size: 1904 bytes
//

undefined4
process_ecdh_element(undefined4 param_1,int param_2,char *param_3,int param_4,char param_5)

{
  ushort uVar1;
  void *pvVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  void *local_d0;
  int local_cc;
  void *local_c8;
  int local_c4;
  int local_c0;
  undefined4 local_bc;
  void *local_b8;
  uint local_b4;
  void *local_b0;
  void *local_ac;
  uint local_a8;
  uint local_a4;
  int *local_68 [17];
  
  local_d0 = (void *)0x0;
  local_cc = 0;
  local_c8 = (void *)0x0;
  local_c4 = 0;
  local_c0 = 0;
  local_bc = 0;
  if ((*param_3 == '\0') && (param_3[1] == '\0')) {
    return 0;
  }
  uVar1 = *(ushort *)(param_3 + 3);
  uVar3 = (uint)uVar1;
  if (uVar3 - 0x13 < 3) {
    *(char *)(param_2 + 0x958) = (char)uVar1;
    if (uVar3 == 0x14) {
      *(undefined1 *)(param_2 + 0x400) = 2;
    }
    else {
      if (uVar3 == 0x15) {
        *(undefined1 *)(param_2 + 0x400) = 3;
        return 0x4d;
      }
      *(undefined1 *)(param_2 + 0x400) = 1;
    }
    if (2 < DebugLevel) goto LAB_0021c4a8;
  }
  else {
    *(undefined1 *)(param_2 + 0x958) = 0;
    if (DebugLevel < 3) {
      return 0x4d;
    }
LAB_0021c4a8:
    printk("==> %s(), peer_group:%d\n","process_ecdh_element");
    if (*(char *)(param_2 + 0x958) == '\0') {
      return 0x4d;
    }
  }
  iVar4 = init_owe_group(param_2 + 0x940,uVar1 & 0xff);
  if (iVar4 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("==> %s(), init_owe_group failed. shall not happen!\n","process_ecdh_element");
    return 1;
  }
  uVar3 = param_4 - 3U & 0xff;
  iVar4 = os_alloc_mem(0,&local_d0,uVar3);
  if (iVar4 == 1) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("==> %s(), alloc buf for peer_pub failed...\n","process_ecdh_element");
    return 1;
  }
  memmove(local_d0,param_3 + 5,uVar3);
  pvVar2 = local_d0;
  local_68[0] = (int *)0x0;
  uVar7 = *(undefined4 *)(param_2 + 0x944);
  local_a8 = 0;
  ecc_point_init(local_68);
  Bignum_Bin2BI(pvVar2,uVar3,&local_a8);
  Bignum_Copy(local_a8,local_68[0]);
  iVar4 = *local_68[0];
  if (iVar4 == 0) {
    if (-1 < DebugLevel) {
      printk("%s, malloc failed\n","owe_process_peer_pubkey");
    }
LAB_0021c1e8:
    ecc_point_free(local_68);
    if (local_a8 != 0) {
      Bignum_Free(&local_a8);
    }
    if (-1 < DebugLevel) {
      uVar7 = 1;
      printk("==> %s(), owe_process_peer_pubkey failed...\n","process_ecdh_element");
      goto LAB_0021c214;
    }
  }
  else {
    if (local_68[0][1] == 0) {
      while (ecc_point_find_by_x(uVar7,iVar4,local_68[0] + 1,1), local_68[0][1] == 0) {
        iVar4 = *local_68[0];
      }
    }
    iVar4 = ecc_point_is_on_curve(uVar7,local_68[0]);
    if (iVar4 == 0) {
      if (0 < DebugLevel) {
        printk("%s, point is not on curve\n","owe_process_peer_pubkey");
      }
      goto LAB_0021c1e8;
    }
    ecc_point_set_z_to_one(local_68[0]);
    if (*(int *)(param_2 + 0x948) != 0) {
      ecc_point_free(param_2 + 0x948);
    }
    *(int **)(param_2 + 0x948) = local_68[0];
    if (local_a8 != 0) {
      Bignum_Free(&local_a8);
    }
    Bignum_Init(&local_cc);
    iVar4 = owe_calculate_secret(param_2 + 0x940,&local_cc);
    if (iVar4 == 0) {
      if (-1 < DebugLevel) {
        uVar7 = 1;
        printk("==> %s(), owe_calculate_secret failed...\n","process_ecdh_element");
        goto LAB_0021c214;
      }
      goto LAB_0021c210;
    }
    iVar8 = *(int *)(param_2 + 0x940);
    iVar4 = os_alloc_mem(0,&local_c0,*(undefined4 *)(iVar8 + 8));
    if (iVar4 == 1) {
LAB_0021c484:
      if (-1 < DebugLevel) {
        uVar7 = 1;
        printk("==> %s(), alloc buf for hkey failed...\n","process_ecdh_element");
        goto LAB_0021c214;
      }
    }
    else {
      Bignum_BI2Bin_with_pad(local_cc,local_c0,&local_bc,*(undefined4 *)(iVar8 + 8));
      iVar4 = os_alloc_mem(0,&local_c8,*(int *)(iVar8 + 8) + 2 + uVar3);
      pvVar2 = local_d0;
      if (iVar4 == 1) goto LAB_0021c484;
      puVar5 = *(undefined4 **)(param_2 + 0x94c);
      if (puVar5 != (undefined4 *)0x0) {
        iVar6 = *(int *)(param_2 + 0x940);
        uVar7 = *puVar5;
        local_b8 = (void *)0x0;
        local_b4 = 0;
        iVar4 = os_alloc_mem(0,&local_b8,*(undefined4 *)(iVar6 + 8));
        if (iVar4 == 1) {
          if (-1 < DebugLevel) {
            printk("==> %s(), alloc buf for material failed...\n","owe_calculate_pmkid");
          }
        }
        else {
          if (param_5 == '\0') {
            local_b0 = pvVar2;
            local_a8 = uVar3;
            Bignum_BI2Bin_with_pad(uVar7,local_b8,&local_b4,*(undefined4 *)(iVar6 + 8));
            local_ac = local_b8;
            local_a4 = local_b4;
          }
          else {
            Bignum_BI2Bin_with_pad(uVar7,local_b8,&local_b4,*(undefined4 *)(iVar6 + 8));
            local_b0 = local_b8;
            local_a8 = local_b4;
            local_ac = pvVar2;
            local_a4 = uVar3;
          }
          if (uVar1 == 0x14) {
            rt_sha384_vector(2,&local_b0,&local_a8,local_68);
          }
          else if (uVar1 != 0x15) {
            rt_sha256_vector(2,&local_b0,&local_a8,local_68);
          }
          hex_dump("OWE PMKID:",local_68,0x10);
          if (*(int *)(param_2 + 0x95c) != 0) {
            os_free_mem();
          }
          iVar4 = os_alloc_mem(0,param_2 + 0x95c,0x10);
          if (iVar4 == 1) {
            if (-1 < DebugLevel) {
              printk("==> %s(), alloc pmkid failed...\n","owe_calculate_pmkid");
            }
          }
          else {
            memmove(*(void **)(param_2 + 0x95c),local_68,0x10);
          }
        }
        if (local_b8 != (void *)0x0) {
          os_free_mem();
        }
        if (param_5 == '\0') {
          memmove(local_c8,local_d0,uVar3);
          Bignum_BI2Bin_with_pad(*puVar5,(int)local_c8 + uVar3,&local_c4,*(undefined4 *)(iVar8 + 8))
          ;
        }
        else {
          if (param_5 != '\x01') {
            if (-1 < DebugLevel) {
              uVar7 = 1;
              printk("==> %s(), parsing wrong type, shall not happen\n","process_ecdh_element");
              goto LAB_0021c214;
            }
            goto LAB_0021c210;
          }
          Bignum_BI2Bin_with_pad
                    (*puVar5,(int)local_c8 + local_c4,&local_c4,*(undefined4 *)(iVar8 + 8));
          memmove((void *)((int)local_c8 + local_c4),local_d0,uVar3);
        }
        *(ushort *)((int)local_c8 + uVar3 + local_c4) = uVar1;
        local_c4 = uVar3 + local_c4 + 2;
        if (uVar1 == 0x13) {
          RT_HMAC_SHA256(local_c8,local_c4,local_c0,local_bc,&local_a8,0x20);
          uVar7 = 0x20;
          HKDF_expand_sha256(&local_a8,0x20,"OWE Key Generation",0x12,param_2 + 0x30a,0x20);
        }
        else if (uVar1 == 0x14) {
          uVar7 = 0x30;
          RT_HMAC_SHA384(local_c8,local_c4,local_c0,local_bc,&local_a8,0x30);
          HKDF_expand_sha384(&local_a8,0x30,"OWE Key Generation",0x12,param_2 + 0x30a,0x30);
        }
        else {
          uVar7 = 0;
        }
        hex_dump("OWE PRK:",&local_a8,uVar7);
        hex_dump("OWE PMK:",param_2 + 0x30a,uVar7);
        uVar7 = 0;
        goto LAB_0021c214;
      }
      if (-1 < DebugLevel) {
        uVar7 = 1;
        printk("==> %s(), get own pub failed, shall not happen...\n","process_ecdh_element");
        goto LAB_0021c214;
      }
    }
  }
LAB_0021c210:
  uVar7 = 1;
LAB_0021c214:
  if (local_c0 != 0) {
    os_free_mem();
  }
  if (local_c8 != (void *)0x0) {
    os_free_mem();
  }
  if (local_cc != 0) {
    Bignum_Free(&local_cc);
  }
  if (local_d0 != (void *)0x0) {
    os_free_mem();
    return uVar7;
  }
  return uVar7;
}

