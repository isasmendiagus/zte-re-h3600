// module: tm.ko
// function: tm_show_acl_list @ 0x5ed90
// size: 104 bytes
//

undefined4 tm_show_acl_list(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  
  puVar4 = sa_rulesRecord + param_1 * 0x100;
  iVar5 = 0;
  do {
    puVar1 = (undefined4 *)(puVar4 + 4);
    puVar2 = (undefined4 *)(puVar4 + 8);
    puVar3 = (undefined4 *)(puVar4 + 0xc);
    puVar4 = puVar4 + 0x10;
    iVar6 = iVar5 + 1;
    printk("## acl_rule[%d][%d]: parseMsk=0x%x, extRuleMsk=0x%x, hashMsk=0x%x, ruleCount=%d\n",
           param_1,iVar5,*(undefined4 *)(sa_rulesRecord + param_1 * 0x100 + iVar5 * 0x10),*puVar1,
           *puVar2,*puVar3);
    iVar5 = iVar6;
  } while (iVar6 != 0x10);
  return 0;
}

