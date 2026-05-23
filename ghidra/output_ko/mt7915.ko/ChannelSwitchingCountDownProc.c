// module: mt7915.ko
// function: ChannelSwitchingCountDownProc @ 0x101048
// size: 304 bytes
//

void ChannelSwitchingCountDownProc(undefined4 param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  byte local_19 [5];
  
  local_19[0] = 0xff;
  if (param_2 != 0) {
    if ((*(uint *)(param_2 + 0xb18) & 0x200000) == 0) {
      if (0 < DebugLevel) {
        printk("%s() wdev %d not ready !!!\n","ChannelSwitchingCountDownProc",
               *(undefined1 *)(param_2 + 0xc));
      }
    }
    else {
      pbVar4 = *(byte **)(param_2 + 0x3fe4);
      if (pbVar4 != (byte *)0x0) {
        if (2 < DebugLevel) {
          printk("%s(): Wdev(%d) Channel Switching...(%d/%d)\n","ChannelSwitchingCountDownProc",
                 *(undefined1 *)(param_2 + 0xc),*pbVar4,pbVar4[1]);
        }
        bVar1 = *pbVar4;
        *pbVar4 = bVar1 + 1;
        iVar2 = DebugLevel;
        if (pbVar4[1] <= (byte)(bVar1 + 1)) {
          if (*(int *)(param_2 + 0x14) == 1) {
            local_19[0] = *(byte *)(param_2 + 0xe);
          }
          uVar3 = *(uint *)(pbVar4 + 0x1c) & ~(1 << (uint)local_19[0]);
          *(uint *)(pbVar4 + 0x1c) = uVar3;
          if (2 < iVar2) {
            printk("  Type = %d, func_idx = %d, csa_ap_bitmap = 0x%x\n",
                   *(undefined4 *)(param_2 + 0x14),*(undefined1 *)(param_2 + 0xe));
            uVar3 = *(uint *)(pbVar4 + 0x1c);
          }
          if (uVar3 == 0) {
            RTEnqueueInternalCmd(param_1,0x17,local_19,1);
          }
        }
      }
    }
  }
  return;
}

