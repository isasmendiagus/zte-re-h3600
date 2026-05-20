// module: plat-zxylzb_9128S.ko
// function: check_user_addr @ 0x11018
// size: 64 bytes
//

bool check_user_addr(int param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)find_vma(*(undefined4 *)(param_1 + 0x18c));
  if (puVar1 == (uint *)0x0) {
    return false;
  }
  if (param_2 < *puVar1) {
    return false;
  }
  return param_2 < puVar1[1];
}

