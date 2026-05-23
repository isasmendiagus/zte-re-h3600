// module: mt7915.ko
// function: mt_engine_calc_ipg_param_by_ipg @ 0x2559ac
// size: 480 bytes
//

undefined4 mt_engine_calc_ipg_param_by_ipg(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0xc14);
  if (*(char *)(param_1 + 0xc55) == '\0') {
    uVar3 = 0x13;
    iVar1 = 0;
  }
  else {
    iVar1 = 6;
    uVar3 = 0x19;
  }
  printk("%s: expected ipg=%d\n","mt_engine_calc_ipg_param_by_ipg",uVar2);
  if (uVar2 < uVar3) {
    *(undefined4 *)(param_1 + 0xc14) = 0;
    printk("%s: invalid ipg!! ","mt_engine_calc_ipg_param_by_ipg");
    printk("sig_ext/slot_time/sifs_time=%d/%d/%d, ",iVar1,9,10);
    printk("set ipg=%d\n",uVar2);
    if (*(int *)(param_1 + 0xc08) != 0) {
      *(undefined4 *)(param_1 + 0xc08) = 0;
      printk("%s: invalid ipg!! ","mt_engine_calc_ipg_param_by_ipg");
      printk("set duty_cycle=%d\n",*(undefined4 *)(param_1 + 0xc08));
    }
  }
  else {
    uVar2 = uVar2 - iVar1;
    if (uVar2 < 0x89) {
      uVar3 = 0;
      uVar4 = 1;
      uVar2 = uVar2 - 9 & 0xffff;
    }
    else {
      uVar4 = 0;
      uVar3 = (uVar2 + 9) / 9;
      while (uVar3 = uVar3 >> 1, uVar3 != 0) {
        uVar4 = uVar4 + 1;
      }
      if (0xf < uVar4) {
        uVar4 = 0x10;
      }
      uVar3 = uVar4 & 0xffff;
      uVar2 = (1 - (1 << (uVar4 & 0xff))) * 9 + uVar2;
      uVar4 = (uint)((int)((ulonglong)uVar2 * 0x38e38e39 >> 0x20) << 0x17) >> 0x18;
      if (0xe < uVar4) {
        uVar4 = 0xf;
      }
      uVar2 = uVar2 + uVar4 * -9;
      if (uVar2 < 0xb) {
        uVar2 = 10;
      }
      else if (uVar2 - 0xb < 0x75) {
        uVar2 = uVar2 & 0xffff;
      }
      else {
        uVar2 = 0x7f;
      }
    }
    *(char *)(param_1 + 0xc18) = (char)iVar1;
    *(short *)(param_1 + 0xc1c) = (short)uVar2;
    *(undefined2 *)(param_1 + 0xc1a) = 9;
    *(char *)(param_1 + 0xc1f) = (char)uVar4;
    *(short *)(param_1 + 0xc20) = (short)uVar3;
    *(undefined2 *)(param_1 + 0xc22) = 0;
    printk("%s: sig_ext=%d, slot_time=%d, sifs_time=%d, ","mt_engine_calc_ipg_param_by_ipg",iVar1,9,
           uVar2);
    printk("aifsn=%d, cw=%d, ",uVar4,uVar3);
    printk("real ipg=%d\n",(short)uVar4 * 9 + uVar2 + iVar1 + ~(-1 << (uVar3 & 0xff)) * 9);
  }
  return 0;
}

