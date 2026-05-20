// module: mt7915.ko
// function: WpaDisassocApAndBlockAssoc @ 0x5774c
// size: 92 bytes
//

void WpaDisassocApAndBlockAssoc(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = GetStaCfgByWdev(*(undefined4 *)(param_2 + 8));
  *(undefined1 *)(iVar1 + 0x2127b8) = 1;
  *(undefined4 *)(iVar1 + 0x2127b4) = 0;
  __cntl_disconnect_request(param_2,1,iVar1 + 0x212428,0xe,"WpaDisassocApAndBlockAssoc",0xf0);
  return;
}

