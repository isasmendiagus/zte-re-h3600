// module: mt7915.ko
// function: rt_ioctl_giwscan @ 0x6e11c
// size: 1456 bytes
//

undefined4 rt_ioctl_giwscan(undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  byte bVar1;
  undefined1 uVar2;
  undefined3 uVar3;
  bool bVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 uVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  uint uVar14;
  uint uVar15;
  int local_8c;
  undefined4 local_88;
  byte local_84;
  undefined1 uStack_83;
  undefined1 uStack_82;
  undefined1 uStack_81;
  ushort uStack_80;
  undefined1 uStack_7e;
  undefined1 uStack_7d;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 local_74;
  int local_70;
  undefined4 *local_6c;
  
  uVar5 = RtmpOsGetNetDevPriv();
  puVar6 = (undefined4 *)RTMP_COM_IoctlHandle(uVar5,0,0x5011,0,0,0);
  if (puVar6 != (undefined4 *)0x0) {
    if (DebugLevel < 3) {
      return 0xffffff9c;
    }
    printk("INFO::Network is down!\n");
    return 0xffffff9c;
  }
  local_74 = RtmpDevPrivFlagsGet(param_1);
  local_6c = puVar6;
  iVar7 = DetermineCallerInterface(param_1,uVar5);
  if (iVar7 != 0) {
    return 0xfffffff2;
  }
  uVar8 = RtmpDevPrivFlagsGet(param_1);
  iVar7 = RTMP_STA_IoctlHandle(uVar5,0,0xa00e,0,&local_74,0,uVar8);
  puVar6 = local_6c;
  puVar10 = local_6c;
  if (iVar7 != 0) {
    uVar5 = 0xffffffea;
    goto LAB_0006e1dc;
  }
  if (local_70 == 0) {
    *(undefined2 *)(param_3 + 4) = 0;
    uVar5 = 0;
    goto LAB_0006e1dc;
  }
  if (*(ushort *)(param_3 + 4) == 0) {
    puVar13 = param_4 + 0x400;
  }
  else {
    puVar13 = (undefined4 *)((int)param_4 + (uint)*(ushort *)(param_3 + 4));
  }
  if (puVar13 <= param_4) {
    uVar5 = 0xfffffff9;
    goto LAB_0006e1dc;
  }
  __memzero(&local_88);
  local_84 = 1;
  uStack_83 = 0;
  local_88 = CONCAT22(0x8b15,(undefined2)local_88);
  uVar8 = *local_6c;
  uStack_82 = (undefined1)uVar8;
  uStack_81 = (undefined1)((uint)uVar8 >> 8);
  uStack_80 = (ushort)((uint)uVar8 >> 0x10);
  uStack_7e = (undefined1)*(undefined2 *)(local_6c + 1);
  uStack_7d = (undefined1)((ushort)*(undefined2 *)(local_6c + 1) >> 8);
  puVar10 = local_6c;
  if (puVar13 <= param_4 + 5) goto LAB_0006e600;
  local_88 = 0x8b150014;
  *param_4 = 0x8b150014;
  param_4[1] = CONCAT13(uStack_81,CONCAT12(uStack_82,1));
  param_4[2] = CONCAT13(uStack_7d,CONCAT12(uStack_7e,uStack_80));
  param_4[3] = local_7c;
  param_4[4] = uStack_78;
  __memzero(&local_88,0x14);
  local_88 = CONCAT22(0x8b01,(undefined2)local_88);
  if (*(byte *)((int)puVar6 + 6) < 0xf) {
    uVar14 = (uint)*(byte *)((int)puVar6 + 0x15);
    if (uVar14 == 0) {
      bVar4 = false;
    }
    else {
      pbVar9 = (byte *)(puVar6 + 2);
      bVar4 = false;
      do {
        pbVar9 = pbVar9 + 1;
        bVar1 = *pbVar9;
        if (0x97 < bVar1 || (bVar1 == 0x8c || bVar1 == 0x92)) {
          bVar4 = true;
        }
      } while (pbVar9 != (byte *)((int)puVar6 + uVar14 + 8));
    }
    uVar15 = (uint)*(byte *)((int)puVar6 + 0x22);
    if (uVar15 != 0) {
      pbVar9 = (byte *)((int)puVar6 + 0x15);
      do {
        pbVar9 = pbVar9 + 1;
        bVar1 = *pbVar9;
        if (0x97 < bVar1 || (bVar1 == 0x8c || bVar1 == 0x92)) {
          bVar4 = true;
        }
      } while (pbVar9 != (byte *)((int)puVar6 + uVar15 + 0x15));
    }
    if (*(char *)(puVar6 + 2) == '\0') {
      if (bVar4) {
        local_84 = 0x38;
        uStack_83 = 0x30;
        uStack_82 = 0x32;
        uStack_81 = 0x2e;
        uStack_80 = 0x3131;
        uStack_7e = 0x67;
        uStack_7d = 0;
      }
      else if ((uVar14 == 4) && (uVar15 == 0)) {
        local_84 = 0x38;
        uStack_83 = 0x30;
        uStack_82 = 0x32;
        uStack_81 = 0x2e;
        uStack_80 = 0x3131;
        uStack_7e = 0x62;
        uStack_7d = 0;
      }
      else {
        local_84 = 0x38;
        uStack_83 = 0x30;
        uStack_82 = 0x32;
        uStack_81 = 0x2e;
        uStack_80 = 0x3131;
        uStack_7e = 0x62;
        uStack_7d = 0x2f;
        local_7c = CONCAT22(local_7c._2_2_,0x67);
      }
    }
    else if (bVar4) {
      uStack_81 = (undefined1)((uint)_LC28 >> 0x18);
      uStack_82 = (undefined1)((uint)_LC28 >> 0x10);
      uStack_83 = (undefined1)((uint)_LC28 >> 8);
      local_84 = (byte)_LC28;
      uStack_7d = 0x2f;
      uStack_7e = 0x67;
      uStack_80 = 0x3131;
                    /* WARNING: Ignoring partial resolution of indirect */
      local_7c._0_2_ = 0x6e;
    }
    else {
      local_7c = 0x6e2f67;
      local_84 = 0x38;
      uStack_83 = 0x30;
      uStack_82 = 0x32;
      uStack_81 = 0x2e;
      uStack_80 = 0x3131;
      uStack_7e = 0x62;
      uStack_7d = 0x2f;
    }
  }
  else if (*(char *)(puVar6 + 2) == '\0') {
    local_84 = (byte)_LC27;
    uStack_83 = (undefined1)((uint)_LC27 >> 8);
    uStack_82 = (undefined1)((uint)_LC27 >> 0x10);
    uStack_81 = (undefined1)((uint)_LC27 >> 0x18);
    uStack_80 = (ushort)DAT_002bfe58;
    uStack_7e = (undefined1)((uint)DAT_002bfe58 >> 0x10);
    uStack_7d = (undefined1)((uint)DAT_002bfe58 >> 0x18);
  }
  else {
    uStack_81 = 0x2e;
    uStack_82 = 0x32;
    uStack_83 = 0x30;
    local_84 = 0x38;
    uStack_7d = 0x2f;
    uStack_7e = 0x61;
    uStack_80 = 0x3131;
                    /* WARNING: Ignoring partial resolution of indirect */
    local_7c._0_2_ = 0x6e;
  }
  puVar6 = param_4 + 10;
  if (puVar6 < puVar13) {
    local_88 = 0x8b010014;
    param_4[5] = 0x8b010014;
    param_4[6] = CONCAT13(uStack_81,CONCAT12(uStack_82,CONCAT11(uStack_83,local_84)));
    param_4[7] = CONCAT13(uStack_7d,CONCAT12(uStack_7e,uStack_80));
    param_4[8] = local_7c;
    param_4[9] = uStack_78;
    if (param_4 + 5 != puVar6) {
      __memzero(&local_88,0x14);
      puVar10 = local_6c;
      uStack_7e = 1;
      uStack_7d = 0;
      local_88 = CONCAT22(0x8b1b,(undefined2)local_88);
      bVar1 = *(byte *)((int)local_6c + 0x23);
      iVar7 = bVar1 + 8;
      puVar12 = (undefined4 *)((int)puVar6 + iVar7);
      uStack_80 = (ushort)bVar1;
      if (puVar12 < puVar13) {
        local_88 = CONCAT22(0x8b1b,(short)iVar7);
        param_4[10] = local_88;
        param_4[0xb] = (uint)CONCAT12(1,uStack_80);
        memcpy(param_4 + 0xc,local_6c + 9,(uint)bVar1);
        if (puVar6 != puVar12) {
          __memzero(&local_88,0x14);
          if (*(char *)((int)local_6c + 7) == '\0') {
            local_84 = 1;
          }
          else if (*(char *)((int)local_6c + 7) == '\x01') {
            local_84 = 2;
          }
          else {
            local_84 = 0;
          }
          uStack_81 = 0;
          uStack_82 = 0;
          uStack_83 = 0;
          puVar11 = puVar12 + 2;
          local_88 = 0x8b070008;
          puVar10 = local_6c;
          if (puVar11 < puVar13) {
            *(undefined4 *)((int)puVar6 + iVar7) = 0x8b070008;
            puVar12[1] = (uint)local_84;
            __memzero(&local_88,0x14);
            local_88 = CONCAT22(0x8b05,(undefined2)local_88);
            uVar2 = *(undefined1 *)((int)local_6c + 6);
            local_8c = 0;
            iVar7 = DetermineCallerInterface(param_1,uVar5);
            if (iVar7 != 0) {
              return 0xfffffff2;
            }
            uVar8 = RtmpDevPrivFlagsGet(param_1);
            RTMP_STA_IoctlHandle(uVar5,0,0x11,0,&local_8c,uVar2,uVar8);
            puVar6 = puVar12 + 5;
            uStack_7e = 0;
            uStack_80 = 1;
            iVar7 = local_8c * 100;
            local_84 = (byte)iVar7;
            uStack_83 = (undefined1)((uint)iVar7 >> 8);
            uStack_82 = (undefined1)((uint)iVar7 >> 0x10);
            uStack_81 = (undefined1)((uint)iVar7 >> 0x18);
            if (puVar6 < puVar13) {
              local_88 = CONCAT22(local_88._2_2_,0xc);
              puVar12[2] = local_88;
              puVar12[3] = iVar7;
              puVar12[4] = CONCAT13(uStack_7d,1);
              if (puVar11 != puVar6) {
                __memzero(&local_88,0x14,puVar6,&local_7c);
                local_88 = CONCAT22(0x8c01,(undefined2)local_88);
                uStack_81 = 0xf;
                local_84 = *(byte *)((int)local_6c + 0x67);
                uStack_83 = *(undefined1 *)(local_6c + 0x1a);
                uStack_82 = *(undefined1 *)((int)local_6c + 0x69);
                uVar3 = *(undefined3 *)((int)local_6c + 0x67);
                if (puVar12 + 7 < puVar13) {
                  local_88 = 0x8c010008;
                  puVar12[5] = 0x8c010008;
                  puVar12[6] = CONCAT13(0xf,uVar3);
                  puVar10 = local_6c;
                  if (puVar11 == puVar12 + 7) goto LAB_0006e600;
                }
                __memzero(&local_88,0x14);
                local_88 = CONCAT22(0x8b2b,(undefined2)local_88);
                puVar10 = local_6c;
                if (*(char *)(local_6c + 0x18) == '\0') {
                  uStack_7e = 0;
                  uStack_7d = 0x80;
                }
                else {
                  uStack_7e = 0;
                  uStack_7d = 8;
                }
                goto LAB_0006e600;
              }
            }
            goto LAB_0006e668;
          }
        }
      }
LAB_0006e600:
      uVar5 = 0xfffffff9;
      goto LAB_0006e1dc;
    }
  }
LAB_0006e668:
  uVar5 = 0xfffffff9;
  puVar10 = local_6c;
LAB_0006e1dc:
  if (puVar10 != (undefined4 *)0x0) {
    os_free_mem(puVar10);
    return uVar5;
  }
  return uVar5;
}

