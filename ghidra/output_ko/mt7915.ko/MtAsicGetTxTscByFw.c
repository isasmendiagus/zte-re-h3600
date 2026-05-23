// module: mt7915.ko
// function: MtAsicGetTxTscByFw @ 0x198d3c
// size: 88 bytes
//

void MtAsicGetTxTscByFw(undefined4 param_1,int param_2,void *param_3)

{
  undefined2 local_14;
  undefined2 local_12;
  undefined4 local_10;
  undefined4 local_c;
  
  local_12 = 0xc;
  local_10 = 0;
  local_c = 0;
  local_14 = 0xf;
  CmdExtWtblUpdate(param_1,*(undefined2 *)(param_2 + 0x9a0),3,&local_14,0xc);
  os_move_mem(param_3,&local_10,6);
  return;
}

