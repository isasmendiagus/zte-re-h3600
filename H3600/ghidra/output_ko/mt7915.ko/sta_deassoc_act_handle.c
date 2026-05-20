// module: mt7915.ko
// function: sta_deassoc_act_handle @ 0xc4858
// size: 220 bytes
//

undefined4 sta_deassoc_act_handle(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 4);
  iVar1 = GetStaCfgByWdev(param_1,iVar2);
  if (*(int *)(iVar2 + 0x14) == 2) {
    if (iVar1 != 0) {
      __cntl_disconnect_request(iVar1,1,iVar1 + 0x212428,8,"sta_deassoc_act_handle",0x212);
      return 0;
    }
  }
  else {
    if (*(int *)(iVar2 + 0x14) == 0x100) {
      iVar1 = (uint)*(byte *)(iVar2 + 0xe) * 0x42f4 + *(int *)(&DAT_003687a8 + param_1);
      __cntl_disconnect_request(iVar1 + 0xe0,1,iVar1 + 0x101,8,"sta_deassoc_act_handle",0x20a);
      return 0;
    }
    if (2 < DebugLevel) {
      printk("%s unknown wdev_type\n","sta_deassoc_act_handle");
    }
  }
  return 0;
}

