// module: idmfdb.ko
// function: idm_proc_dbg_write @ 0x11ac0
// size: 60 bytes
//

undefined4 idm_proc_dbg_write(undefined4 param_1,int param_2,undefined4 param_3)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_2 + -1);
  ifd_debug = 0;
  while( true ) {
    pbVar1 = pbVar1 + 1;
    if (9 < *pbVar1 - 0x30) break;
    ifd_debug = (*pbVar1 - 0x30) + ifd_debug * 10;
  }
  return param_3;
}

