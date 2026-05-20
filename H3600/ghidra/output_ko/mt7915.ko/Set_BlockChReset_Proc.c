// module: mt7915.ko
// function: Set_BlockChReset_Proc @ 0x1014ac
// size: 136 bytes
//

undefined4 Set_BlockChReset_Proc(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (2 < DebugLevel) {
    printk("%s: Reset channel block status.\n","Set_BlockChReset_Proc");
  }
  iVar3 = 0;
  while( true ) {
    iVar1 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar3);
    if (*(byte *)(iVar1 + 0x49c) != 0) {
      iVar2 = iVar1 + (uint)*(byte *)(iVar1 + 0x49c) * 0x14;
      do {
        *(undefined2 *)(iVar1 + 0xc) = 0;
        iVar1 = iVar1 + 0x14;
      } while (iVar1 != iVar2);
    }
    if (iVar3 == 1) break;
    iVar3 = 1;
  }
  return 1;
}

