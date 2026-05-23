// module: mt7915.ko
// function: MATProto_IP_Tx @ 0x7a50c
// size: 908 bytes
//

uint MATProto_IP_Tx(int param_1,uint param_2,int param_3,undefined1 *param_4)

{
  undefined2 uVar1;
  char cVar3;
  ushort uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  void *__s1;
  int iVar8;
  uint uVar2;
  
  iVar8 = *(int *)(param_2 + 0xcc);
  iVar7 = *(int *)(param_1 + 0x20);
  if ((((*(byte *)(iVar8 + 6) & 1) == 0) &&
      (((((*(byte *)(iVar8 + 6) != 0 || *(char *)(iVar8 + 7) != '\0') ||
         *(char *)(iVar8 + 8) != '\0') || *(char *)(iVar8 + 9) != '\0') ||
       *(char *)(iVar8 + 10) != '\0') || *(char *)(iVar8 + 0xb) != '\0')) &&
     (*(int *)(param_3 + 0xc) != 0)) {
    FUN_0007a38c(param_1,iVar8 + 6);
  }
  if (*(char *)(param_3 + 9) != '\x11') {
    return 0;
  }
  iVar8 = param_3 + 0x14;
  if (*(short *)(param_3 + 0x16) != 0x4300 || *(short *)(param_3 + 0x14) != 0x4400) {
    return 0;
  }
  uVar5 = *(byte *)(param_2 + 0x72) & 1;
  if ((*(byte *)(param_2 + 0x72) & 1) != 0) {
    if ((*(uint *)(*(int *)(param_2 + 0xc4) + 0x20) & 0xffff) == 1) {
      uVar5 = 0;
    }
    else {
      uVar5 = skb_copy(param_2,0x20);
      g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
      if (uVar5 != 0) {
        iVar8 = *(int *)(uVar5 + 0xcc);
        if (CONCAT11(*(undefined1 *)(iVar8 + 0xc),*(undefined1 *)(iVar8 + 0xd)) == -0x7f00) {
          iVar8 = iVar8 + 0x26;
        }
        else {
          iVar8 = iVar8 + 0x22;
        }
      }
    }
  }
  uVar4 = *(ushort *)(iVar8 + 0x12) << 8 | *(ushort *)(iVar8 + 0x12) >> 8;
  if (2 < DebugLevel) {
    printk("is bootp packet! bootpFlag=0x%x\n",uVar4);
  }
  __s1 = (void *)(iVar8 + 0xf4);
  if (*(char *)(iVar7 + 0xa7c554) == '\x01') {
    if (*(char *)(param_1 + 0x18) == '\0') {
      if (uVar4 == 0x8000) {
        return uVar5;
      }
      goto LAB_0007a640;
    }
    iVar7 = RTMPLookupRepeaterCliEntry(*(undefined4 *)(param_1 + 0x20),0,param_4);
    if (iVar7 == 0) goto LAB_0007a638;
LAB_0007a6ec:
    if (*(char *)(param_1 + 0x18) == '\0') {
      return uVar5;
    }
    iVar7 = RTMPLookupRepeaterCliEntry(*(undefined4 *)(param_1 + 0x20),0,param_4,1);
    if (iVar7 == 0) {
      return uVar5;
    }
  }
  else {
LAB_0007a638:
    if (uVar4 == 0x8000) goto LAB_0007a6ec;
LAB_0007a640:
    if (DebugLevel < 3) {
      iVar7 = memcmp(__s1,&_LANCHOR0,4);
      if (iVar7 != 0) goto LAB_0007a6ec;
    }
    else {
      printk("the DHCP flag is a unicast, dhcp_magic=%02x:%02x:%02x:%02x\n",
             *(undefined1 *)(iVar8 + 0xf4),*(undefined1 *)(iVar8 + 0xf5),
             *(undefined1 *)(iVar8 + 0xf6),*(undefined1 *)(iVar8 + 0xf7));
      iVar7 = memcmp(__s1,&_LANCHOR0,4);
      if (iVar7 != 0) goto LAB_0007a6ec;
      if (2 < DebugLevel) {
        printk("dhcp magic macthed!\n");
      }
    }
    *(undefined2 *)(iVar8 + 0x12) = 0x80;
    if ((*(char *)(param_1 + 0x18) == '\0') ||
       (iVar7 = RTMPLookupRepeaterCliEntry(*(undefined4 *)(param_1 + 0x20),0,param_4,1), iVar7 == 0)
       ) goto LAB_0007a690;
  }
  if (*(char *)(iVar7 + 1) != '\x01') {
    printk(&_LC3,0x295);
    dump_stack();
  }
  memmove((void *)(iVar8 + 0x24),param_4,6);
  iVar7 = memcmp(__s1,&_LANCHOR0,4);
  if (iVar7 == 0) {
    pcVar6 = (char *)(iVar8 + 0xf8);
    cVar3 = *(char *)(iVar8 + 0xf8);
    while (cVar3 != '=') {
      pcVar6 = pcVar6 + (byte)pcVar6[1] + 2;
      cVar3 = *pcVar6;
      if ((cVar3 == -1) ||
         ((int)((*(ushort *)(iVar8 + 4) & 0xff) << 8 | (uint)(*(ushort *)(iVar8 + 4) >> 8)) <
          (int)pcVar6 - iVar8)) goto LAB_0007a690;
    }
    if (2 < DebugLevel) {
      printk("Client Identifier found, change Hardware Address to %02x:%02x:%02x:%02x:%02x:%02x\n",
             *param_4,param_4[1],param_4[2],param_4[3],param_4[4],param_4[5]);
    }
    memmove(pcVar6 + 3,param_4,6);
  }
LAB_0007a690:
  __memzero(iVar8 + 6,2);
  uVar2 = uVar5;
  if (uVar5 == 0) {
    uVar2 = param_2;
  }
  uVar1 = RTMP_UDP_Checksum(uVar2);
  *(undefined2 *)(iVar8 + 6) = uVar1;
  return uVar5;
}

