// module: mt7915.ko
// function: set_txcmd_sxn_protect_ruinfo @ 0x98834
// size: 396 bytes
//

undefined4 set_txcmd_sxn_protect_ruinfo(undefined4 param_1,char *param_2)

{
  uint *puVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  undefined4 uVar6;
  char *local_1c [2];
  uint *local_14;
  
  local_1c[0] = param_2;
  iVar3 = os_alloc_mem(param_1,&local_14,8);
  if (iVar3 == 1) {
    uVar6 = 1;
  }
  else {
    os_zero_mem(local_14,8);
    puVar1 = local_14;
    *(byte *)local_14 = (byte)*local_14 & 0xc0 | 4;
    *local_14 = *local_14 & 0xffc0003f | 0x100;
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 == (char *)0x0) || (*pcVar4 == '\0')) {
      uVar5 = ((uint)*(ushort *)((int)puVar1 + 2) << 0x13) >> 0x19;
    }
    else {
      uVar5 = os_str_tol(pcVar4,0,0x10);
      uVar5 = uVar5 & 0x7f;
      *(ushort *)((int)puVar1 + 2) = *(ushort *)((int)puVar1 + 2) & 0xe03f | (ushort)(uVar5 << 6);
    }
    if (uVar5 < 0x10) {
      pcVar4 = strsep(local_1c,"-");
      if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
        cVar2 = os_str_tol(pcVar4,0,0x10);
        *(byte *)((int)puVar1 + 7) = *(byte *)((int)puVar1 + 7) | 0xf0;
        *(byte *)((int)puVar1 + 5) = *(byte *)((int)puVar1 + 5) & 0xf | cVar2 << 4;
      }
      uVar6 = send_cmd_msg(param_1,local_14,0);
    }
    else if (DebugLevel < 0) {
      uVar6 = 1;
    }
    else {
      printk("%s: index exceed than %d\n","set_txcmd_sxn_protect_ruinfo",0x10);
      uVar6 = 1;
    }
    os_free_mem(local_14);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_protect_ruinfo",uVar6);
  }
  return uVar6;
}

