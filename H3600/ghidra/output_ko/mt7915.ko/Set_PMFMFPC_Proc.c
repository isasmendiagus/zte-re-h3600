// module: mt7915.ko
// function: Set_PMFMFPC_Proc @ 0x21af10
// size: 368 bytes
//

undefined4 Set_PMFMFPC_Proc(int *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  
  if (*param_2 == '\0') {
    return 0;
  }
  cVar4 = *(char *)((int)param_1 + 0x286285);
  if (cVar4 == '\x01') {
    iVar3 = *param_1;
    iVar1 = os_str_tol(param_2,0,10);
    iVar2 = *(int *)(iVar3 + 0x3c);
    if (iVar1 == 0) {
      *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2b7655) = 0;
    }
    else {
      *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2b7655) = 1;
    }
    if (0 < DebugLevel) {
      iVar1 = *(int *)(iVar3 + 0x3c);
      printk("[PMF]%s:: apidx=%d, Desired MFPC=%d\n","Set_PMFMFPC_Proc",iVar1,
             *(undefined1 *)((int)param_1 + iVar1 * 0x5834 + 0x2b7655));
    }
    cVar4 = *(char *)((int)param_1 + 0x286285);
  }
  if (cVar4 == '\0') {
    iVar3 = *param_1;
    iVar1 = os_str_tol(param_2,0,10);
    iVar2 = *(int *)(iVar3 + 0x3c);
    if (iVar1 == 0) {
      *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x36df65) = 0;
    }
    else {
      *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x36df65) = 1;
    }
    if (0 < DebugLevel) {
      iVar1 = *(int *)(iVar3 + 0x3c);
      printk("[PMF]%s:: staidx=%d, Desired MFPC=%d\n","Set_PMFMFPC_Proc",iVar1,
             *(undefined1 *)((int)param_1 + iVar1 * 0x2137b0 + 0x36df65));
    }
  }
  return 1;
}

