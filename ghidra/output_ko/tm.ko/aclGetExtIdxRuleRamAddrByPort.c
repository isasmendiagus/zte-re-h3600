// module: tm.ko
// function: aclGetExtIdxRuleRamAddrByPort @ 0x58970
// size: 196 bytes
//

undefined4 aclGetExtIdxRuleRamAddrByPort(uint param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == (uint *)0x0) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x443);
    printk("getExtIdxRuleTblAddrByPort params is NULL\n");
    return 0xfffffff4;
  }
  if (param_1 < 0x20) {
    if (g_ipv4FastEn != '\0') {
      *param_2 = 9;
      return 0;
    }
    if (g_ipv6FastEn != '\0') {
      *param_2 = 10;
      return 0;
    }
    iVar3 = 0;
    do {
      iVar2 = iVar3 * 2;
      iVar1 = iVar3 * 2;
      iVar3 = iVar3 + 1;
      if ((byte)(&s_aclPortExtIdxTblMap)[iVar2] == param_1) {
        *param_2 = (uint)(byte)(&DAT_0007acfd)[iVar1];
        return 0;
      }
    } while (iVar3 != 0x18);
  }
  return 0xfffffff4;
}

