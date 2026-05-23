// module: mt7915.ko
// function: CmdWscApCliLinkDown @ 0xc4358
// size: 76 bytes
//

undefined4 CmdWscApCliLinkDown(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  
  uVar1 = **(undefined1 **)(param_2 + 4);
  if (2 < DebugLevel) {
    printk("cmd>  CMDTHREAD_WSC_APCLI_LINK_DOWN! apidx=%u\n",uVar1,*(undefined1 **)(param_2 + 4),
           DebugLevel,param_4);
  }
  WscApCliLinkDownById(param_1,uVar1);
  return 0;
}

