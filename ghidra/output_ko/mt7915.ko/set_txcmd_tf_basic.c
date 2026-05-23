// module: mt7915.ko
// function: set_txcmd_tf_basic @ 0x998ec
// size: 252 bytes
//

undefined4 set_txcmd_tf_basic(undefined4 param_1,char *param_2)

{
  uint *puVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *local_1c [2];
  uint *local_14 [2];
  
  local_1c[0] = param_2;
  iVar3 = os_alloc_mem(param_1,local_14,0x34);
  uVar5 = 1;
  if (iVar3 != 1) {
    os_zero_mem(local_14[0],0x34);
    puVar1 = local_14[0];
    *(byte *)local_14[0] = (byte)*local_14[0] & 0xc0 | 10;
    *local_14[0] = *local_14[0] & 0xffc0003f | 0xc00;
    pcVar4 = strsep(local_1c,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      bVar2 = os_str_tol(pcVar4,0,0x10);
      *(byte *)((int)puVar1 + 0x2e) = *(byte *)((int)puVar1 + 0x2e) | 0xc;
      *(byte *)((int)puVar1 + 0x16) = *(byte *)((int)puVar1 + 0x16) & 0xf3 | (bVar2 & 3) << 2;
    }
    uVar5 = send_cmd_msg(param_1,local_14[0],0);
    os_free_mem(local_14[0]);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_tf_basic",uVar5);
  }
  return uVar5;
}

