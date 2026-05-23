// module: mt7915.ko
// function: HdevInit @ 0xae3e0
// size: 240 bytes
//

undefined4 HdevInit(int param_1,uint param_2,char *param_3)

{
  uint uVar1;
  int iVar2;
  
  if (param_2 < 2) {
    iVar2 = param_1 + param_2 * 0x1c;
    os_zero_mem(iVar2,0x1c);
    *(int *)(iVar2 + 0xc) = iVar2 + 0xc;
    *(int *)(iVar2 + 0x10) = iVar2 + 0xc;
    *(char **)(param_1 + param_2 * 0x1c + 4) = param_3;
    *(int *)(iVar2 + 0x18) = param_1;
    *(char *)(param_1 + param_2 * 0x1c) = (char)param_2;
    *(undefined1 *)(iVar2 + 0x14) = 0;
    if ((*param_3 != '\x01') || (uVar1 = hc_get_asic_cap(param_1), (uVar1 & 0x800000) == 0)) {
      *(int *)(param_1 + param_2 * 0x1c + 8) = param_1 + 0x1a10;
      return 0;
    }
    *(int *)(iVar2 + 8) = param_1 + 0x1a1c;
  }
  else if (-1 < DebugLevel) {
    printk("%s: HdevIdx:%d >= %d\n","HdevInit",param_2,2);
  }
  return 0;
}

