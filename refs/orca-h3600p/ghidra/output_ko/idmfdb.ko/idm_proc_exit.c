// module: idmfdb.ko
// function: idm_proc_exit @ 0x12108
// size: 16 bytes
//

void idm_proc_exit(void)

{
  proc_remove(proc_parent);
  return;
}

