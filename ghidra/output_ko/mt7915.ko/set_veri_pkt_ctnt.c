// module: mt7915.ko
// function: set_veri_pkt_ctnt @ 0x1d5cdc
// size: 464 bytes
//

undefined4 set_veri_pkt_ctnt(undefined4 param_1,char *param_2)

{
  bool bVar1;
  uint uVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint local_84;
  int local_80;
  char acStack_7c [104];
  
  local_84 = 0;
  memset(acStack_7c,0,100);
  local_80 = 0;
  os_alloc_mem(0,&local_80,0x400);
  if (local_80 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: padded_ctnt Allocate memory fail!!!\n","set_veri_pkt_ctnt");
    return 0;
  }
  __memzero(local_80,0x400);
  if (param_2 == (char *)0x0) {
    uVar6 = 1;
    goto LAB_001d5dfc;
  }
  sscanf(param_2,"len:%u-ctnt:%100s",&local_84,acStack_7c);
  sVar3 = strlen(acStack_7c);
  uVar2 = sVar3 >> 1;
  uVar5 = local_84;
  if (local_84 < 0x401) {
    uVar5 = uVar2;
  }
  if (sVar3 != uVar2 * 2 || 0x400 < uVar5) {
    if (0 < DebugLevel) {
      printk("%s: ctnt format error: padding_to_length:%d, ctnt_length:%d, strlen(ctnt):%d\n",
             "ctnt_length_sanity_check",local_84,uVar2,sVar3);
    }
    FUN_001d54e4();
    os_free_mem(local_80);
    return 0;
  }
  if (uVar2 < local_84) {
LAB_001d5db4:
    iVar7 = 0;
    uVar5 = local_84;
    do {
      iVar4 = local_80 + iVar7;
      iVar7 = iVar7 + uVar2;
      AtoH(acStack_7c,iVar4,uVar2);
      bVar1 = uVar5 < uVar2;
      uVar5 = uVar5 - uVar2;
      if (bVar1) {
        uVar5 = uVar2;
      }
    } while (uVar5 != 0);
  }
  else {
    local_84 = uVar2;
    if (0 < DebugLevel) {
      printk("%s: honor ctnt_len\n","set_veri_pkt_ctnt");
    }
    if (local_84 != 0) goto LAB_001d5db4;
  }
  iVar7 = prepare_veri_pkt_ctnt(param_1,local_80,local_84);
  uVar6 = 0;
  if (iVar7 != 0) {
    uVar6 = 1;
  }
LAB_001d5dfc:
  os_free_mem(local_80);
  return uVar6;
}

