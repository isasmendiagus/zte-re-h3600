// module: mt7915.ko
// function: hc_register_chip_ops @ 0xaa6d8
// size: 16 bytes
//

void hc_register_chip_ops(int param_1,void *param_2)

{
  os_move_mem((void *)(param_1 + 0xd64),param_2,0x2fc);
  return;
}

