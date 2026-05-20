// module: mt7915.ko
// function: vow_fill_group_all @ 0x40aa8
// size: 836 bytes
//

void vow_fill_group_all(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  iVar5 = param_1 + param_2 * 0x1c;
  iVar4 = param_3 + param_2 * 0x10;
  *(undefined2 *)(iVar4 + 0x10) = *(undefined2 *)(iVar5 + 0xa79838);
  param_3 = param_3 + (param_2 + 1) * 0x10;
  *(undefined2 *)(iVar4 + 0x12) = *(undefined2 *)(iVar5 + 0xa7983a);
  *(undefined1 *)(iVar4 + 0x14) = *(undefined1 *)(iVar5 + 0xa79834);
  bVar1 = *(byte *)(param_3 + 6);
  *(undefined1 *)(param_3 + 5) = *(undefined1 *)(iVar5 + 0xa7983c);
  bVar3 = *(byte *)(iVar5 + 0xa7983d) & 7;
  *(byte *)(param_3 + 6) = bVar1 & 0xf8 | bVar3;
  *(byte *)(param_3 + 6) = bVar1 & 8 | bVar3 | *(char *)(iVar5 + 0xa7982e) << 4;
  *(char *)(param_3 + 7) = (char)(((uint)*(ushort *)(iVar5 + 0xa7982e) << 0x14) >> 0x18);
  bVar1 = *(byte *)(iVar4 + 0x1a);
  *(undefined1 *)(iVar4 + 0x18) = *(undefined1 *)(iVar5 + 0xa79835);
  *(undefined1 *)(iVar4 + 0x19) = *(undefined1 *)(iVar5 + 0xa7983e);
  bVar3 = *(byte *)(iVar5 + 0xa7983f) & 7;
  *(byte *)(iVar4 + 0x1a) = bVar1 & 0xf8 | bVar3;
  *(byte *)(iVar4 + 0x1a) = bVar1 & 8 | bVar3 | *(char *)(iVar5 + 0xa79830) << 4;
  *(char *)(iVar4 + 0x1b) = (char)(((uint)*(ushort *)(iVar5 + 0xa79830) << 0x14) >> 0x18);
  *(undefined1 *)(iVar4 + 0x1c) = *(undefined1 *)(iVar5 + 0xa79836);
  *(undefined1 *)(iVar4 + 0x1e) = *(undefined1 *)(iVar5 + 0xa79832);
  iVar2 = DebugLevel;
  *(byte *)(iVar4 + 0x1f) = *(byte *)(iVar4 + 0x1f) & 0xf0 | *(byte *)(iVar5 + 0xa79833) & 0xf;
  if (iVar2 < 4) {
    return;
  }
  iVar2 = param_2 * 0x1c + param_1;
  uVar7 = (uint)*(ushort *)(iVar2 + 0xa7982a);
  uVar8 = (uint)*(byte *)(iVar2 + 0xa7982c);
  uVar6 = (uint)*(byte *)(iVar2 + 0xa7982d);
  printk("%s:(Group id = 0x%x, min_rate %d, max_rate %d, min_ratio %d, max_ratio %d)\n",
         "vow_fill_group_all",param_2,*(undefined2 *)(iVar2 + 0xa79828),uVar7,uVar8,uVar6);
  if (DebugLevel < 4) {
LAB_00040cc8:
    if (DebugLevel < 4) goto LAB_00040d88;
    iVar2 = param_2 * 0x1c + param_1;
    printk("%s:(min rate bucket = 0x%x)\n","vow_fill_group_all",*(undefined2 *)(iVar2 + 0xa7982e),
           iVar2 + 0xa79828,uVar7,uVar8,uVar6);
    if (DebugLevel < 4) {
      return;
    }
    printk("%s:(max rate bucket = 0x%x)\n","vow_fill_group_all",*(undefined2 *)(iVar2 + 0xa79830),
           0xa79830,uVar7,uVar8,uVar6);
  }
  else {
    printk("%s:(min rate token = 0x%x)\n","vow_fill_group_all",*(undefined2 *)(iVar2 + 0xa79838),
           DebugLevel,uVar7,uVar8,uVar6);
    if (DebugLevel < 4) {
      return;
    }
    printk("%s:(max rate token = 0x%x)\n","vow_fill_group_all",*(undefined2 *)(iVar2 + 0xa7983a),
           DebugLevel,uVar7,uVar8,uVar6);
    if (3 < DebugLevel) {
      printk("%s:(min airtime token = 0x%x)\n","vow_fill_group_all",
             *(undefined2 *)(iVar2 + 0xa7983c),DebugLevel,uVar7,uVar8,uVar6);
      if (DebugLevel < 4) {
        return;
      }
      printk("%s:(max airtime token = 0x%x)\n","vow_fill_group_all",
             *(undefined2 *)(iVar2 + 0xa7983e),DebugLevel,uVar7,uVar8,uVar6);
      goto LAB_00040cc8;
    }
  }
  if (DebugLevel < 4) {
    return;
  }
  iVar2 = param_2 * 0x1c + param_1;
  printk("%s:(min airtime bucket = 0x%x)\n","vow_fill_group_all",*(undefined1 *)(iVar2 + 0xa79834),
         iVar2,uVar7,uVar8,uVar6);
  if (DebugLevel < 4) {
    return;
  }
  printk("%s:(max airtime bucket = 0x%x)\n","vow_fill_group_all",*(undefined1 *)(iVar2 + 0xa79835));
LAB_00040d88:
  if (3 < DebugLevel) {
    param_1 = param_2 * 0x1c + param_1;
    printk("%s:(max baclog size = 0x%x)\n","vow_fill_group_all",*(undefined2 *)(param_1 + 0xa79832),
           0x1c,uVar7,uVar8,uVar6);
    if (3 < DebugLevel) {
      printk("%s:(max wait time = 0x%x)\n","vow_fill_group_all",*(undefined1 *)(param_1 + 0xa79836))
      ;
      return;
    }
  }
  return;
}

