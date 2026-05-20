// module: mt7915.ko
// function: wdev_config_init @ 0x14de4c
// size: 44 bytes
//

undefined4 wdev_config_init(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + 8);
  do {
    piVar1 = piVar1 + 1;
    iVar2 = *piVar1;
    if (iVar2 != 0) {
      *(undefined1 *)(iVar2 + 0x1a) = 0;
      *(undefined2 *)(iVar2 + 0x18) = 0;
    }
  } while (piVar1 != (int *)(param_1 + 0x1a8));
  return 1;
}

