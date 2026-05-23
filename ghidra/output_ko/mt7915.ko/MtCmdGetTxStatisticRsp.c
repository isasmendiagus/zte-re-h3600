// module: mt7915.ko
// function: MtCmdGetTxStatisticRsp @ 0x1abe60
// size: 256 bytes
//

void MtCmdGetTxStatisticRsp(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = *(uint *)(param_2 + 4);
  iVar3 = *(int *)(param_1 + 0xc);
  *(uint *)(iVar3 + 4) = uVar2;
  if ((uVar2 & 1) != 0) {
    *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(param_2 + 8);
    *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(param_2 + 0xc);
    *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(param_2 + 0x10);
    *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(param_2 + 0x18);
  }
  if ((uVar2 & 2) != 0) {
    os_move_mem((void *)(iVar3 + 0x28),(void *)(param_2 + 0x28),9);
    uVar2 = *(uint *)(iVar3 + 4);
  }
  if ((uVar2 & 4) != 0) {
    os_move_mem((void *)(iVar3 + 0x31),(void *)(param_2 + 0x31),9);
    iVar1 = DebugLevel;
    if ((*(byte *)(iVar3 + 0x31) - 2 < 2) && (*(byte *)(iVar3 + 0x38) != 0)) {
      uVar2 = (uint)*(byte *)(iVar3 + 0x37) + (*(byte *)(iVar3 + 0x38) - 1 & 3) * 8;
      *(char *)(iVar3 + 0x37) = (char)uVar2;
      if (1 < iVar1) {
        printk("%s:11n change mcs:%u\n","MtCmdGetTxStatisticRsp",uVar2 & 0xff,uVar2,param_4);
      }
    }
    uVar2 = *(uint *)(iVar3 + 4);
  }
  if ((uVar2 & 8) != 0) {
    *(undefined4 *)(iVar3 + 0x20) = *(undefined4 *)(param_2 + 0x20);
    *(undefined4 *)(iVar3 + 0x24) = *(undefined4 *)(param_2 + 0x24);
  }
  if ((uVar2 & 0x10) != 0) {
    *(undefined1 *)(iVar3 + 0x3a) = *(undefined1 *)(param_2 + 0x3a);
  }
  return;
}

