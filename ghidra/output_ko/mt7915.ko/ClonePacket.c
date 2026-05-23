// module: mt7915.ko
// function: ClonePacket @ 0x243678
// size: 156 bytes
//

void ClonePacket(undefined4 param_1,undefined4 param_2,int param_3,int param_4,uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_3 == 0) {
    printk(&_LC4,0x1d2);
    dump_stack();
  }
  if (0x5f9 < param_5) {
    printk(&_LC5,0x1d7);
    dump_stack();
  }
  iVar1 = skb_clone(param_3,0x20);
  if (iVar1 == 0) {
    return;
  }
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  uVar2 = *(undefined4 *)(param_3 + 0x18);
  *(int *)(iVar1 + 0xcc) = param_4;
  *(uint *)(iVar1 + 0xc0) = param_4 + param_5;
  *(undefined4 *)(iVar1 + 0x18) = uVar2;
  *(uint *)(iVar1 + 100) = param_5;
  return;
}

