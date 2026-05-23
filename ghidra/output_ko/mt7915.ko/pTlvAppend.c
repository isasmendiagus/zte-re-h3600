// module: mt7915.ko
// function: pTlvAppend @ 0x1c50d4
// size: 216 bytes
//

int pTlvAppend(void *param_1,undefined2 param_2,size_t param_3,undefined2 *param_4,int *param_5,
              char *param_6)

{
  if (param_4 == (undefined2 *)0x0 || param_3 == 0) {
    if (-1 < DebugLevel) {
      printk("%s::Can not append WTBL TLV\n","pTlvAppend");
    }
    return 0;
  }
  *param_4 = param_2;
  param_4[1] = (short)param_3;
  *param_5 = *param_5 + param_3;
  *param_6 = *param_6 + '\x01';
  os_move_mem(param_1,param_4,param_3);
  if (3 < DebugLevel) {
    printk("%s::T(%d), L(%d), V(%p)\n","pTlvAppend",*param_4,param_4[1],param_4);
  }
  return (int)param_1 + param_3;
}

