// module: plat-zxylzb_9128S.ko
// function: user_va2pa @ 0x10fd8
// size: 64 bytes
//

int user_va2pa(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *(uint *)((*(uint *)(*(int *)(*(int *)(param_1 + 0x18c) + 0x24) + (param_2 >> 0x15) * 8) &
                    0xfffff000) + ((param_2 << 0xb) >> 0x17) * 4 + 0x7ffff800);
  iVar2 = 0;
  if (uVar1 != 0) {
    iVar2 = (uVar1 & 0xfffff000) + (param_2 & 0xfff);
  }
  return iVar2;
}

