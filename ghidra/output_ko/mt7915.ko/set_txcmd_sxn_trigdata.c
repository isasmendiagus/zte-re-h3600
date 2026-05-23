// module: mt7915.ko
// function: set_txcmd_sxn_trigdata @ 0x991cc
// size: 468 bytes
//

undefined4 set_txcmd_sxn_trigdata(undefined4 param_1,char *param_2)

{
  uint *puVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  uint uVar6;
  char *local_1c [2];
  uint *local_14 [2];
  
  local_1c[0] = param_2;
  iVar3 = os_alloc_mem(param_1,local_14,0x54);
  uVar5 = 1;
  if (iVar3 != 1) {
    os_zero_mem(local_14[0],0x54);
    puVar1 = local_14[0];
    *(byte *)local_14[0] = (byte)*local_14[0] & 0xc0 | 7;
    *local_14[0] = *local_14[0] & 0xffc0003f | 0x1400;
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x2f) = *(byte *)((int)puVar1 + 0x2f) | 3;
      *(byte *)((int)puVar1 + 7) = *(byte *)((int)puVar1 + 7) & 0xfc | bVar2 & 3;
    }
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      uVar6 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x32) =
           ~((byte)~(byte)(((uint)*(byte *)((int)puVar1 + 0x32) << 0x1d) >> 0x18) >> 5);
      *(byte *)((int)puVar1 + 0x33) = *(byte *)((int)puVar1 + 0x33) | 0x7f;
      *(byte *)((int)puVar1 + 0xb) =
           *(byte *)((int)puVar1 + 0xb) & 0x80 | (byte)((uVar6 << 0x14) >> 0x19);
      *(byte *)((int)puVar1 + 10) = *(byte *)((int)puVar1 + 10) & 7 | (byte)((uVar6 & 0x1f) << 3);
    }
    strsep(local_1c,"-");
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x4f) = *(byte *)((int)puVar1 + 0x4f) | 0xf;
      *(byte *)((int)puVar1 + 0x27) = *(byte *)((int)puVar1 + 0x27) & 0xf0 | bVar2 & 0xf;
    }
    uVar5 = send_cmd_msg(param_1,local_14[0],0);
    os_free_mem(local_14[0]);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_trigdata",uVar5);
  }
  return uVar5;
}

