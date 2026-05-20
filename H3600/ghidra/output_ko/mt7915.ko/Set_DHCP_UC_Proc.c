// module: mt7915.ko
// function: Set_DHCP_UC_Proc @ 0x3416c
// size: 104 bytes
//

undefined4 Set_DHCP_UC_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0xa7c554) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0xa7c554) = 1;
  }
  if (0 < DebugLevel) {
    printk("@@@ pAd->DhcpUcEnable=%u\n",*(undefined1 *)(param_1 + 0xa7c554));
  }
  return 1;
}

