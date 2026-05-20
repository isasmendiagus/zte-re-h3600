// module: tm.ko
// function: tm_get_dn_drop_protocal_packtcnt @ 0x4c4a0
// size: 36 bytes
//

undefined4 tm_get_dn_drop_protocal_packtcnt(void)

{
  int iVar1;
  
  iVar1 = adm_get_dn_drop_protocal_packtcnt();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[tmtst]adm_get_dn_drop_protocal_packtcnt error\n");
  return 0xffffffff;
}

