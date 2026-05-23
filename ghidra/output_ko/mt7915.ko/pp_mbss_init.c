// module: mt7915.ko
// function: pp_mbss_init @ 0x171a64
// size: 272 bytes
//

undefined4 pp_mbss_init(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 local_1c;
  undefined1 local_1b;
  char local_1a;
  bool local_19;
  
  if (param_2 != 0) {
    iVar2 = HcGetBandByWdev(param_2);
    if (2 < DebugLevel) {
      printk("%s: Preamble puncture initialize via profile.\n","pp_mbss_init");
    }
    cVar1 = *(char *)(param_1 + iVar2 + 0x795b1e);
    os_zero_mem(&local_1c);
    local_1c = 1;
    local_19 = cVar1 == '\x01';
    local_1b = (undefined1)iVar2;
    local_1a = cVar1;
    if (2 < DebugLevel) {
      printk("%s: pp_en %d, pp_auto_mode %d\n","pp_mbss_init",cVar1,local_19);
    }
    iVar3 = pp_cmd_cap_ctrl(param_1,&local_1c);
    if ((iVar3 == 1) && (-1 < DebugLevel)) {
      printk("%s: Set pp_enable[%d]=%d Fail!\n","pp_mbss_init",iVar2,
             *(undefined1 *)(param_1 + iVar2 + 0x795b1e));
    }
    return 0;
  }
  return 1;
}

