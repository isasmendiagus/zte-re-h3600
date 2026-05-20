// module: mt7915.ko
// function: RTMPMoveMemory @ 0x13a500
// size: 108 bytes
//

void RTMPMoveMemory(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  
  if (param_3 != 0) {
    if (param_2 == 0 || param_1 == 0) {
      printk(&_LC16,0x2a1);
      dump_stack();
    }
    iVar2 = 0;
    if (param_1 == 0 || param_2 == 0) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    do {
      if (bVar1) {
        *(undefined1 *)(param_1 + iVar2) = *(undefined1 *)(param_2 + iVar2);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != param_3);
    return;
  }
  return;
}

