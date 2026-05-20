// module: mt7915.ko
// function: set_txcmd_sxn_trigdata_user_ackinfo @ 0x99544
// size: 676 bytes
//

undefined4 set_txcmd_sxn_trigdata_user_ackinfo(undefined4 param_1,char *param_2)

{
  uint *puVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  undefined4 uVar7;
  char *local_1c [2];
  uint *local_14;
  
  local_1c[0] = param_2;
  iVar4 = os_alloc_mem(param_1,&local_14,0x24);
  if (iVar4 == 1) {
    uVar7 = 1;
  }
  else {
    os_zero_mem(local_14,0x24);
    puVar1 = local_14;
    *(byte *)local_14 = (byte)*local_14 & 0xc0 | 8;
    *local_14 = *local_14 & 0xffc0003f | 0x800;
    pcVar5 = strsep(local_1c,"-");
    if ((pcVar5 == (char *)0x0) || (*pcVar5 == '\0')) {
      uVar6 = ((uint)*(ushort *)((int)puVar1 + 2) << 0x13) >> 0x19;
    }
    else {
      uVar6 = os_str_tol(pcVar5,0,0x10);
      uVar6 = uVar6 & 0x7f;
      *(ushort *)((int)puVar1 + 2) = *(ushort *)((int)puVar1 + 2) & 0xe03f | (ushort)(uVar6 << 6);
    }
    if (uVar6 < 0x10) {
      pcVar5 = strsep(local_1c,"-");
      if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
        bVar2 = os_str_tol(pcVar5,0,0x10);
        *(byte *)((int)puVar1 + 0x16) = *(byte *)((int)puVar1 + 0x16) | 0x20;
        *(byte *)((int)puVar1 + 6) = *(byte *)((int)puVar1 + 6) & 0xdf | (bVar2 & 1) << 5;
      }
      pcVar5 = strsep(local_1c,"-");
      if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
        cVar3 = os_str_tol(pcVar5,0,0x10);
        *(byte *)(puVar1 + 6) = (byte)puVar1[6] | 0xfe;
        *(byte *)(puVar1 + 2) = (byte)puVar1[2] & 1 | cVar3 << 1;
      }
      pcVar5 = strsep(local_1c,"-");
      if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
        bVar2 = os_str_tol(pcVar5,0,0x10);
        *(byte *)((int)puVar1 + 0x19) = *(byte *)((int)puVar1 + 0x19) | 0x3f;
        *(byte *)((int)puVar1 + 9) = *(byte *)((int)puVar1 + 9) & 0xc0 | bVar2 & 0x3f;
      }
      pcVar5 = strsep(local_1c,"-");
      if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
        uVar6 = os_str_tol(pcVar5,0,0x10);
        *(byte *)((int)puVar1 + 0x19) =
             ~((byte)~(byte)(((uint)*(byte *)((int)puVar1 + 0x19) << 0x1a) >> 0x18) >> 2);
        *(byte *)((int)puVar1 + 0x1a) = *(byte *)((int)puVar1 + 0x1a) | 1;
        *(byte *)((int)puVar1 + 10) =
             *(byte *)((int)puVar1 + 10) & 0xfe | (byte)((uVar6 << 0x1d) >> 0x1f);
        *(byte *)((int)puVar1 + 9) = *(byte *)((int)puVar1 + 9) & 0x3f | (byte)((uVar6 & 3) << 6);
      }
      uVar7 = send_cmd_msg(param_1,local_14,0);
    }
    else if (DebugLevel < 0) {
      uVar7 = 1;
    }
    else {
      printk("%s: index exceed than %d\n","set_txcmd_sxn_trigdata_user_ackinfo",0x10);
      uVar7 = 1;
    }
    os_free_mem(local_14);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_trigdata_user_ackinfo",uVar7);
  }
  return uVar7;
}

