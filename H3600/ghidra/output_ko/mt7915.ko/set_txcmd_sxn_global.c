// module: mt7915.ko
// function: set_txcmd_sxn_global @ 0x98460
// size: 444 bytes
//

undefined4 set_txcmd_sxn_global(undefined4 param_1,char *param_2)

{
  uint *puVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *local_1c [2];
  uint *local_14;
  
  local_1c[0] = param_2;
  if (3 < DebugLevel) {
    printk("%s: arg = %s\n","set_txcmd_sxn_global",param_2);
  }
  iVar3 = os_alloc_mem(param_1,&local_14,0x24);
  uVar5 = 1;
  if (iVar3 != 1) {
    os_zero_mem(local_14,0x24);
    puVar1 = local_14;
    *(byte *)local_14 = (byte)*local_14 & 0xc0 | 2;
    *local_14 = *local_14 & 0xffc0003f | 0x800;
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x19) = *(byte *)((int)puVar1 + 0x19) | 2;
      *(byte *)((int)puVar1 + 9) = *(byte *)((int)puVar1 + 9) & 0xfd | (bVar2 & 1) << 1;
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x19) = *(byte *)((int)puVar1 + 0x19) | 0x40;
      *(byte *)((int)puVar1 + 9) = *(byte *)((int)puVar1 + 9) & 0xbf | (bVar2 & 1) << 6;
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x1b) = *(byte *)((int)puVar1 + 0x1b) | 2;
      *(byte *)((int)puVar1 + 0xb) = *(byte *)((int)puVar1 + 0xb) & 0xfd | (bVar2 & 1) << 1;
    }
    uVar5 = send_cmd_msg(param_1,local_14,0);
    os_free_mem(local_14);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","set_txcmd_sxn_global",uVar5);
  }
  return uVar5;
}

