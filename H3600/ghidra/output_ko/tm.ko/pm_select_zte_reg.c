// module: tm.ko
// function: pm_select_zte_reg @ 0x34d80
// size: 680 bytes
//

undefined4 pm_select_zte_reg(int *param_1,int param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint local_1c;
  
  local_1c = 0;
  iVar3 = 0;
  if (*param_1 == 0) {
    do {
      while (tmOnuRegRead(0xe,&local_1c,iVar3,pmRegTable), param_1[3] == (local_1c << 0x11) >> 0x1d)
      {
        if ((param_1[2] == (local_1c << 0x10) >> 0x1f) && (param_1[4] == (local_1c & 0xfff))) {
          iVar2 = -((int)(local_1c << 0xf) >> 0x1f);
          if (param_2 != 0) goto LAB_00035004;
          if ((iVar2 == 1) && (param_1[1] == 1)) goto LAB_00034e18;
          uVar1 = 0xe;
          local_1c = local_1c & 0xfffeffff | param_1[1] << 0x10;
          goto LAB_00034f34;
        }
        iVar3 = iVar3 + 1;
        if (iVar3 == 0x10) goto LAB_00034e8c;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x10);
LAB_00034e8c:
    if ((param_2 != 0) || (iVar3 = 0, param_1[1] == 0)) goto LAB_00035014;
    do {
      tmOnuRegRead(0xe,&local_1c,iVar3,pmRegTable);
      if ((local_1c & 0x10000) == 0) {
        local_1c = param_1[2] << 0xf | param_1[3] << 0xc | param_1[4] | param_1[1] << 0x10;
        tmOnuRegWrite(0xe,local_1c,iVar3,pmRegTable);
        *param_3 = iVar3;
        return 0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x10);
  }
  else {
    iVar3 = 0;
    do {
      tmOnuRegRead(0xf,&local_1c,iVar3,pmRegTable);
      if ((param_1[3] == (local_1c & 7)) && (param_1[2] == (local_1c << 0x1c) >> 0x1f)) {
        iVar2 = -((int)(local_1c << 0x1b) >> 0x1f);
        if (param_2 != 0) {
LAB_00035004:
          param_1[1] = iVar2;
          *param_3 = iVar3;
          return 0;
        }
        if ((iVar2 == 1) && (param_1[1] == 1)) {
LAB_00034e18:
          printk("This rule already exist!\n");
          return 0xffffffff;
        }
        uVar1 = 0xf;
        local_1c = local_1c & 0xffffffef | param_1[1] << 4;
LAB_00034f34:
        tmOnuRegWrite(uVar1,local_1c,iVar3,pmRegTable);
        *param_3 = iVar3;
        return 0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x10);
    if ((param_2 != 0) || (iVar3 = 0, param_1[1] == 0)) {
LAB_00035014:
      printk("This rule not exist!\n");
      return 0xffffffff;
    }
    do {
      tmOnuRegRead(0xf,&local_1c,iVar3,pmRegTable);
      if ((local_1c & 0x10) == 0) {
        local_1c = param_1[1] << 4 | param_1[2] << 3 | param_1[3];
        tmOnuRegWrite(0xf,local_1c,iVar3,pmRegTable);
        *param_3 = iVar3;
        return 0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x10);
  }
  printk("error:This rule mode is full!\n");
  return 0xffffffff;
}

