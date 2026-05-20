// module: mt7915.ko
// function: TxBFPlyGetGrpStr @ 0x8769c
// size: 248 bytes
//

void TxBFPlyGetGrpStr(undefined4 param_1,void *param_2)

{
  if (param_2 != (void *)0x0) {
    switch(param_1) {
    case 0:
      os_move_mem(param_2,&DAT_00291d64,4);
      return;
    case 1:
      os_move_mem(param_2,&DAT_00291d6c,4);
      return;
    case 2:
      os_move_mem(param_2,&DAT_00291d74,4);
      return;
    case 3:
      os_move_mem(param_2,&DAT_00291d7c,4);
      return;
    case 4:
      os_move_mem(param_2,&DAT_00291d84,4);
      return;
    case 5:
      os_move_mem(param_2,&DAT_00291d8c,4);
      return;
    case 6:
      os_move_mem(param_2,&DAT_00291d94,4);
      return;
    case 7:
      os_move_mem(param_2,&DAT_00291d9c,4);
      return;
    case 8:
      os_move_mem(param_2,&DAT_00291da4,4);
      return;
    case 9:
      os_move_mem(param_2,&DAT_00291dac,4);
      return;
    case 10:
      os_move_mem(param_2,&DAT_00291db4,4);
      return;
    case 0xb:
      os_move_mem(param_2,&DAT_00291dbc,4);
      return;
    case 0xc:
      os_move_mem(param_2,&DAT_00291dc4,4);
      return;
    case 0xd:
      os_move_mem(param_2,&DAT_00291dcc,4);
      return;
    default:
      return;
    }
  }
  return;
}

