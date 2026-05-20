// module: mt7915.ko
// function: TxBFPlyGetPlyStr @ 0x87804
// size: 104 bytes
//

void TxBFPlyGetPlyStr(undefined4 param_1,void *param_2)

{
  if (param_2 != (void *)0x0) {
    switch(param_1) {
    case 0:
      os_move_mem(param_2,&DAT_00291dd4,4);
      return;
    case 1:
      os_move_mem(param_2,&DAT_00291ddc,4);
      return;
    case 2:
      os_move_mem(param_2,&DAT_00291de4,4);
      return;
    case 3:
      os_move_mem(param_2,&DAT_00291dec,4);
      return;
    case 4:
      os_move_mem(param_2,&DAT_00291df4,4);
      return;
    default:
      return;
    }
  }
  return;
}

