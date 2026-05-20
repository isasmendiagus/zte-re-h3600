// module: mt7915.ko
// function: set_txcmd_sxn_txdata @ 0x989c4
// size: 448 bytes
//

undefined4 set_txcmd_sxn_txdata(undefined4 param_1,char *param_2)

{
  uint *puVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *local_1c [2];
  uint *local_14 [2];
  
  local_1c[0] = param_2;
  iVar3 = os_alloc_mem(param_1,local_14,0x44);
  uVar5 = 1;
  if (iVar3 != 1) {
    os_zero_mem(local_14[0],0x44);
    puVar1 = local_14[0];
    *(byte *)local_14[0] = (byte)*local_14[0] & 0xc0 | 5;
    *local_14[0] = *local_14[0] & 0xffc0003f | 0x1000;
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)(puVar1 + 10) = (byte)puVar1[10] | 0x40;
      *(byte *)(puVar1 + 2) = (byte)puVar1[2] & 0xbf | (bVar2 & 1) << 6;
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x36) =
           ~((byte)~(byte)(((uint)*(byte *)((int)puVar1 + 0x36) << 0x1c) >> 0x18) >> 4);
      *(byte *)((int)puVar1 + 0x37) = *(byte *)((int)puVar1 + 0x37) | 0xf;
      *(byte *)((int)puVar1 + 0x17) = *(byte *)((int)puVar1 + 0x17) & 0xf0 | bVar2 >> 4;
      *(byte *)((int)puVar1 + 0x16) = *(byte *)((int)puVar1 + 0x16) & 0xf | bVar2 << 4;
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x3b) = *(byte *)((int)puVar1 + 0x3b) | 0xf;
      *(byte *)((int)puVar1 + 0x1b) = *(byte *)((int)puVar1 + 0x1b) & 0xf0 | bVar2 & 0xf;
    }
    uVar5 = send_cmd_msg(param_1,local_14[0],0);
    os_free_mem(local_14[0]);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_txdata",uVar5);
  }
  return uVar5;
}

