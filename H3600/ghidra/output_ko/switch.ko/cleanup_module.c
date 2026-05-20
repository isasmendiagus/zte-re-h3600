// module: switch.ko
// function: cleanup_module @ 0x21fe4
// size: 16 bytes
//

void cleanup_module(void)

{
  l3_hardfastUnReg();
  fuc_table_node_clear();
  return;
}

