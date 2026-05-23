// module: mt7915.ko
// function: fnSetCipherKey @ 0x63af0
// size: 388 bytes
//

void fnSetCipherKey(undefined4 param_1,undefined1 param_2,undefined4 param_3,int param_4,
                   void *param_5,int param_6,int param_7)

{
  int iVar1;
  int local_a0 [3];
  undefined2 local_94;
  undefined1 local_92;
  undefined1 local_91;
  undefined1 auStack_90 [81];
  undefined1 auStack_3f [32];
  undefined1 local_1f;
  undefined1 auStack_1e [6];
  
  memset(local_a0,0,0x88);
  iVar1 = GetAssociatedAPByWdev(param_1,param_7);
  if (param_4 == 0) {
    os_zero_mem(local_a0,0x88);
    local_a0[2] = *(uint *)(iVar1 + 0x2c4);
    local_91 = *(undefined1 *)(iVar1 + 0x2c8);
    local_94 = *(undefined2 *)(iVar1 + 0xe0);
    local_92 = *(undefined1 *)(iVar1 + 0xe4);
    local_a0[1] = 2;
    local_a0[0] = param_4;
    os_move_mem(auStack_1e,(void *)(iVar1 + 0xec),6);
    os_move_mem(auStack_90,param_5,0x20);
  }
  else {
    memmove((void *)(iVar1 + 0x3c9),param_5,0x20);
    *(undefined1 *)(iVar1 + 0x3a8) = param_2;
    os_zero_mem(local_a0,0x88);
    local_a0[2] = *(uint *)(iVar1 + 0x3a4);
    local_a0[0] = 2;
    local_94 = *(undefined2 *)(param_7 + 0x9a0);
    local_91 = *(undefined1 *)(iVar1 + 0x3a8);
    local_a0[1] = 1;
    local_92 = 0;
    os_move_mem(auStack_1e,(void *)(iVar1 + 0xec),6);
    os_move_mem(auStack_90,(void *)(iVar1 + 0x3c9),0x20);
    if ((param_6 == 0x20) && ((local_a0[2] & 0x20U) != 0)) {
      os_move_mem(auStack_3f,(void *)((int)param_5 + 0x10),0x10);
      local_1f = 0x10;
    }
  }
  WPAInstallKey(param_1,local_a0,(local_a0[2] & 0x10U) != 0,1);
  return;
}

