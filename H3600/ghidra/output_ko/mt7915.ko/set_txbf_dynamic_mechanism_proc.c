// module: mt7915.ko
// function: set_txbf_dynamic_mechanism_proc @ 0xe5a54
// size: 132 bytes
//

undefined4 set_txbf_dynamic_mechanism_proc(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*param_2 == '\0') {
    if (0 < DebugLevel) {
      printk("bfdm Usage:\niwpriv ra0 set bfdm=On_Off_Bit_Map\nBit0: Dynamic BFee Adaption\n");
    }
  }
  else {
    uVar2 = simple_strtol(param_2,0,10);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0xa789d0) = uVar2;
    if (0 < iVar1) {
      printk("bfdm_bitmap=%d\n",uVar2);
    }
  }
  return 1;
}

