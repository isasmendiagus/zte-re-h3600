// module: mt7915.ko
// function: owe_pmkid_ecdh_process @ 0x21c8e4
// size: 232 bytes
//

undefined2
owe_pmkid_ecdh_process
          (int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined1 param_6,undefined4 param_7,undefined4 param_8,undefined1 param_9)

{
  undefined2 uVar1;
  void *__s1;
  int iVar2;
  int iVar3;
  
  __s1 = (void *)WPA_ExtractSuiteFromRSNIE(param_3,param_4,4,param_8);
  if (__s1 != (void *)0x0) {
    iVar2 = RTMPSearchPMKIDCache
                      (&DAT_003687fc + param_1,*(undefined1 *)(param_2 + 0xe4),param_2 + 0xec);
    if ((iVar2 != -1) &&
       (iVar3 = memcmp(__s1,(void *)(param_1 + iVar2 * 0x60 + 0x368803),0x10), iVar3 == 0)) {
      store_pmkid_cache_in_sec_config(param_1,param_2,iVar2);
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s: no OWE PMKID, do normal ECDH procedure\n","owe_pmkid_ecdh_process");
    }
  }
  uVar1 = process_ecdh_element(param_1,param_2,param_5,param_6,param_9);
  return uVar1;
}

