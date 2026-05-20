// module: mt7915.ko
// function: MATProto_ARP_Tx @ 0x7ab10
// size: 320 bytes
//

uint MATProto_ARP_Tx(undefined4 param_1,int param_2,short *param_3,void *param_4)

{
  uint uVar1;
  int iVar2;
  short *__dest;
  
  if (((*param_3 == 0x100) && (param_3[1] == 8)) && ((param_3[3] - 0x100U & 0xfeff) == 0)) {
    if (((*(byte *)(param_3 + 4) & 1) == 0) &&
       (((((*(byte *)(param_3 + 4) != 0 || *(char *)((int)param_3 + 9) != '\0') ||
          (char)param_3[5] != '\0') || *(char *)((int)param_3 + 0xb) != '\0') ||
        (char)param_3[6] != '\0') || *(char *)((int)param_3 + 0xd) != '\0')) {
      __dest = param_3 + 4;
      if (*(int *)(param_3 + 7) != 0) {
        FUN_0007a38c(param_1,__dest,*(int *)(param_3 + 7),param_4,param_4);
      }
      uVar1 = *(byte *)(param_2 + 0x72) & 1;
      if ((*(byte *)(param_2 + 0x72) & 1) != 0) {
        if ((*(uint *)(*(int *)(param_2 + 0xc4) + 0x20) & 0xffff) == 1) {
          uVar1 = 0;
        }
        else {
          uVar1 = skb_copy(param_2,0x20);
          g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
          if (uVar1 != 0) {
            iVar2 = *(int *)(uVar1 + 0xcc);
            if (CONCAT11(*(undefined1 *)(iVar2 + 0xc),*(undefined1 *)(iVar2 + 0xd)) == -0x7f00) {
              __dest = (short *)(iVar2 + 0x1a);
            }
            else {
              __dest = (short *)(iVar2 + 0x16);
            }
          }
        }
      }
      if (param_4 == (void *)0x0) {
        printk(&_LC9,0x1c6);
        dump_stack();
      }
      memmove(__dest,param_4,6);
      return uVar1;
    }
    return 0;
  }
  return 0;
}

