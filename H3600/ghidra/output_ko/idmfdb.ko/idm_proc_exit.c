// module: idmfdb.ko
// function: idm_proc_exit @ 0x11fc0
// size: 16 bytes
//

void idm_proc_exit(void)

{
  proc_remove(proc_parent);
  return;
}

