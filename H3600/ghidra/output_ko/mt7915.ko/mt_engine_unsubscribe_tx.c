// module: mt7915.ko
// function: mt_engine_unsubscribe_tx @ 0x2552b4
// size: 320 bytes
//

undefined4
mt_engine_unsubscribe_tx(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = (uint)*(byte *)(param_2 + 0x215);
  while( true ) {
    iVar1 = param_2 + uVar2 * 4;
    if (uVar2 == 0) break;
    if (uVar2 - 1 < 0x10) {
      *(undefined4 *)(iVar1 + 0x2b8) = 0;
      iVar1 = net_ad_free_pkt(param_1,*(undefined4 *)(iVar1 + 0x2f8));
      if (iVar1 == 0) {
        iVar1 = *(byte *)(param_2 + 0x215) - 1;
        iVar4 = param_2 + (uint)*(byte *)(param_2 + 0x215) * 4;
        *(undefined4 *)(iVar4 + 0x2f8) = 0;
        net_ad_free_wtbl(param_1,param_2 + 0x214 + iVar1 * 6 + 6,*(undefined4 *)(iVar4 + 0x278),
                         param_2 + 0x214 + iVar1 * 0x20 + 0x128);
      }
      else {
        printk("%s: Free Packet fail(0x%04x)\n","mt_engine_stack_pop",iVar1);
        iVar4 = *(byte *)(param_2 + 0x215) - 1;
        net_ad_free_wtbl(param_1,iVar4 * 6 + param_2 + 0x214 + 6,
                         *(undefined4 *)(param_2 + (uint)*(byte *)(param_2 + 0x215) * 4 + 0x278),
                         param_2 + 0x214 + iVar4 * 0x20 + 0x128);
        printk("%s: Free wtbl fail(0x%04x)\n","mt_engine_stack_pop",iVar1);
      }
      sys_ad_zero_mem(param_2 + 0x214 + (uint)*(byte *)(param_2 + 0x215) * 0x20 + 0x108,0x20);
      sys_ad_zero_mem(param_2 + 0x214 + (uint)*(byte *)(param_2 + 0x215) * 6,6);
      uVar3 = *(byte *)(param_2 + 0x215) - 1;
      uVar2 = uVar3 & 0xff;
      *(undefined4 *)(param_2 + (*(byte *)(param_2 + 0x215) + 0x19) * 4 + 0x214) = 0;
      *(char *)(param_2 + 0x215) = (char)uVar3;
    }
    else {
      printk("(%s)Stack for Tx is empty, dismissed\n","mt_engine_stack_pop",iVar1,uVar2,param_4);
      uVar2 = (uint)*(byte *)(param_2 + 0x215);
    }
  }
  return 0;
}

