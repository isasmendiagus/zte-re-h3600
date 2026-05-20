// module: mt7915.ko
// function: hqa_muru_set_mu_tx_pkt_cnt @ 0x23de48
// size: 188 bytes
//

undefined4 hqa_muru_set_mu_tx_pkt_cnt(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  char *local_14;
  undefined1 local_10 [4];
  undefined4 local_c;
  
  local_14 = param_2;
  os_zero_mem(local_10,8);
  pcVar1 = strsep(&local_14,":");
  if (pcVar1 != (char *)0x0) {
    local_10[0] = simple_strtol(pcVar1,0,10);
    pcVar1 = strsep(&local_14,"");
    if (pcVar1 != (char *)0x0) {
      local_c = simple_strtol(pcVar1,0,10);
      uVar2 = set_muru_mu_tx_pkt_cnt(param_1,local_10);
      goto LAB_0023decc;
    }
  }
  uVar2 = 0;
LAB_0023decc:
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","hqa_muru_set_mu_tx_pkt_cnt",uVar2);
  }
  return uVar2;
}

