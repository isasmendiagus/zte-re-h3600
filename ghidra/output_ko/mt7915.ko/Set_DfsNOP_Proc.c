// module: mt7915.ko
// function: Set_DfsNOP_Proc @ 0x2319b8
// size: 180 bytes
//

undefined4 Set_DfsNOP_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  uVar2 = simple_strtol(param_2,0,10,param_4,param_4);
  if (0 < DebugLevel) {
    printk("Set NOP of all channel as %ld.\n",uVar2);
  }
  iVar6 = 0;
  while( true ) {
    iVar3 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar6);
    cVar1 = *(char *)(iVar3 + 0x49c);
    if (cVar1 != '\0') {
      iVar4 = iVar3;
      do {
        *(short *)(iVar4 + 0xc) = (short)uVar2;
        iVar5 = iVar4 + 0x14;
        *(undefined1 *)(iVar4 + 7) = 0;
        *(undefined1 *)(iVar4 + 9) = 0;
        iVar4 = iVar5;
      } while (iVar5 != iVar3 + ((byte)(cVar1 - 1) + 1) * 0x14);
    }
    if (iVar6 == 1) break;
    iVar6 = 1;
  }
  return 1;
}

