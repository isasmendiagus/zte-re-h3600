// module: mt7915.ko
// function: HdevExit @ 0xae4d4
// size: 244 bytes
//

undefined4 HdevExit(int param_1,uint param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (param_2 < 2) {
    param_1 = param_1 + param_2 * 0x1c;
    puVar5 = (undefined4 *)(param_1 + 0xc);
    puVar3 = *(undefined4 **)(param_1 + 0xc);
    if (puVar5 != puVar3) {
      puVar4 = (undefined4 *)*puVar3;
      puVar2 = (undefined4 *)*puVar3;
      do {
        puVar1 = puVar2;
        *(undefined1 *)(puVar3 + 2) = 0;
        puVar3[-3] = 0;
        if (puVar4 != (undefined4 *)0x0) {
          puVar4[1] = puVar3[1];
        }
        if ((undefined4 *)puVar3[1] != (undefined4 *)0x0) {
          *(undefined4 *)puVar3[1] = *puVar3;
        }
        *puVar3 = 0;
        puVar3[1] = 0;
        puVar3[-2] = puVar3 + -2;
        puVar3[-1] = puVar3 + -2;
        *(char *)(param_1 + 0x14) = *(char *)(param_1 + 0x14) + -1;
        puVar4 = (undefined4 *)*puVar1;
        puVar2 = puVar4;
        puVar3 = puVar1;
      } while (puVar5 != puVar1);
    }
    *(undefined4 **)(param_1 + 0xc) = puVar5;
    *(undefined4 **)(param_1 + 0x10) = puVar5;
    os_zero_mem(param_1,0x1c);
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s: HdevIdx:%d >= %d\n","HdevExit",param_2,2);
  }
  return 0;
}

