// module: mt7915.ko
// function: hqa_iBFProfileRead_ext @ 0x277e18
// size: 292 bytes
//

undefined4 hqa_iBFProfileRead_ext(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int local_2c;
  undefined4 local_28;
  byte local_24 [4];
  byte local_20 [4];
  char *local_1c [2];
  
  local_2c = param_3 + 0xc;
  local_28 = 0;
  os_alloc_mem(param_1,local_1c,0x200);
  if (local_1c[0] == (char *)0x0) {
    uVar1 = 3;
  }
  else {
    FUN_00276034(1,4,&local_2c,&local_28);
    FUN_00276034(1,4,&local_2c,local_24);
    FUN_00276034(1,4,&local_2c,local_20);
    __memzero(local_1c[0],0x200);
    sprintf(local_1c[0],"%03x:%03x",(uint)local_24[0],(uint)local_20[0]);
    SetATETxBfProfileRead(param_1,local_1c[0]);
    if (0 < DebugLevel) {
      printk("%s: str:%s\n","hqa_iBFProfileRead_ext",local_1c[0]);
    }
    uVar1 = 0;
    os_free_mem(local_1c[0]);
    *(undefined4 *)(param_3 + 0xe) = local_28;
    memmove((void *)(param_3 + 0x12),(void *)(param_1 + 0xa786e0),0x14);
  }
  FUN_0026cdd0(param_3,param_2,0x1a,uVar1);
  return uVar1;
}

