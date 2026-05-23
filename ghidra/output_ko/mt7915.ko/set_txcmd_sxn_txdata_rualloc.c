// module: mt7915.ko
// function: set_txcmd_sxn_txdata_rualloc @ 0x98b88
// size: 412 bytes
//

undefined4 set_txcmd_sxn_txdata_rualloc(undefined4 param_1,char *param_2)

{
  ushort uVar1;
  uint *puVar2;
  byte bVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  undefined4 uVar7;
  char *local_24 [2];
  uint *local_1c [2];
  
  local_24[0] = param_2;
  iVar4 = os_alloc_mem(param_1,local_1c,0x44);
  if (iVar4 == 1) {
    uVar7 = 1;
  }
  else {
    os_zero_mem(local_1c[0],0x44);
    puVar2 = local_1c[0];
    *(byte *)local_1c[0] = (byte)*local_1c[0] & 0xc0 | 5;
    *local_1c[0] = *local_1c[0] & 0xffc0003f | 0x1000;
    pcVar5 = strsep(local_24,"-");
    if ((pcVar5 == (char *)0x0) || (*pcVar5 == '\0')) {
      uVar6 = ((uint)*(ushort *)((int)puVar2 + 2) << 0x13) >> 0x19;
    }
    else {
      uVar6 = os_str_tol(pcVar5,0,0x10);
      uVar6 = uVar6 & 0x7f;
      *(ushort *)((int)puVar2 + 2) = *(ushort *)((int)puVar2 + 2) & 0xe03f | (ushort)(uVar6 << 6);
    }
    if (uVar6 < 8) {
      pcVar5 = strsep(local_24,"-");
      if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
        uVar1 = *(ushort *)((int)puVar2 + 2);
        bVar3 = os_str_tol(pcVar5,0,0x10);
        *(byte *)((int)puVar2 + (((uint)uVar1 << 0x13) >> 0x19) + 0xc) = bVar3;
        *(byte *)((int)puVar2 + (((uint)*(ushort *)((int)puVar2 + 2) << 0x13) >> 0x19) + 0x2c) =
             0xff;
      }
      uVar7 = send_cmd_msg(param_1,local_1c[0],0);
    }
    else if (DebugLevel < 0) {
      uVar7 = 1;
    }
    else {
      printk("%s: index exceed than %d\n","set_txcmd_sxn_txdata_rualloc",7);
      uVar7 = 1;
    }
    os_free_mem(local_1c[0]);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_txdata_rualloc",uVar7);
  }
  return uVar7;
}

