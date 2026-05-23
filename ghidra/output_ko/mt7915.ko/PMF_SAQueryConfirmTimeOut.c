// module: mt7915.ko
// function: PMF_SAQueryConfirmTimeOut @ 0x219c68
// size: 132 bytes
//

void PMF_SAQueryConfirmTimeOut(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    return;
  }
  uVar1 = *(undefined4 *)(param_2 + 0xc);
  if (-1 < DebugLevel) {
    printk("[PMF]%s - STA(%02x:%02x:%02x:%02x:%02x:%02x)\n","PMF_SAQueryConfirmTimeOut",
           *(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
           *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
           *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
  }
  *(undefined1 *)(param_2 + 0x628) = 1;
  PMF_MlmeSAQueryReq(uVar1,param_2);
  return;
}

