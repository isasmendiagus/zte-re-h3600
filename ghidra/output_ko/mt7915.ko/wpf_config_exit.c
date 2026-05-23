// module: mt7915.ko
// function: wpf_config_exit @ 0x105d88
// size: 140 bytes
//

void wpf_config_exit(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar1 = (undefined1 *)(param_1 + 0xa7c558);
  do {
    iVar2 = *(int *)(puVar1 + 8);
    *puVar1 = (char)iVar3;
    iVar3 = iVar3 + 1;
    if (iVar2 != 0) {
      phy_cfg_exit(iVar2);
      ht_cfg_exit(iVar2 + 0x14);
      vht_cfg_exit(iVar2 + 0x5c);
      he_cfg_exit(iVar2 + 100);
      os_free_mem(*(undefined4 *)(puVar1 + 8));
    }
    *(undefined4 *)(puVar1 + 8) = 0;
    if (*(int *)(puVar1 + 0xc) != 0) {
      os_free_mem();
    }
    *(undefined4 *)(puVar1 + 0xc) = 0;
    puVar1 = puVar1 + 0x10;
  } while (iVar3 != 0x68);
  os_zero_mem((undefined1 *)(param_1 + 0xa7c558),0x680);
  return;
}

