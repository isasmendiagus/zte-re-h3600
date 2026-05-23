// module: mt7915.ko
// function: event_ecc_result @ 0x1a8df4
// size: 104 bytes
//

void event_ecc_result(undefined4 param_1,int param_2)

{
  if (0 < DebugLevel) {
    printk("ucEccCmdId = %d, ucIsResFail= %d\n",*(undefined1 *)(param_2 + 6),
           *(undefined1 *)(param_2 + 7));
  }
  hex_dump_with_lvl(&_LC176,param_2 + 8,*(undefined1 *)(param_2 + 4),1);
  hex_dump_with_lvl(&_LC177,param_2 + 0x38,*(undefined1 *)(param_2 + 5),1);
  return;
}

