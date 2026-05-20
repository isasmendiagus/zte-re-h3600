// module: mt7915.ko
// function: show_txcmd_dbg_status @ 0x9a3a8
// size: 184 bytes
//

undefined4 show_txcmd_dbg_status(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_18;
  uint *local_14;
  
  local_18 = CONCAT31(local_18._1_3_,0xf);
  local_18 = local_18 & 0xffc0003f;
  iVar1 = os_alloc_mem(param_1,&local_14,0x2c);
  uVar2 = 1;
  if (iVar1 != 1) {
    os_zero_mem(local_14,0x2c);
    *(byte *)local_14 = (byte)*local_14 & 0xc0 | 0xf;
    *local_14 = *local_14 & 0xffc0003f | 0xa00;
    uVar2 = send_cmd_msg(param_1,&local_18,local_14);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","show_txcmd_dbg_status",uVar2);
  }
  return uVar2;
}

