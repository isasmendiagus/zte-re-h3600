// module: mt7915.ko
// function: set_txcmd_tf_basic_user @ 0x999ec
// size: 476 bytes
//

undefined4 set_txcmd_tf_basic_user(undefined4 param_1,char *param_2)

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
  iVar4 = os_alloc_mem(param_1,&local_14,0x10);
  if (iVar4 == 1) {
    uVar7 = 1;
  }
  else {
    os_zero_mem(local_14,0x10);
    puVar1 = local_14;
    *(byte *)local_14 = (byte)*local_14 & 0xc0 | 0xb;
    *local_14 = *local_14 & 0xffc0003f | 0x300;
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
        *(byte *)((int)puVar1 + 0xf) = *(byte *)((int)puVar1 + 0xf) | 0x1c;
        *(byte *)((int)puVar1 + 9) = *(byte *)((int)puVar1 + 9) & 0xe3 | (bVar2 & 7) << 2;
      }
      pcVar5 = strsep(local_1c,"-");
      if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
        cVar3 = os_str_tol(pcVar5,0,0x10);
        *(byte *)((int)puVar1 + 0xf) = *(byte *)((int)puVar1 + 0xf) | 0xc0;
        *(byte *)((int)puVar1 + 9) = *(byte *)((int)puVar1 + 9) & 0x3f | cVar3 << 6;
      }
      uVar7 = send_cmd_msg(param_1,local_14,0);
    }
    else if (DebugLevel < 0) {
      uVar7 = 1;
    }
    else {
      printk("%s: index exceed than %d\n","set_txcmd_tf_basic_user",0x10);
      uVar7 = 1;
    }
    os_free_mem(local_14);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_tf_basic_user",uVar7);
  }
  return uVar7;
}

