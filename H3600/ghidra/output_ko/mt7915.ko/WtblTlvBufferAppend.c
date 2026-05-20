// module: mt7915.ko
// function: WtblTlvBufferAppend @ 0x1c4fd0
// size: 152 bytes
//

void WtblTlvBufferAppend(undefined4 param_1,undefined2 param_2,size_t param_3,undefined2 *param_4)

{
  void *__dest;
  
  if (param_4 != (undefined2 *)0x0 && param_3 != 0) {
    *param_4 = param_2;
    param_4[1] = (short)param_3;
    __dest = (void *)skb_put(param_1,param_3);
    os_move_mem(__dest,param_4,param_3);
    if (2 < DebugLevel) {
      printk("%s::T(%d), L(%d), V(%p)\n","WtblTlvBufferAppend",*param_4,param_4[1],param_4);
    }
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s::Can not append WTBL TLV\n","WtblTlvBufferAppend");
  return;
}

