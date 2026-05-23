// module: plat-zxylzb_9128S.ko
// function: shell_dump_sym_data @ 0x1071c
// size: 596 bytes
//

void shell_dump_sym_data(uint *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  byte bStack_6d;
  uint local_6c [18];
  
  if (param_2 == 0) {
    if (data_cnt == 1) {
      DataSynchronizationBarrier(0xf);
      printk("sym %s is %d(0x%.2x)\n",sym,(byte)*param_1,(byte)*param_1);
      iVar5 = 1;
    }
    else {
      iVar5 = 1;
    }
  }
  else if (param_2 == 1) {
    if (data_cnt == 1) {
      DataSynchronizationBarrier(0xf);
      printk("sym %s is %d(0x%.4x)\n",sym,(ushort)*param_1,(ushort)*param_1);
      iVar5 = 1;
    }
    else {
      iVar5 = 2;
    }
  }
  else if (data_cnt == 1) {
    DataSynchronizationBarrier(0xf);
    printk("sym %s is %d(0x%.8x)\n",sym,*param_1,*param_1);
    iVar5 = 1;
  }
  else {
    iVar5 = 4;
  }
  if ((1 < (int)data_cnt) && (uVar6 = data_cnt & 0xffff, uVar6 != 0)) {
    uVar1 = __aeabi_idiv(0x10,iVar5);
    do {
      printk("%08x:",param_1);
      uVar8 = 0;
      puVar7 = param_1;
      if ((int)uVar6 <= (int)uVar1) {
        uVar1 = uVar6;
      }
      do {
        if (iVar5 == 4) {
          uVar3 = *puVar7;
          DataSynchronizationBarrier(0xf);
          local_6c[uVar8] = uVar3;
        }
        else if (iVar5 == 2) {
          uVar3 = (uint)(ushort)*puVar7;
          DataSynchronizationBarrier(0xf);
          *(ushort *)((int)local_6c + uVar8 * 2) = (ushort)*puVar7;
        }
        else {
          uVar3 = (uint)(byte)*puVar7;
          DataSynchronizationBarrier(0xf);
          *(byte *)((int)local_6c + uVar8) = (byte)*puVar7;
        }
        uVar8 = uVar8 + 1;
        printk(" %0*x",(int)(short)iVar5 << 1,uVar3);
        puVar7 = (uint *)((int)puVar7 + iVar5);
      } while (uVar8 != uVar1);
      iVar2 = uVar1 * iVar5;
      param_1 = (uint *)((int)param_1 + iVar5 * (uVar1 - 1) + iVar5);
      if (iVar2 < 1) {
        iVar2 = 0;
      }
      else {
        pbVar4 = &bStack_6d;
        do {
          pbVar4 = pbVar4 + 1;
          if ((((&_ctype)[*pbVar4] & 0x97) == 0) || ((*pbVar4 & 0x80) != 0)) {
            *pbVar4 = 0x2e;
          }
        } while (pbVar4 != (byte *)((int)local_6c + iVar2 + -1));
      }
      *(undefined1 *)((int)local_6c + iVar2) = 0;
      printk("    %s\n",local_6c);
      uVar6 = uVar6 - uVar1 & 0xffff;
    } while (uVar6 != 0);
  }
  return;
}

