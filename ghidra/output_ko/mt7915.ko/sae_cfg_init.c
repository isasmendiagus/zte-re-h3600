// module: mt7915.ko
// function: sae_cfg_init @ 0x20895c
// size: 156 bytes
//

void sae_cfg_init(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_cfg_init");
  }
  *(undefined4 *)(param_2 + 0x1b904) = 0;
  *(undefined1 *)(param_2 + 0x1b91c) = 0x28;
  *(undefined4 *)(param_2 + 0x1b908) = 0;
  *(undefined4 *)(param_2 + 0x1b90c) = 0;
  *(undefined4 *)(param_2 + 0x1b924) = param_1;
  *(undefined4 *)(param_2 + 0x1b918) = 10;
  *(undefined4 *)(param_2 + 0x1b920) = 2;
  __memzero(param_2 + 0x1b910,6);
  __memzero(param_2 + 0x1b900,2);
  uVar1 = sae_support_group_list._1_1_;
  *(undefined1 *)(param_2 + 0x1b900) = (undefined1)sae_support_group_list;
  *(undefined1 *)(param_2 + 0x1b901) = uVar1;
  return;
}

