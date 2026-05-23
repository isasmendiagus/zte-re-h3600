// module: tm.ko
// function: sw_get_arp_icmp_stat @ 0x63adc
// size: 184 bytes
//

int sw_get_arp_icmp_stat(void)

{
  int iVar1;
  int local_14;
  
  local_14 = 0;
  adm_get_up_pass_protocal_packtcnt(0,&local_14);
  iVar1 = local_14;
  adm_get_up_drop_protocal_packtcnt(0,&local_14);
  iVar1 = iVar1 + local_14;
  adm_get_up_pass_protocal_packtcnt(5,&local_14);
  iVar1 = iVar1 + local_14;
  adm_get_up_drop_protocal_packtcnt(5,&local_14);
  iVar1 = iVar1 + local_14;
  adm_get_dn_pass_protocal_packtcnt(0,&local_14);
  iVar1 = iVar1 + local_14;
  adm_get_dn_drop_protocal_packtcnt(0,&local_14);
  iVar1 = iVar1 + local_14;
  adm_get_dn_pass_protocal_packtcnt(5,&local_14);
  iVar1 = iVar1 + local_14;
  adm_get_dn_drop_protocal_packtcnt(5,&local_14);
  return iVar1 + local_14;
}

