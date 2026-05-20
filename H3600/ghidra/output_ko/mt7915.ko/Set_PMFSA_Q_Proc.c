// module: mt7915.ko
// function: Set_PMFSA_Q_Proc @ 0x21b7a4
// size: 212 bytes
//

undefined4 Set_PMFSA_Q_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  uVar2 = HcGetMaxStaNum(param_1);
  uVar1 = uVar1 & 0xffff;
  if ((uVar1 < uVar2) && (*(char *)(uVar1 * 0x14c0 + param_1 + 0xa2282) == '\x01')) {
    if (*(char *)(param_1 + uVar1 * 0x620 + 0x2f762) == '\x01') {
      if (-1 < DebugLevel) {
        printk("%s: PMF CONNECTION BUT RECV WEP=0 ACTION, ACTIVE THE SA QUERY\n","Set_PMFSA_Q_Proc")
        ;
      }
      PMF_MlmeSAQueryReq(param_1,uVar1 * 0x14c0 + param_1 + 0xa1d20);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: PMF Connection IGNORE THIS PKT DUE TO NOT IN PORTSECURED\n","Set_PMFSA_Q_Proc");
      return 0;
    }
  }
  return 0;
}

