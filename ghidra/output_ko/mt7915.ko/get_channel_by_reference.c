// module: mt7915.ko
// function: get_channel_by_reference @ 0x100f7c
// size: 200 bytes
//

uint get_channel_by_reference(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  ushort uVar3;
  uint uVar4;
  ushort *puVar5;
  ushort *puVar6;
  
  uVar1 = HcGetBandByWdev(param_3);
  iVar2 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar1);
  if (param_2 == 1) {
    if (*(byte *)(iVar2 + 0x49c) == 0) {
      uVar4 = 0;
    }
    else {
      uVar3 = 0xffff;
      uVar4 = 0;
      puVar5 = (ushort *)(iVar2 + 0xc);
      do {
        puVar6 = puVar5 + 10;
        if (*puVar5 < uVar3) {
          uVar4 = (uint)(byte)puVar5[-6];
          uVar3 = *puVar5;
        }
        puVar5 = puVar6;
      } while (puVar6 != (ushort *)((uint)*(byte *)(iVar2 + 0x49c) * 0x14 + iVar2 + 0xc));
    }
  }
  else {
    uVar4 = FirstChannel(param_1,param_3);
  }
  if (2 < DebugLevel) {
    printk("%s(): mode = %u, ch = %u\n","get_channel_by_reference",param_2,uVar4,param_4);
  }
  return uVar4;
}

