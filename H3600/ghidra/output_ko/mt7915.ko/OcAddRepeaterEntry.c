// module: mt7915.ko
// function: OcAddRepeaterEntry @ 0xacee0
// size: 216 bytes
//

int OcAddRepeaterEntry(int param_1,char param_2)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  char *local_24 [2];
  
  iVar5 = *(int *)(param_1 + 8);
  local_24[0] = (char *)0x0;
  uVar6 = *(undefined4 *)(iVar5 + 0x18);
  iVar3 = os_alloc_mem(0,local_24,0xc);
  if (iVar3 != 0) {
    if (-1 < DebugLevel) {
      printk(" Alloc memory for HD_REPT_ENRTY failed.\n");
    }
    return iVar3;
  }
  OS_SPIN_LOCK(param_1 + 0x20);
  *(char *)(param_1 + 0x1d) = *(char *)(param_1 + 0x1d) + '\x01';
  OS_SPIN_UNLOCK(param_1 + 0x20);
  pcVar1 = local_24[0];
  *local_24[0] = param_2;
  cVar2 = GetOmacIdx(uVar6,0x100,iVar5,(int)param_2);
  pcVar1[1] = cVar2;
  piVar4 = *(int **)(param_1 + 0x10);
  *(int *)(local_24[0] + 4) = *piVar4;
  *(int **)(local_24[0] + 8) = piVar4;
  *(char **)(*piVar4 + 4) = local_24[0] + 4;
  *piVar4 = (int)(local_24[0] + 4);
  return 0;
}

