// module: idmfdb.ko
// function: idm_proc_forbidIdm_seq_show @ 0x11c20
// size: 32 bytes
//

undefined4
idm_proc_forbidIdm_seq_show(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,&_LC0,*(undefined4 *)(*(int *)(param_1 + 0x50) + 8),*(int *)(param_1 + 0x50),
             param_4);
  return 0;
}

