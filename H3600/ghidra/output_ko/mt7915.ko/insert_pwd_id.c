// module: mt7915.ko
// function: insert_pwd_id @ 0x115f04
// size: 324 bytes
//

void insert_pwd_id(int param_1,int param_2,int param_3)

{
  char *__s;
  char *__s_00;
  size_t sVar1;
  int *piVar2;
  int *local_24 [2];
  
  local_24[0] = (int *)0x0;
  if (param_3 != 0) {
    __s = (char *)rstrtok(param_3,&_LC99);
    __s_00 = (char *)rstrtok(0,&_LC99);
    if (__s_00 == (char *)0x0) {
      os_zero_mem((void *)(param_1 + 0x14d),0x41);
      if (__s != (char *)0x0) {
        sVar1 = strlen(__s);
        os_move_mem((void *)(param_1 + 0x14d),__s,sVar1);
      }
      *(undefined1 *)(param_1 + 0x7e4) = 0;
      return;
    }
    os_alloc_mem(0,local_24,0x74);
    if (local_24[0] != (int *)0x0) {
      os_zero_mem(local_24[0],0x74);
      if (__s == (char *)0x0) {
        sVar1 = 0;
      }
      else {
        sVar1 = strlen(__s);
        os_move_mem(local_24[0] + 2,__s,sVar1);
      }
      piVar2 = local_24[0];
      *(undefined1 *)((int)local_24[0] + sVar1 + 8) = 0;
      sVar1 = strlen(__s_00);
      os_move_mem((void *)((int)piVar2 + 0x49),__s_00,sVar1);
      *(undefined1 *)((int)local_24[0] + sVar1 + 0x49) = 0;
      piVar2 = *(int **)(param_2 + 4);
      *local_24[0] = *piVar2;
      local_24[0][1] = (int)piVar2;
      *(int **)(*piVar2 + 4) = local_24[0];
      *piVar2 = (int)local_24[0];
    }
    *(char *)(param_1 + 0x7e5) = *(char *)(param_1 + 0x7e5) + '\x01';
  }
  return;
}

