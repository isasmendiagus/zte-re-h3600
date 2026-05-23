// module: mt7915.ko
// function: Set_WPAPSK_Proc @ 0x587dc
// size: 316 bytes
//

undefined4 Set_WPAPSK_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  int iVar2;
  void *__dest;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  sVar1 = strlen(param_2);
  if (sVar1 < 0x41) {
    os_move_mem((void *)((int)param_1 + iVar2 * 0x2137b0 + 0x36dcd1),param_2,sVar1);
    sVar1 = strlen(param_2);
    (&DAT_0036dcd1)[(int)param_1 + sVar1 + iVar2 * 0x2137b0] = 0;
  }
  else {
    *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x36dcd1) = 0;
  }
  if (2 < DebugLevel) {
    printk("%s:: PSK=%s\n","Set_WPAPSK_Proc",param_2,DebugLevel,param_4);
  }
  __dest = (void *)((int)param_1 + iVar2 * 0x2137b0 + 0x3717d9);
  __memzero(__dest,0x40);
  param_1[iVar2 * 0x84dec + 0xdc607] = 0;
  sVar1 = strlen(param_2);
  memmove(__dest,param_2,sVar1);
  sVar1 = strlen(param_2);
  param_1[iVar2 * 0x84dec + 0xdc607] = sVar1;
  return 0;
}

