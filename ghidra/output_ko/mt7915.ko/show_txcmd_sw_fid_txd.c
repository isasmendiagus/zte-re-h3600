// module: mt7915.ko
// function: show_txcmd_sw_fid_txd @ 0x9aa00
// size: 284 bytes
//

undefined4 show_txcmd_sw_fid_txd(undefined4 param_1,char *param_2)

{
  ushort uVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  char *local_1c;
  undefined4 local_18;
  uint *local_14 [2];
  
  local_18 = CONCAT31(local_18._1_3_,0x17);
  local_18 = local_18 & 0xffc0003f;
  local_1c = param_2;
  pcVar2 = strsep(&local_1c,"-");
  if ((pcVar2 == (char *)0x0) || (*pcVar2 == '\0')) {
    local_18 = local_18 & 0xe03fffff;
  }
  else {
    uVar1 = os_str_tol(pcVar2,0,10);
    local_18 = CONCAT22(local_18._2_2_ & 0xe03f | (uVar1 & 0x7f) << 6,(undefined2)local_18);
  }
  set_txcmd_entry_idx(&local_18,local_1c);
  iVar3 = os_alloc_mem(param_1,local_14,0x404);
  uVar4 = 1;
  if (iVar3 != 1) {
    os_zero_mem(local_14[0],0x404);
    *(byte *)local_14[0] = (byte)*local_14[0] & 0xc0 | 0x17;
    *local_14[0] = *local_14[0] & 0xffc0003f | 0x10000;
    uVar4 = send_cmd_msg(param_1,&local_18,local_14[0]);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","show_txcmd_sw_fid_txd",uVar4);
  }
  return uVar4;
}

