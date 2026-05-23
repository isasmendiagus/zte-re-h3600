// module: mt7915.ko
// function: HQA_StaRecCmmUpdate @ 0x272d60
// size: 616 bytes
//

undefined4 HQA_StaRecCmmUpdate(int param_1,undefined4 param_2,int param_3)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  char *local_40;
  uint local_3a;
  uint local_36;
  uint local_32;
  uint local_2e;
  undefined2 local_2a;
  
  os_alloc_mem(param_1,&local_40,0x200);
  pcVar1 = local_40;
  if (local_40 == (char *)0x0) {
    FUN_0026cdd0(param_3,param_2,2,3);
    return 3;
  }
  uVar4 = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
  if (0x12 < uVar4) {
    os_free_mem(local_40);
    FUN_0026cdd0(param_3,param_2,2,2);
    return 2;
  }
  memcpy(&local_3a,(void *)(param_3 + 0xc),uVar4);
  iVar3 = uVar4 - 6;
  if (iVar3 < 0) {
    iVar3 = uVar4 - 3;
  }
  iVar3 = iVar3 >> 2;
  if (((0 < iVar3) &&
      (local_3a = local_3a << 0x18 | (local_3a >> 8 & 0xff) << 0x10 | (local_3a >> 0x10 & 0xff) << 8
                  | local_3a >> 0x18, iVar3 != 1)) &&
     (local_36 = local_36 << 0x18 | (local_36 >> 8 & 0xff) << 0x10 | (local_36 >> 0x10 & 0xff) << 8
                 | local_36 >> 0x18, iVar3 == 3)) {
    local_32 = local_32 << 0x18 | (local_32 >> 8 & 0xff) << 0x10 | (local_32 >> 0x10 & 0xff) << 8 |
               local_32 >> 0x18;
  }
  uVar2 = local_36;
  uVar4 = local_3a;
  if (local_3a < 5) {
    iVar3 = (local_3a - 1) * 10;
    iVar6 = param_1 + iVar3;
    iVar3 = param_1 + iVar3;
    *(short *)(iVar6 + 0xa3b00a) = (short)local_3a;
    *(char *)(iVar6 + 0xa3b00c) = (char)local_36;
    *(uint *)(iVar3 + 0xa3b00e) = local_2e;
    *(undefined2 *)(iVar3 + 0xa3b012) = local_2a;
    __memzero(pcVar1,0x200);
    sprintf(local_40,"%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",uVar4,uVar2,local_32,
            local_2e & 0xff,local_2e >> 8 & 0xff,local_2e >> 0x10 & 0xff,local_2e >> 0x18,
            (uint)(byte)local_2a,(uint)local_2a._1_1_);
    Set_StaRecCmmUpdate(param_1,local_40);
    if (local_40 == (char *)0x0) {
      FUN_0026cdd0(param_3,param_2,2,0);
      uVar5 = 0;
      goto LAB_00272e74;
    }
    uVar5 = 0;
  }
  else {
    uVar5 = 2;
    local_40 = pcVar1;
  }
  os_free_mem(local_40);
  FUN_0026cdd0(param_3,param_2,2,uVar5);
LAB_00272e74:
  if (0 < DebugLevel) {
    printk("%s: wlan_idx:%x, bss_idx:%x, aid:%x, mac:%02x:%02x:%02x:%02x:%02x:%02x\n",
           "HQA_StaRecCmmUpdate",local_3a,local_36,local_32,local_2e & 0xff,local_2e >> 8 & 0xff,
           local_2e >> 0x10 & 0xff,local_2e >> 0x18,(byte)local_2a,local_2a._1_1_);
  }
  return uVar5;
}

