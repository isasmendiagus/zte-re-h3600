// module: mt7915.ko
// function: twt_ctrl_init @ 0x16a788
// size: 204 bytes
//

void twt_ctrl_init(int param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  undefined1 *puVar4;
  char cVar5;
  int iVar6;
  
  os_zero_mem(param_1 + 0x2c38,0x4a0);
  iVar6 = 0;
  *(undefined4 *)(param_1 + 0x30d0) = 0;
  puVar4 = (undefined1 *)(param_1 + 0x2c49);
  cVar1 = *(char *)(param_1 + 0x2c38);
  cVar5 = *(char *)(param_1 + 0x2c39);
  do {
    *puVar4 = (char)iVar6;
    iVar6 = iVar6 + 1;
    puVar4[-1] = 0;
    puVar4[0x2b] = 0;
    puVar4 = puVar4 + 0x48;
  } while (iVar6 != 8);
  cVar2 = *(char *)(param_1 + 0x2c3a);
  *(char *)(param_1 + 0x2c39) = cVar5 + '\b';
  *(char *)(param_1 + 0x2c38) = cVar1 + '\b';
  puVar4 = (undefined1 *)(param_1 + 0x2e88);
  cVar5 = '\b';
  do {
    cVar3 = cVar5 + '\x01';
    puVar4[1] = cVar5;
    *puVar4 = 0;
    puVar4[0x2c] = 1;
    puVar4 = puVar4 + 0x48;
    cVar5 = cVar3;
  } while (cVar3 != '\x10');
  *(char *)(param_1 + 0x2c38) = cVar1 + '\x10';
  *(char *)(param_1 + 0x2c3a) = cVar2 + '\b';
  *(int *)(param_1 + 0x30c8) = param_1 + 0x30c8;
  *(int *)(param_1 + 0x30cc) = param_1 + 0x30c8;
  *(int *)(param_1 + 0x30c0) = param_1 + 0x30c0;
  *(int *)(param_1 + 0x30c4) = param_1 + 0x30c0;
  return;
}

