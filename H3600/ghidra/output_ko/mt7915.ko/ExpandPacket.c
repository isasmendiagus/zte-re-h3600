// module: mt7915.ko
// function: ExpandPacket @ 0x243964
// size: 316 bytes
//

int ExpandPacket(undefined4 param_1,int param_2,uint param_3,uint param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = param_4;
  if (((*(byte *)(param_2 + 0x72) & 1) == 0) ||
     ((*(uint *)(*(int *)(param_2 + 0xc4) + 0x20) & 0xffff) == 1)) {
    uVar3 = *(int *)(param_2 + 0xcc) - *(int *)(param_2 + 200);
    if (uVar3 < param_3) goto LAB_00243998;
    if (*(int *)(param_2 + 0x68) != 0) {
      if (param_4 == 0) {
        return param_2;
      }
      if (uVar3 < param_3) {
        uVar3 = param_3;
      }
      goto LAB_002439b0;
    }
    if (param_4 <= (uint)(*(int *)(param_2 + 0xc4) - *(int *)(param_2 + 0xc0))) {
      return param_2;
    }
    if (uVar3 < param_3) {
      uVar3 = param_3;
    }
  }
  else {
    uVar3 = *(int *)(param_2 + 0xcc) - *(int *)(param_2 + 200);
LAB_00243998:
    if (uVar3 < param_3) {
      uVar3 = param_3;
    }
    if ((*(int *)(param_2 + 0x68) == 0) &&
       (uVar4 = *(int *)(param_2 + 0xc4) - *(int *)(param_2 + 0xc0), param_4 <= uVar4))
    goto LAB_002439b0;
  }
  uVar4 = param_4;
LAB_002439b0:
  iVar2 = skb_copy_expand(param_2,uVar3,uVar4,0x20,param_4);
  __dev_kfree_skb_any(param_2,1);
  uVar1 = g_stWlanRadioStat._8_4_;
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
  if (iVar2 != 0) {
    g_stWlanRadioStat._8_4_ = uVar1;
    return iVar2;
  }
  if (-1 < DebugLevel) {
    printk("Extend Tx buffer for WPI failed!, dropping packet!\n");
    return 0;
  }
  return 0;
}

