// module: switch.ko
// function: cleanup_module @ 0x220e8
// size: 32 bytes
//

void cleanup_module(void)

{
  l3_hardfastUnReg();
  remove_proc_entry("tcphy",0);
  fuc_table_node_clear();
  return;
}

