// module: mt7915.ko
// function: ba_ctl_init @ 0xa88f8
// size: 112 bytes
//

void ba_ctl_init(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *(undefined4 *)(param_2 + 0x2f4c4) = 0;
  *(undefined4 *)(param_2 + 0x2f4c0) = 0;
  *(undefined4 *)(param_2 + 0x2f4c8) = 0;
  *(undefined4 *)(param_2 + 0x2f400) = 0;
  *(undefined1 *)(param_2 + 0x2f42c) = 0;
  os_zero_mem(param_2 + 0x2f430,0x90);
  iVar1 = param_2;
  do {
    iVar2 = iVar1;
    *(undefined4 *)(iVar2 + 8) = 0;
    *(undefined4 *)(iVar2 + 0x10) = 0;
    iVar1 = iVar2 + 0x60;
  } while (iVar2 + 0x60 != param_2 + 0x1b000);
  puVar3 = (undefined4 *)(iVar2 + 0x6c);
  do {
    puVar4 = puVar3 + 0x12;
    *puVar3 = 0;
    puVar3 = puVar4;
  } while (puVar4 != (undefined4 *)(param_2 + 0x2f40c));
  return;
}

