// module: mt7915.ko
// function: WpaMessageSanity @ 0x11e054
// size: 2100 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4
WpaMessageSanity(int param_1,int param_2,undefined4 param_3,uint param_4,uint *param_5,int param_6,
                int param_7)

{
  undefined1 uVar1;
  undefined1 uVar2;
  void *__src;
  uint uVar3;
  int iVar4;
  byte bVar5;
  undefined4 uVar6;
  undefined1 uVar7;
  int iVar8;
  uint uVar9;
  size_t __n;
  int iVar10;
  undefined4 uVar11;
  bool bVar12;
  bool bVar13;
  undefined2 local_1ce;
  void *local_1cc;
  undefined4 local_1c8;
  undefined1 local_1c4 [24];
  undefined1 local_1ac [80];
  uint local_15c;
  uint local_158;
  undefined2 local_154;
  undefined1 local_152;
  
  local_1cc = (void *)0x0;
  iVar8 = *(int *)(param_6 + 8);
  if (5 < param_4 - 1) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("The message type is invalid(%d)!\n",param_4);
    return 0;
  }
  os_alloc_mem(0,&local_1cc,0xff);
  if (local_1cc == (void *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Allocate memory fail!!!\n","WpaMessageSanity");
    return 0;
  }
  __memzero(local_1c4,0x18);
  __memzero(local_1ac,0x50);
  __memzero(local_1cc,0xff);
  __memzero(&local_1ce,2);
  local_1ce = *(ushort *)(param_2 + 5);
  uVar3 = *param_5;
  if (param_4 == 5 || (param_4 & 0xfd) == 1) {
    __memzero(&local_15c,8);
    iVar10 = RTMPCompareMemory(param_2 + 9,param_5 + 0xe4,8);
    if ((iVar10 != 1) && (iVar10 = RTMPCompareMemory(param_2 + 9,&local_15c,8), iVar10 != 0)) {
LAB_0011e2b4:
      if (param_4 < 5) {
        if (-1 < DebugLevel) {
          printk("Replay Counter Different in pairwise msg %d of 4-way handshake!\n",param_4);
        }
      }
      else if (-1 < DebugLevel) {
        printk("Replay Counter Different in group msg %d of 2-way handshake!\n",param_4 - 4);
      }
      hex_dump("Receive replay counter ",param_2 + 9,8);
      hex_dump("Current replay counter ",param_5 + 0xe4,8);
      uVar7 = 0x65;
      goto LAB_0011e300;
    }
    uVar9 = *param_5;
  }
  else {
    uVar9 = uVar3;
    if ((param_4 == 4 || (param_4 & 0xfb) == 2) &&
       (iVar10 = memcmp((void *)(param_2 + 9),param_5 + 0xe4,8), iVar10 != 0)) goto LAB_0011e2b4;
  }
  if ((uVar9 & 0x30000) == 0) {
    if ((char)param_5[0xa1] == '\x02') {
      __n = 0x18;
    }
    else {
      __n = 0x10;
    }
  }
  else {
    __n = 0x18;
  }
  if (param_4 != 1) {
    uVar7 = *(undefined1 *)(param_2 + 2);
    uVar1 = *(undefined1 *)(param_2 + 3);
    memcpy(&local_15c,(void *)(param_2 + 0x51),__n);
    iVar10 = CONCAT11(uVar7,uVar1) + 4;
    __memzero((void *)(param_2 + 0x51),__n);
    if (2 < DebugLevel) {
      printk("%s(): peer KeyDescVer = %d\n","WpaMessageSanity",local_1ce._1_1_ & 7);
    }
    bVar5 = local_1ce._1_1_ & 7;
    if (bVar5 == 1) {
      RT_HMAC_MD5(param_7,0x10,param_2,iVar10,local_1c4,0x10);
    }
    else if (bVar5 == 2) {
      RT_HMAC_SHA1(param_7,0x10,param_2,iVar10,local_1ac,0x14);
    }
    else if ((local_1ce & 0x700) == 0) {
      if ((*param_5 & 0x30000) == 0) {
LAB_0011e1e0:
        local_1c8 = 0x10;
        AES_CMAC(param_2,iVar10,param_7,0x10,local_1c4,&local_1c8);
      }
      else {
        RT_HMAC_SHA384(param_7,0x18,param_2,iVar10,local_1c4,0x18);
      }
    }
    else if (((*param_5 & 0x2000) != 0) || (bVar5 == 3)) goto LAB_0011e1e0;
    iVar10 = memcmp(&local_15c,local_1c4,0x10);
    if (iVar10 != 0) {
      if (param_4 < 5) {
        if (-1 < DebugLevel) {
          printk("MIC Different in pairwise msg %d of 4-way handshake!\n",param_4);
        }
      }
      else if (-1 < DebugLevel) {
        printk("MIC Different in group msg %d of 2-way handshake!\n",param_4 - 4);
      }
      hex_dump("Received MIC",&local_15c,0x10);
      uVar7 = 0x66;
      hex_dump("Desired  MIC",local_1c4,0x10);
      goto LAB_0011e300;
    }
  }
  iVar10 = param_2 + __n + 0x48;
  uVar9 = (uint)CONCAT11(*(undefined1 *)(param_2 + __n + 0x51),*(undefined1 *)(iVar10 + 10));
  if (uVar9 != 0) {
    __src = (void *)(iVar10 + 0xb);
    bVar12 = (uVar3 & 0x18) == 0;
    if (param_4 == 5 || param_4 == 3 && bVar12) {
      bVar13 = (local_1ce & 0x700) == 0;
      if ((bVar13 || (local_1ce._1_1_ & 7) != 2) && (!bVar13 && (local_1ce._1_1_ & 7) != 3)) {
        TKIP_GTK_KEY_UNWRAP(param_7 + 0x10,param_2 + 0x31,__src,uVar9,local_1cc);
        uVar3 = (uint)*(byte *)(iVar10 + 10);
      }
      else {
        local_15c = 0;
        if (((*param_5 & 0x30000) == 0) && ((char)param_5[0xa1] != '\x02')) {
          uVar11 = 0x10;
          iVar4 = 0x10;
        }
        else {
          uVar11 = 0x20;
          iVar4 = 0x18;
        }
        AES_Key_Unwrap(__src,uVar9,param_7 + iVar4,uVar11,local_1cc,&local_15c);
        *(char *)(param_2 + __n + 0x51) = (char)(local_15c >> 8);
        uVar3 = local_15c & 0xff;
        *(char *)(iVar10 + 10) = (char)local_15c;
      }
      if (bVar12 < (param_4 == 5)) {
        uVar9 = ((uint)local_1ce._1_1_ << 0x1a) >> 0x1e;
      }
      else {
        uVar9 = 0;
      }
    }
    else {
      if ((param_4 != 2) && ((param_4 == 3) <= bVar12)) {
        if (3 < DebugLevel) {
          printk("The Key Data Length should be zero !!!\n");
        }
        goto LAB_0011e48c;
      }
      memmove(local_1cc,__src,uVar9);
      uVar3 = (uint)*(byte *)(iVar10 + 10);
      uVar9 = 0;
    }
    iVar10 = WPAParseEapolKeyData(param_1,local_1cc,uVar3,uVar9,param_4,bVar12,param_6);
    if (iVar10 == 0) {
      uVar7 = 0x67;
LAB_0011e300:
      __memzero(&local_15c,0x134);
      local_158 = *(uint *)(param_6 + 0xec);
      uVar3 = (uint)*(byte *)(param_6 + 0xe5);
      local_154 = *(undefined2 *)(param_6 + 0xf0);
      local_15c = uVar3;
      local_152 = uVar7;
      if (-1 < DebugLevel) {
        local_154._1_1_ = (undefined1)((ushort)local_154 >> 8);
        uVar1 = local_154._1_1_;
        uVar2 = (undefined1)local_154;
        printk("%s: %d key error: %02x:%02x:%02x:%02x:%02x:%02x, if_index=%d, reason=%d\n",
               "WpaMessageSanity",0x11d3,local_158 & 0xff,local_158 >> 8 & 0xff,
               local_158 >> 0x10 & 0xff,local_158 >> 0x18,uVar2,uVar1,uVar3,uVar7);
        uVar3 = (uint)*(byte *)(param_6 + 0xe5);
      }
      iVar10 = uVar3 * 0x5834 + param_1;
      *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + iVar10 + 0x24) =
           *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + iVar10 + 0x24) + 1;
      Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa23d,&local_15c,0x134,0,0);
      if ((iVar8 == 0) || (*(int *)(iVar8 + 0x14) != 2)) {
        __ZTE_STA_Assoc_Process(param_1,0xc,0,0,0,uVar7,param_6,"WpaMessageSanity",0x11e7);
      }
      else if (*(byte *)(iVar8 + 0x1a) < 0xf) {
        __ZTE_STA_Assoc_Process(param_1,0xc,0,0xffffffff,0,uVar7,param_6,"WpaMessageSanity",0x11df);
      }
      else {
        __ZTE_STA_Assoc_Process(param_1,0xc,0,0xfffffffb,0,uVar7,param_6,"WpaMessageSanity",0x11e3);
      }
      if (local_1cc != (void *)0x0) {
        os_free_mem();
      }
      return 0;
    }
  }
LAB_0011e48c:
  if ((iVar8 == 0) || (*(int *)(iVar8 + 0x14) != 2)) {
    __ZTE_STA_Assoc_Process(param_1,0xc,0,0,0,0,param_6,"WpaMessageSanity",0x11bd);
  }
  else {
    if (*(byte *)(iVar8 + 0x1a) < 0xf) {
      uVar11 = 0x11b5;
      uVar6 = 0xffffffff;
    }
    else {
      uVar11 = 0x11b9;
      uVar6 = 0xfffffffb;
    }
    __ZTE_STA_Assoc_Process(param_1,0xc,0,uVar6,0,0,param_6,"WpaMessageSanity",uVar11);
  }
  if (local_1cc == (void *)0x0) {
    return 1;
  }
  os_free_mem(local_1cc);
  return 1;
}

