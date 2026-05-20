// module: mt7915.ko
// function: send_veri_pkt @ 0x1d561c
// size: 1516 bytes
//

int send_veri_pkt(int *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char cVar6;
  int iVar7;
  ushort uVar8;
  uint uVar9;
  uint *puVar10;
  uint uVar11;
  int iVar12;
  bool bVar13;
  uint *local_48;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  undefined2 local_30;
  undefined2 uStack_2e;
  undefined2 uStack_2c;
  undefined2 local_2a;
  uint local_28;
  uint local_24;
  
  local_48 = (uint *)0x0;
  pbVar2 = (byte *)hc_get_chip_cap(param_1[0x29e5e8]);
  uVar11 = (uint)*pbVar2;
  local_44 = 0;
  os_alloc_mem(0,&local_48,0x400);
  if (local_48 == (uint *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: buf Allocate memory fail!!!\n","send_veri_pkt");
    return 0;
  }
  __memzero(local_48,0x400);
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  puVar10 = local_48;
  if (param_1[0x29f317] != 2) {
    if (0 < DebugLevel) {
      printk("%s: state error:%d\n","send_veri_pkt");
    }
LAB_001d56ac:
    os_free_mem(local_48);
    return 0;
  }
  iVar12 = param_1[0x29f31a];
  uVar4 = uVar11 + iVar12;
  if (0x400 < uVar4) {
    if (0 < DebugLevel) {
      printk("%s: txd_size:%d pkt length:%d exceed:%d bytes\n","veri_pkt_ctnt_len_sanity_check",
             uVar11,iVar12,0x400);
    }
    goto LAB_001d56ac;
  }
  iVar7 = param_1[0x29f318];
  if (iVar3 == 0) goto LAB_001d57cc;
  switch(iVar7) {
  case 0:
    local_38 = 0;
    MgtMacHeaderInit(param_1,(int)local_48 + uVar11,(char)param_1[0x29f319],0,param_1 + 0x29f31b,
                     (int)param_1 + 0xa7cc72,param_1 + 0x29f31e);
    MakeOutgoingFrame((int)puVar10 + uVar11 + 0x18,&local_38,param_1[0x29f31a] + -0x18,
                      (int)param_1 + 0xa7cc7e,0xffffffff);
    iVar7 = param_1[0x29f318];
    iVar12 = param_1[0x29f31a];
    break;
  case 1:
    if (param_1[0x29f319] == 8) {
      iVar12 = (int)local_48 + uVar11;
      BarHeaderInit(param_1,iVar12,param_1 + 0x29f31b,(int)param_1 + 0xa7cc72);
      memcpy((void *)(iVar12 + 0x10),(void *)((int)param_1 + 0xa7cc7e),param_1[0x29f31a] - 0x10);
      iVar7 = param_1[0x29f318];
      iVar12 = param_1[0x29f31a];
      break;
    }
    if (param_1[0x29f319] == 10) {
      local_38 = CONCAT22(local_38._2_2_,*(undefined2 *)((int)param_1 + 0xa7cc7e));
      ComposePsPoll(param_1,(int)local_48 + uVar11,*(undefined2 *)((int)param_1 + 0xa7cc7e),
                    param_1 + 0x29f31b,(int)param_1 + 0xa7cc72);
      iVar7 = param_1[0x29f318];
      iVar12 = param_1[0x29f31a];
      param_1[0x29f316] = param_1[0x29f316] | 0x10;
      break;
    }
    goto LAB_001d57d8;
  case 2:
    __memzero(&local_38,0x18);
    uVar9 = param_1[0x29f316];
    puVar10 = (uint *)((int)puVar10 + uVar11);
    uVar4 = local_38 & 0xfffffff3;
    bVar1 = (byte)uVar4;
    if ((uVar9 & 1) == 0) {
      cVar6 = '\0';
      if ((uVar9 & 2) != 0) {
        cVar6 = '\b';
      }
      bVar1 = bVar1 & 0xf | 8 | cVar6 << 4;
    }
    else {
      if ((uVar9 & 2) == 0) {
        cVar6 = '\x04';
      }
      else {
        cVar6 = '\f';
        bVar1 = (byte)local_38 & 0xf3;
      }
      bVar1 = bVar1 & 0xf | 8 | cVar6 << 4;
    }
    local_38 = CONCAT31((int3)(uVar4 >> 8),bVar1);
    if (*(int *)(iVar3 + 0x14) == 1) {
      local_38 = local_38 | 0x200;
    }
    else if (*(int *)(iVar3 + 0x14) == 2) {
      local_38 = local_38 | 0x100;
    }
    local_34 = param_1[0x29f31b];
    bVar13 = (uVar9 & 0x2000) != 0;
    local_28 = param_1[0x29f31e];
    local_30 = (undefined2)param_1[0x29f31c];
    local_2a = *(undefined2 *)((int)param_1 + 0xa7cc76);
    uVar8 = *(ushort *)(param_1 + 0x29f31f);
    local_24 = CONCAT22(local_24._2_2_,uVar8);
    if (bVar13) {
      uVar8 = (ushort)local_38._1_1_;
    }
    uStack_2e = (undefined2)*(undefined4 *)((int)param_1 + 0xa7cc72);
    uStack_2c = (undefined2)((uint)*(undefined4 *)((int)param_1 + 0xa7cc72) >> 0x10);
    if (bVar13) {
      local_38 = CONCAT22(local_38._2_2_,CONCAT11((char)uVar8,(byte)local_38)) | 0x8000;
    }
    puVar10[2] = param_1[0x29f31c];
    *puVar10 = local_38;
    puVar10[1] = local_34;
    puVar10[3] = CONCAT22(local_2a,uStack_2c);
    puVar10[4] = local_28;
    puVar10[5] = local_24;
    uVar4 = param_1[0x29f316];
    if ((uVar4 & 2) == 0) {
      iVar12 = 0x18;
    }
    else if ((uVar4 & 0x2000) == 0) {
      iVar12 = 0x1a;
    }
    else {
      iVar12 = 0x1e;
      *(int *)((int)puVar10 + 0x1a) = param_1[0x29f421];
      uVar4 = param_1[0x29f316];
    }
    if ((uVar4 & 1) == 0) {
      memcpy((void *)((int)puVar10 + iVar12),(void *)((int)param_1 + 0xa7cc7e),
             param_1[0x29f31a] - iVar12);
    }
    pcVar5 = "802.11 data buf";
    goto LAB_001d57b8;
  case 3:
    *local_48 = param_1[0x29f31b];
    *(short *)(local_48 + 1) = (short)param_1[0x29f31c];
    *(undefined4 *)((int)local_48 + 6) = *(undefined4 *)((int)param_1 + 0xa7cc72);
    *(undefined2 *)((int)local_48 + 10) = *(undefined2 *)((int)param_1 + 0xa7cc76);
    memcpy(local_48 + 3,(void *)((int)param_1 + 0xa7cc7e),param_1[0x29f31a] - 0xc);
    pcVar5 = "802.3 buf";
LAB_001d57b8:
    hex_dump(pcVar5,puVar10,param_1[0x29f31a]);
    iVar7 = param_1[0x29f318];
    iVar12 = param_1[0x29f31a];
    break;
  default:
    if (0 < DebugLevel) {
      printk("%s: try to contruct wrong type:%d\n","construct_veri_pkt");
      iVar7 = param_1[0x29f318];
      iVar12 = param_1[0x29f31a];
    }
  }
LAB_001d57cc:
  if (iVar7 == 3) {
    iVar12 = RTMPAllocateNdisPacket(param_1,&local_44,0,0,local_48,iVar12);
  }
  else {
    uVar4 = iVar12 + uVar11;
LAB_001d57d8:
    iVar12 = RTMPAllocateNdisPacket(param_1,&local_44,0,0,local_48,uVar4);
  }
  if (iVar12 == 0) {
    if (iVar3 != 0) {
      *(undefined1 *)(local_44 + 0x2d) = *(undefined1 *)(iVar3 + 0xc);
      RTMP_QueryPacketInfo(local_44,&local_38,&local_40,&local_3c);
      if (2 < DebugLevel) {
        printk("%s:: allocate pkt, wdev_idx=%d, TotalPacketLength:%u, pkt_va:%p, VA:%p, Len:%u\n",
               "send_veri_pkt",*(undefined1 *)(iVar3 + 0xc),CONCAT22(uStack_2e,local_30),local_44,
               local_40,local_3c);
      }
      if (param_1[0x29f318] == 3) {
        iVar12 = wdev_tx_pkts(param_1,&local_44,1,iVar3);
      }
      else {
        *(undefined1 *)(local_44 + 0x36) = 9;
        *(undefined1 *)(local_44 + 0x4f) = 2;
        *(undefined1 *)(local_44 + 0x4d) = 0;
        iVar12 = send_mlme_pkt(param_1,local_44,iVar3,0,0);
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: AllocateNdisPacket fail\n","send_veri_pkt");
  }
  os_free_mem(local_48);
  return iVar12;
}

