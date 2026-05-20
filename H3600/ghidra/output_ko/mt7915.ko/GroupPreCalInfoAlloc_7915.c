// module: mt7915.ko
// function: GroupPreCalInfoAlloc_7915 @ 0x1c8b34
// size: 120 bytes
//

int GroupPreCalInfoAlloc_7915(int param_1,int *param_2,int param_3,size_t param_4)

{
  int iVar1;
  int iVar2;
  int local_1c;
  
  iVar2 = param_4 + 0x10;
  iVar1 = os_alloc_mem(param_1,&local_1c,iVar2);
  if (iVar1 == 0) {
    *param_2 = local_1c;
    os_zero_mem(local_1c,iVar2);
    *(char *)(local_1c + 7) = (char)param_3;
    *(size_t *)(local_1c + 0xc) = param_4;
    os_move_mem((void *)(local_1c + 0x10),
                (void *)(*(int *)("RTMPSetSTAPassPhrase" + param_1 + 8) + param_3 * 0x400),param_4);
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

