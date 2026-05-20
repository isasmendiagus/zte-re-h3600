// module: mt7915.ko
// function: set_txcmd_sxn_protect @ 0x98620
// size: 528 bytes
//

undefined4 set_txcmd_sxn_protect(undefined4 param_1,char *param_2)

{
  uint *puVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  uint uVar6;
  char *local_1c [2];
  uint *local_14;
  
  local_1c[0] = param_2;
  iVar3 = os_alloc_mem(param_1,&local_14,0x14);
  uVar5 = 1;
  if (iVar3 != 1) {
    os_zero_mem(local_14,0x14);
    puVar1 = local_14;
    *(byte *)local_14 = (byte)*local_14 & 0xc0 | 3;
    *local_14 = *local_14 & 0xffc0003f | 0x400;
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0xe) = *(byte *)((int)puVar1 + 0xe) | 0xc;
      *(byte *)((int)puVar1 + 6) = *(byte *)((int)puVar1 + 6) & 0xf3 | (bVar2 & 3) << 2;
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)(puVar1 + 4) = (byte)puVar1[4] | 0x3f;
      *(byte *)(puVar1 + 2) = (byte)puVar1[2] & 0xc0 | bVar2 & 0x3f;
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      uVar6 = os_str_tol(pcVar4,0,0x10);
      *(byte *)(puVar1 + 4) = ~((byte)~(byte)(((uint)(byte)puVar1[4] << 0x1a) >> 0x18) >> 2);
      *(byte *)((int)puVar1 + 0x11) = *(byte *)((int)puVar1 + 0x11) | 3;
      *(byte *)((int)puVar1 + 9) =
           *(byte *)((int)puVar1 + 9) & 0xfc | (byte)((uVar6 << 0x1c) >> 0x1e);
      *(byte *)(puVar1 + 2) = (byte)puVar1[2] & 0x3f | (byte)((uVar6 & 3) << 6);
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x11) = *(byte *)((int)puVar1 + 0x11) | 0x1c;
      *(byte *)((int)puVar1 + 9) = *(byte *)((int)puVar1 + 9) & 0xe3 | (bVar2 & 7) << 2;
    }
    uVar5 = send_cmd_msg(param_1,local_14,0);
    os_free_mem(local_14);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_protect",uVar5);
  }
  return uVar5;
}

