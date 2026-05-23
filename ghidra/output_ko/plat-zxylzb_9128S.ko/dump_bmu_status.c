// module: plat-zxylzb_9128S.ko
// function: dump_bmu_status @ 0x18fa4
// size: 176 bytes
//

void dump_bmu_status(void)

{
  printk("sw alloc cnt \t: 0x%x\n",bmu_status._8_4_);
  printk("hw alloc cnt \t: 0x%x\n",bmu_status._20_4_);
  printk("alloc repeat    : 0x%x\n",bmu_status._32_4_);
  printk("sw free cnt     : 0x%x\n",bmu_status._12_4_);
  printk("hw free cnt     : 0x%x\n",bmu_status._24_4_);
  printk("free repeat   \t: 0x%x\n",bmu_status._28_4_);
  printk("alloc_bp_fail \t: 0x%x\n",bmu_status._0_4_);
  printk("free_bp_fail \t: 0x%x\n",bmu_status._4_4_);
  printk("timeout alloc   : 0x%x\n",bmu_status._36_4_);
  printk("sw free jumbo_c : 0x%x\n",bmu_status._16_4_);
  return;
}

