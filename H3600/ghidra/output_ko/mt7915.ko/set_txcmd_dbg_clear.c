// module: mt7915.ko
// function: set_txcmd_dbg_clear @ 0x97f9c
// size: 208 bytes
//

undefined4 set_txcmd_dbg_clear(undefined4 param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *local_1c [2];
  uint *local_14 [2];
  
  local_1c[0] = param_2;
  iVar1 = os_alloc_mem(param_1,local_14,4);
  uVar3 = 1;
  if (iVar1 != 1) {
    os_zero_mem(local_14[0],4);
    uVar3 = 1;
    *(byte *)local_14[0] = (byte)*local_14[0] & 0xc0 | 1;
    *local_14[0] = *local_14[0] & 0xffc0003f;
    pcVar2 = strsep(local_1c,"-");
    if ((pcVar2 != (char *)0x0) && (*pcVar2 == '1')) {
      uVar3 = send_cmd_msg(param_1,local_14[0],0);
    }
    os_free_mem(local_14[0]);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_dbg_clear",uVar3);
  }
  return uVar3;
}

