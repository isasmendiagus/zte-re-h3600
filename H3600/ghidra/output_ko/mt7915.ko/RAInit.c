// module: mt7915.ko
// function: RAInit @ 0x1d91e4
// size: 296 bytes
//

void RAInit(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_40 [40];
  
  iVar2 = param_2 + 0x13c0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(iVar2,0x44);
  os_zero_mem(param_2 + 0x1404,0x20);
  os_zero_mem(auStack_40,0x28);
  raWrapperEntrySet(param_1,param_2,iVar2);
  raWrapperConfigSet(param_1,*(undefined4 *)(param_2 + 8),auStack_40);
  *(undefined1 *)(param_2 + 0x1405) = 1;
  *(undefined1 *)(param_2 + 0x140a) = 0xff;
  *(undefined1 *)(param_2 + 0x1406) = 0;
  *(undefined1 *)(param_2 + 0x1404) = 0;
  *(undefined1 *)(param_2 + 0x1414) = 0;
  *(undefined1 *)(param_2 + 0x1409) = 0;
  *(undefined1 *)(param_2 + 0x140c) = 0;
  if (*(char *)(iVar1 + 0x150) == '\x01') {
    *(undefined1 *)(param_2 + 0x13c0) = 1;
    WifiSysRaInit(param_1,param_2);
  }
  *(uint *)(param_1 + 0xa39f9c) =
       (*(byte *)(param_2 + 0x13f9) & 7) << 0xd | *(byte *)(param_2 + 0x13ff) & 0x3f |
       (*(byte *)(param_2 + 0x13fd) & 3) << 7 | (uint)(*(char *)(param_2 + 0x13fe) != '\0') << 6 |
       (uint)(*(char *)(param_2 + 0x13fc) != '\0') << 9 | (*(byte *)(param_2 + 0x13fb) & 1) << 10;
  raWrapperEntryRestore(param_1,param_2,iVar2);
  return;
}

