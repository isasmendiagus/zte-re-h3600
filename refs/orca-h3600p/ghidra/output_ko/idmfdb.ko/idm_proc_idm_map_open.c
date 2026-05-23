// module: idmfdb.ko
// function: idm_proc_idm_map_open @ 0x11bb4
// size: 36 bytes
//

void idm_proc_idm_map_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_idm_map_seq_show,uVar1);
  return;
}

