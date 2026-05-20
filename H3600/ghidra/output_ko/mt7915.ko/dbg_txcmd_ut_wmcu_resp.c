// module: mt7915.ko
// function: dbg_txcmd_ut_wmcu_resp @ 0x28ddc4
// size: 88 bytes
//

void dbg_txcmd_ut_wmcu_resp(int param_1,int param_2,int param_3)

{
  printk(&_LC0,"FRAMEWORK","dbg_txcmd_ut_wmcu_resp",*(undefined4 *)(param_2 + 4),
         *(undefined4 *)(param_2 + 8),param_3);
  os_move_mem(*(void **)(param_1 + 0xc),(void *)(param_2 + 0x10),param_3 - 0x10);
  return;
}

