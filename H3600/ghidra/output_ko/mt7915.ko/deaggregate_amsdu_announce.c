// module: mt7915.ko
// function: deaggregate_amsdu_announce @ 0xc8d54
// size: 1312 bytes
//

int deaggregate_amsdu_announce(int param_1,int param_2,undefined4 *param_3,uint param_4)

{
  undefined2 uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  undefined4 *__s2;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  bool bVar14;
  bool bVar15;
  int local_70;
  int local_44;
  int local_40;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined4 local_36;
  undefined2 local_32;
  undefined2 uStack_30;
  undefined2 uStack_2e;
  undefined2 uStack_2c;
  undefined2 local_2a;
  
  uVar5 = (uint)*(byte *)(param_2 + 0x2d);
  if (0x67 < uVar5) {
    if (-1 < DebugLevel) {
      printk("%s():invalud wdev_idx(%d)\n","deaggregate_amsdu_announce",uVar5);
    }
    *(int *)(param_1 + 0x9dcd8) = *(int *)(param_1 + 0x9dcd8) + 1;
    wlan_dbg_set_last_error(0,1,0xe4b,"deaggregate_amsdu_announce");
    RTMPFreeNdisPacket(param_1,param_2);
    return 0;
  }
  puVar6 = *(undefined4 **)(param_1 + uVar5 * 4 + 0xc);
  if (*(short *)((int)puVar6 + 0x8fa) == 0) {
    iVar8 = 0;
  }
  else {
    iVar8 = 4;
  }
  if (param_4 < 0xf) {
    local_70 = 0;
  }
  else {
    uVar5 = (uint)*(byte *)((int)param_3 + 0xd) + (uint)*(byte *)(param_3 + 3) * 0x100 & 0xffff;
    if (param_4 < (uVar5 + 0xe & 0xffff) || 0x5ee < uVar5) {
      local_70 = 1;
    }
    else {
      local_70 = 1;
      sVar2 = 0;
      uVar1 = 0;
      do {
        __s2 = (undefined4 *)((int)param_3 + 0xe);
        puVar10 = (undefined4 *)((int)param_3 + 6);
        iVar4 = memcmp(&SNAP_802_1H,__s2,6);
        cVar7 = (char)(uVar5 >> 8);
        uVar9 = uVar5;
        if (iVar4 == 0) {
          iVar4 = memcmp(&IPX,param_3 + 5,2);
          if ((iVar4 != 0) && (iVar4 = memcmp(&APPLE_TALK,param_3 + 5,2), iVar4 != 0))
          goto LAB_000c8ea4;
          puVar12 = (undefined4 *)0x0;
          local_36 = *param_3;
          local_32 = *(undefined2 *)(param_3 + 1);
          puVar13 = (undefined4 *)0x0;
          uStack_30 = (undefined2)*puVar10;
          uStack_2e = (undefined2)((uint)*puVar10 >> 0x10);
          uStack_2c = *(undefined2 *)((int)param_3 + 10);
          local_2a = CONCAT11((char)uVar5,cVar7);
          puVar11 = puVar12;
          if (cVar7 == -0x78) goto LAB_000c9020;
LAB_000c8eec:
          cVar7 = *(char *)(param_1 + 0x286285);
          puVar13 = puVar12;
        }
        else {
          iVar4 = memcmp(&SNAP_BRIDGE_TUNNEL,__s2,6);
          if (iVar4 == 0) {
LAB_000c8ea4:
            local_2a = *(undefined2 *)(param_3 + 5);
            local_36 = *param_3;
            local_32 = *(undefined2 *)(param_3 + 1);
            uStack_2c = *(undefined2 *)((int)param_3 + 10);
            uStack_30 = (undefined2)*puVar10;
            uStack_2e = (undefined2)((uint)*puVar10 >> 0x10);
            uVar9 = uVar5 - 8 & 0xffff;
            puVar12 = (undefined4 *)((int)param_3 + 0x16);
            puVar13 = __s2;
            puVar11 = (undefined4 *)(uint)(__s2 != (undefined4 *)0x0);
          }
          else {
            local_32 = *(undefined2 *)(param_3 + 1);
            puVar13 = (undefined4 *)0x0;
            local_36 = *param_3;
            uStack_2c = *(undefined2 *)((int)param_3 + 10);
            uStack_30 = (undefined2)*puVar10;
            uStack_2e = (undefined2)((uint)*puVar10 >> 0x10);
            local_2a = CONCAT11((char)uVar5,cVar7);
            puVar12 = __s2;
            puVar11 = puVar13;
          }
          __s2 = puVar12;
          puVar12 = puVar13;
          if ((char)local_2a != -0x78) goto LAB_000c8eec;
LAB_000c9020:
          puVar12 = puVar13;
          if ((local_2a._1_1_ != -0x72) || (os_alloc_mem(param_1,&local_44,0x930), local_44 == 0))
          goto LAB_000c8eec;
          (**(code **)(puVar6[0x241] + 0xb8))(param_1,puVar10,puVar6,&local_40);
          if (local_40 == 0) {
            printk(&_LC69,0xe73);
            dump_stack();
            if (local_40 != 0) goto LAB_000c907c;
          }
          else {
LAB_000c907c:
            iVar3 = local_40;
            iVar4 = local_44;
            memmove((void *)(local_44 + 0x20),__s2,uVar9);
            local_3c = 0;
            local_3b = 0;
            *(uint *)(iVar4 + 0x908) = uVar9 + 0x20;
            local_3a = 0;
            local_39 = 0;
            local_38 = 0;
            local_37 = 0;
            MlmeEnqueueForRecv(param_1,*(undefined2 *)(iVar3 + 0xe0),&local_3c,uVar9 + 0x20,iVar4,0,
                               puVar6,*(byte *)(iVar3 + 0xbd) >> 5);
          }
          os_free_mem(local_44);
          cVar7 = *(char *)(param_1 + 0x286285);
        }
        if (cVar7 == '\x01') {
          iVar4 = iVar8;
          if (puVar13 != (undefined4 *)0x0) {
            iVar4 = iVar8 + 0xe;
          }
          __s2 = (undefined4 *)((int)__s2 - iVar4);
          uVar9 = uVar9 + iVar4 & 0xffff;
          if (*(short *)((int)puVar6 + 0x8fa) != 0) {
            uVar1 = *(undefined2 *)(puVar6 + 0x23f);
            sVar2 = *(short *)((int)puVar6 + 0x8fa);
          }
          VLAN_8023_Header_Copy(sVar2,uVar1,&local_36,0xe,__s2,&TPID);
          cVar7 = *(char *)(param_1 + 0x286285);
        }
        if (cVar7 != '\0') {
          puVar11 = (undefined4 *)0x0;
        }
        puVar10 = __s2;
        if (puVar11 != (undefined4 *)0x0) {
          uVar9 = uVar9 + 0xe & 0xffff;
          puVar10 = (undefined4 *)((int)__s2 + -0xe);
          *puVar10 = local_36;
          *(uint *)((int)__s2 + -10) = CONCAT22(uStack_30,local_32);
          *(uint *)((int)__s2 + -6) = CONCAT22(uStack_2c,uStack_2e);
          *(undefined2 *)((int)__s2 + -2) = local_2a;
        }
        iVar4 = ClonePacket("hif_set_WPDMA"[param_1 + 0xc] == '\x01',*puVar6,param_2,puVar10,uVar9);
        if (iVar4 != 0) {
          announce_or_forward_802_3_pkt(param_1,iVar4,puVar6,*(undefined1 *)(param_1 + 0x286285));
        }
        uVar5 = uVar5 + 0x11 & 0xfffc;
        if ((0x5d8 < (uVar5 - 0x20 & 0xffff)) || (param_4 <= uVar5)) break;
        param_4 = param_4 - uVar5;
        param_3 = (undefined4 *)((int)param_3 + uVar5);
        if (param_4 < 0xf) break;
        local_70 = local_70 + 1;
        uVar5 = (uint)*(byte *)((int)param_3 + 0xd) + (uint)*(byte *)(param_3 + 3) * 0x100 & 0xffff;
        uVar9 = uVar5 + 0xe & 0xffff;
        bVar15 = 0x5ed < uVar5;
        bVar14 = uVar5 == 0x5ee;
        if (uVar5 < 0x5ef) {
          bVar15 = param_4 <= uVar9;
          bVar14 = uVar9 == param_4;
        }
      } while (!bVar15 || bVar14);
    }
  }
  RTMPFreeNdisPacket(param_1,param_2);
  return local_70;
}

