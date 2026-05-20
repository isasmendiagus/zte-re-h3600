// module: mt7915.ko
// function: MemSectionRead @ 0x193324
// size: 72 bytes
//

void MemSectionRead(int param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == 0) {
    return;
  }
  iVar1 = param_2;
  do {
    iVar2 = iVar1 + 4;
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar1 + (param_4 - param_2),iVar1);
    iVar1 = iVar2;
  } while ((uint)(iVar2 - param_2) < param_3);
  return;
}

