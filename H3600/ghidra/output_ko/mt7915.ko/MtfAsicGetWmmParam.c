// module: mt7915.ko
// function: MtfAsicGetWmmParam @ 0x19555c
// size: 248 bytes
//

uint MtfAsicGetWmmParam(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint local_14 [2];
  
  if (param_2 < 4) {
    switch(param_3) {
    case 0:
      iVar1 = param_2 * 0xc;
      iVar2 = *(int *)(&DAT_0029d538 + iVar1);
      uVar3 = *(uint *)(&DAT_0029d53c + iVar1);
      uVar4 = *(uint *)(&DAT_0029d540 + iVar1);
      break;
    case 1:
      iVar1 = param_2 * 0xc;
      iVar2 = *(int *)(&DAT_0029d568 + iVar1);
      uVar3 = *(uint *)(&DAT_0029d56c + iVar1);
      uVar4 = *(uint *)(&DAT_0029d570 + iVar1);
      break;
    case 2:
      iVar1 = param_2 * 0xc;
      iVar2 = *(int *)(&DAT_0029d598 + iVar1);
      uVar3 = *(uint *)(&DAT_0029d59c + iVar1);
      uVar4 = *(uint *)(&DAT_0029d5a0 + iVar1);
      break;
    case 3:
      iVar1 = param_2 * 0xc;
      iVar2 = *(int *)(&DAT_0029d5c8 + iVar1);
      uVar3 = *(uint *)(&DAT_0029d5cc + iVar1);
      uVar4 = *(uint *)(&DAT_0029d5d0 + iVar1);
      break;
    default:
      if (DebugLevel < 1) {
        return 0xdeadbeef;
      }
      printk("%s(%d): Error type=%d\n","MtfAsicGetWmmParam",0x152,param_3);
      return 0xdeadbeef;
    }
    if (uVar3 != 0 && iVar2 != 0) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,local_14);
      return (local_14[0] & uVar3) >> (uVar4 & 0xff);
    }
  }
  return 0xdeadbeef;
}

