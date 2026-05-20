// module: mt7915.ko
// function: WfSysPreInit @ 0xb309c
// size: 88 bytes
//

undefined4 WfSysPreInit(int param_1)

{
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    mt7915_init();
  }
  wifi_sup_list_register(param_1,0);
  wifi_sup_list_register(param_1,1);
  wifi_sup_list_register(param_1,2);
  return 0;
}

