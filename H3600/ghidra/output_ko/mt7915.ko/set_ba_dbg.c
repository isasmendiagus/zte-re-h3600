// module: mt7915.ko
// function: set_ba_dbg @ 0xc3ae0
// size: 328 bytes
//

undefined4 set_ba_dbg(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  if (((param_2 == (char *)0x0) || (*param_2 == '\0')) ||
     (iVar1 = sscanf(param_2,"%u:%u:%u:%u:%u:%u:%u:%u",&local_28,&local_24,&local_20,&local_1c,
                     &local_18,&local_14,&local_10,&local_c), iVar1 != 8)) {
    if (-1 < DebugLevel) {
      printk(
            "please input record_basic:record_mac:dump_within:dump_surpass:dump_old:dump_dup:dump_stepone:dump_bar\n"
            );
    }
  }
  else {
    if (local_28 == 0) {
      uVar2 = *(uint *)(param_1 + 0x2f68c) & 0xfffffffd;
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x2f68c) | 2;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
    if (local_24 == 0) {
      uVar2 = uVar2 & 0xfffffffb;
    }
    else {
      uVar2 = uVar2 | 4;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
    if (local_20 == 0) {
      uVar2 = uVar2 & 0xfffffff7;
    }
    else {
      uVar2 = uVar2 | 8;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
    if (local_1c == 0) {
      uVar2 = uVar2 & 0xffffffef;
    }
    else {
      uVar2 = uVar2 | 0x10;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
    if (local_18 == 0) {
      uVar2 = uVar2 & 0xffffffdf;
    }
    else {
      uVar2 = uVar2 | 0x20;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
    if (local_14 == 0) {
      uVar2 = uVar2 & 0xffffffbf;
    }
    else {
      uVar2 = uVar2 | 0x40;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
    if (local_10 == 0) {
      uVar2 = uVar2 & 0xffffff7f;
    }
    else {
      uVar2 = uVar2 | 0x80;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
    if (local_c == 0) {
      uVar2 = uVar2 & 0xfffffeff;
    }
    else {
      uVar2 = uVar2 | 0x100;
    }
    *(uint *)(param_1 + 0x2f68c) = uVar2;
  }
  return 1;
}

