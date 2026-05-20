// module: tm.ko
// function: pm_select_g988_reg @ 0x347b4
// size: 444 bytes
//

undefined4 pm_select_g988_reg(int *param_1,int param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_28;
  int local_24;
  
  iVar2 = *param_1;
  local_28 = 0;
  local_24 = 0;
  if (iVar2 == 0) {
    uVar5 = 7;
    uVar3 = 0;
    uVar4 = uVar3;
  }
  else if (iVar2 == 1) {
    uVar5 = 0xf;
    uVar3 = 8;
    uVar4 = uVar3;
  }
  else {
    if (iVar2 != 3) {
      printk("error:This rule mode not support!\n");
      return 0xffffffff;
    }
    uVar5 = 0x3f;
    uVar3 = 0x10;
    uVar4 = uVar3;
  }
  while( true ) {
    tmOnuRegRead(0xd,&local_28,uVar3,pmRegTable);
    uVar1 = local_28;
    pm_check_g988_rule(local_28,param_1,&local_24);
    if (local_24 == 1) break;
    uVar3 = uVar3 + 1;
    if (uVar5 < uVar3) {
      if ((param_2 == 0) && (param_1[1] != 0)) {
        if (uVar4 <= uVar5) {
          do {
            tmOnuRegRead(0xd,&local_28,uVar4,pmRegTable);
            if ((local_28 & 0x100000) == 0) {
              pm_add_g988_rule(param_1,uVar4);
              *param_3 = uVar4;
              return 0;
            }
            uVar4 = uVar4 + 1;
          } while (uVar4 != uVar5 + 1);
        }
        printk("error:This rule mode is full!\n");
      }
      else {
        printk("This rule not exist!\n");
      }
      return 0xffffffff;
    }
  }
  iVar2 = -((int)(uVar1 << 0xb) >> 0x1f);
  if (param_2 != 0) {
    param_1[1] = iVar2;
    *param_3 = uVar3;
    return 0;
  }
  if ((iVar2 == 1) && (param_1[1] == 1)) {
    printk("This rule already exist!\n");
    return 0xffffffff;
  }
  local_28 = local_28 & 0xffefffff | param_1[1] << 0x14;
  tmOnuRegWrite(0xd,local_28,uVar3,pmRegTable);
  *param_3 = uVar3;
  return 0;
}

