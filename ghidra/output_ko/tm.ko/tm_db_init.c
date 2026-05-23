// module: tm.ko
// function: tm_db_init @ 0x5ec00
// size: 116 bytes
//

undefined4 tm_db_init(void)

{
  undefined4 local_134;
  undefined4 local_130 [25];
  undefined1 auStack_cc [16];
  undefined4 local_bc;
  
  local_134 = 0;
  __memzero(local_130,100);
  __memzero(auStack_cc,0xbc);
  operListInit();
  local_130[0] = 0;
  addFlowOperInfo(local_130,auStack_cc,&local_134);
  gs_upDefFlowInit = 1;
  local_bc = 1;
  addFlowOperInfo(local_130,auStack_cc,&local_134);
  gs_downDefFlowInit = 1;
  return 0;
}

