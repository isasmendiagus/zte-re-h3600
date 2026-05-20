// module: mt7915.ko
// function: mt_engine_search_stack @ 0x255224
// size: 140 bytes
//

undefined4
mt_engine_search_stack(int param_1,undefined2 param_2,undefined1 *param_3,undefined4 *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = (uint)*(byte *)(param_1 + 0x215);
  if (uVar4 == 0) {
    printk("(%s)Stack for Tx is empty, dismissed!\n","mt_engine_search_stack",param_3,param_4,
           param_4);
    return 0x300;
  }
  uVar2 = 0;
  do {
    iVar3 = param_1 + (uVar2 + 0x1a) * 4;
    iVar1 = *(int *)(iVar3 + 0x214);
    if (iVar1 != 0) {
      iVar1 = net_ad_match_wtbl(iVar1,param_2);
      if (iVar1 == 0) {
        *param_3 = (char)uVar2;
        *param_4 = *(undefined4 *)(iVar3 + 0x214);
        return 0;
      }
      uVar4 = (uint)*(byte *)(param_1 + 0x215);
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < uVar4);
  return 0x300;
}

