// module: tm.ko
// function: operListInit @ 0x58d1c
// size: 856 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 operListInit(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (s_tmFlowInfoListHead_u == (undefined4 *)0x0) {
    s_tmFlowInfoListHead_u = (undefined4 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (s_tmFlowInfoListHead_u == (undefined4 *)0x0) goto LAB_00059038;
    __memzero(s_tmFlowInfoListHead_u,0x14);
    puVar1 = s_tmFlowInfoListHead_u;
    s_tmFlowInfoListTail_u = s_tmFlowInfoListHead_u;
    *s_tmFlowInfoListHead_u = 0;
    puVar1[4] = 0;
    puVar1[1] = 0;
    puVar1[3] = 0;
    *(undefined1 *)(puVar1 + 2) = 0;
  }
  if (s_tmSubRamInfoListHead == (undefined4 *)0x0) {
    s_tmSubRamInfoListHead = (undefined4 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (s_tmSubRamInfoListHead == (undefined4 *)0x0) goto LAB_00059038;
    __memzero(s_tmSubRamInfoListHead,0x14);
    puVar1 = s_tmSubRamInfoListHead;
    s_tmSubRamInfoListTail = s_tmSubRamInfoListHead;
    *s_tmSubRamInfoListHead = 0;
    puVar1[4] = 0;
    puVar1[1] = 0;
    puVar1[3] = 0;
    *(undefined1 *)(puVar1 + 2) = 0;
  }
  if (s_tmNatInfoListHead == (undefined4 *)0x0) {
    s_tmNatInfoListHead = (undefined4 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (s_tmNatInfoListHead == (undefined4 *)0x0) goto LAB_00059038;
    __memzero(s_tmNatInfoListHead,0x14);
    puVar1 = s_tmNatInfoListHead;
    s_tmNatInfoListTail = s_tmNatInfoListHead;
    *s_tmNatInfoListHead = 0;
    puVar1[4] = 0;
    puVar1[1] = 0;
    puVar1[3] = 0;
    *(undefined1 *)(puVar1 + 2) = 0;
  }
  if (s_tmVlanInfoListHead == (undefined4 *)0x0) {
    s_tmVlanInfoListHead = (undefined4 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (s_tmVlanInfoListHead == (undefined4 *)0x0) goto LAB_00059038;
    __memzero(s_tmVlanInfoListHead,0x14);
    puVar1 = s_tmVlanInfoListHead;
    s_tmVlanInfoListTail = s_tmVlanInfoListHead;
    *s_tmVlanInfoListHead = 0;
    puVar1[4] = 0;
    puVar1[1] = 0;
    puVar1[3] = 0;
    *(undefined1 *)(puVar1 + 2) = 0;
  }
  puVar1 = s_tmCmdInfoListHead;
  if (s_tmCmdInfoListHead == (undefined4 *)0x0) {
    s_tmCmdInfoListHead = (undefined4 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (s_tmCmdInfoListHead == (undefined4 *)0x0) goto LAB_00059038;
    __memzero(s_tmCmdInfoListHead,0x1c);
    iVar2 = kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (iVar2 == 0) goto LAB_00059038;
    __memzero(iVar2,0xc);
    *(undefined2 *)(iVar2 + 8) = 0;
    *(undefined4 *)(iVar2 + 4) = 1;
    g_direction = puVar1;
    writeCmdInfoToRam_constprop_8(iVar2,1,0);
    puVar1 = s_tmCmdInfoListHead;
    s_tmCmdInfoListTail = s_tmCmdInfoListHead;
    s_tmCmdInfoListHead[3] = 1;
    *puVar1 = 0;
    puVar1[6] = iVar2;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[4] = 0;
    *(undefined1 *)(puVar1 + 5) = 1;
  }
  puVar1 = s_tmQosInfoListHead;
  if (s_tmQosInfoListHead == (undefined4 *)0x0) {
    s_tmQosInfoListHead = (undefined4 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (s_tmQosInfoListHead == (undefined4 *)0x0) {
      printk("ERROR:qosListInit Fail!!\n");
      return 0xfffffff4;
    }
    __memzero(s_tmQosInfoListHead,0x14);
    puVar3 = (undefined1 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (puVar3 == (undefined1 *)0x0) {
      printk("ERROR:lp_qosInfo malloc Fail!!\n");
      return 0xfffffff4;
    }
    __memzero(puVar3,5);
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    g_direction = puVar1;
    writeQosInfoToRam_constprop_7(puVar3,0);
    s_tmQosInfoListTail = s_tmQosInfoListHead;
    *s_tmQosInfoListHead = 0;
    s_tmQosInfoListTail[4] = puVar3;
    s_tmQosInfoListTail[1] = 0;
    s_tmQosInfoListTail[3] = 0;
    *(undefined1 *)(s_tmQosInfoListTail + 2) = 1;
  }
  if (s_tmFlowInfoListHead_d == (undefined4 *)0x0) {
    s_tmFlowInfoListHead_d = (undefined4 *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (s_tmFlowInfoListHead_d == (undefined4 *)0x0) {
LAB_00059038:
      printk("ERROR:operListInit Fail!!\n");
      return 0xfffffff4;
    }
    __memzero(s_tmFlowInfoListHead_d,0x14);
    puVar1 = s_tmFlowInfoListHead_d;
    s_tmFlowInfoListTail_d = s_tmFlowInfoListHead_d;
    *s_tmFlowInfoListHead_d = 0;
    puVar1[4] = 0;
    puVar1[1] = 0;
    puVar1[3] = 0;
    *(undefined1 *)(puVar1 + 2) = 0;
  }
  tmInfoListInited = 1;
  return 0;
}

