// module: plat-zxylzb_9128S.ko
// function: proc_get_cmd @ 0x102f0
// size: 192 bytes
//

void proc_get_cmd(byte *param_1)

{
  byte bVar1;
  size_t sVar2;
  char *pcVar3;
  byte *pbVar4;
  uint uVar6;
  int iVar7;
  undefined1 *puVar8;
  bool bVar9;
  byte *pbVar5;
  
  proc_argc = 1;
  if (param_1 == (byte *)0x0) {
    return;
  }
  sVar2 = strlen((char *)param_1);
  if (0 < (int)sVar2) {
    pbVar5 = param_1;
    do {
      pbVar4 = pbVar5 + 1;
      bVar1 = *pbVar5;
      bVar9 = 0xc < bVar1;
      if (bVar1 != 0xd) {
        bVar9 = bVar1 != 9;
      }
      if (!bVar9 || (bVar1 == 0xd || bVar1 == 10)) {
        *pbVar5 = 0x20;
      }
      pbVar5 = pbVar4;
    } while (pbVar4 != param_1 + sVar2);
  }
  puVar8 = proc_argv;
  iVar7 = 1;
  do {
    uVar6 = (uint)*param_1;
    bVar1 = (&_ctype)[uVar6];
    while ((bVar1 & 0x20) != 0) {
      param_1 = param_1 + 1;
      uVar6 = (uint)*param_1;
      bVar1 = (&_ctype)[uVar6];
    }
    if (uVar6 == 0) {
      proc_argc = iVar7;
      return;
    }
    puVar8 = (undefined1 *)((int)puVar8 + 4);
    *(byte **)puVar8 = param_1;
    pcVar3 = strchr((char *)param_1,0x20);
    iVar7 = iVar7 + 1;
    if (pcVar3 == (char *)0x0) {
      proc_argc = iVar7;
      return;
    }
    *pcVar3 = '\0';
    param_1 = (byte *)(pcVar3 + 1);
  } while (iVar7 != 0x1e);
  proc_argc = iVar7;
  return;
}

