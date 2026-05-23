// module: mt7915.ko
// function: mt7915_dump_ser_stat @ 0x17a10c
// size: 432 bytes
//

void mt7915_dump_ser_stat(int param_1,int param_2)

{
  undefined *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_134;
  uint local_130;
  undefined4 local_12c [18];
  undefined4 local_e4 [48];
  
  puVar5 = local_e4 + 0x14;
  memcpy(local_e4,&DAT_0029b6a8,0x50);
  memcpy(puVar5,&DAT_0029b6f8,0x6c);
  memcpy(local_12c,&DAT_0029b764,0x48);
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
     ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x10] == '\0')) {
    iVar4 = 9;
    puVar3 = puVar5;
  }
  else {
    iVar4 = 6;
    puVar3 = local_12c;
  }
  puVar2 = local_e4;
  do {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),puVar2[1],&local_134);
    if ((local_134 != 0) && (0 < DebugLevel)) {
      printk("%s,::E  R , %s = 0x%08X\n","mt7915_dump_ser_stat",*puVar2);
    }
    puVar2 = puVar2 + 2;
  } while (puVar2 != puVar5);
  if (param_2 != 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f2a0,&local_130);
    if (0 < DebugLevel) {
      printk("%s,::E  R , HWITS_WAR_EN_MASK = 0x%08X\n","mt7915_dump_ser_stat",local_130);
    }
    puVar5 = puVar3 + iVar4 * 3;
    do {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),puVar3[2],&local_134);
      if (0 < DebugLevel) {
        puVar1 = &_LC277;
        if ((puVar3[1] & local_130) == 0) {
          puVar1 = &_LC278;
        }
        printk("\t(WAR_%s) %s=%d\n",puVar1,*puVar3,local_134);
      }
      puVar3 = puVar3 + 3;
    } while (puVar3 != puVar5);
  }
  Show_MibBucket_Proc(param_1,&_LC276);
  return;
}

