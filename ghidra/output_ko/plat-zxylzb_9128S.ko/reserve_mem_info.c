// module: plat-zxylzb_9128S.ko
// function: reserve_mem_info @ 0x1b30c
// size: 776 bytes
//

void reserve_mem_info(void)

{
  undefined4 in_r3;
  
  printk("ZX_PA_BUF_BASE0=%x\n",pdt_mem_size + 0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_BUF_BASE0=%x\n",pdt_mem_size + -0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_ACL_BASE=%x\n",pdt_mem_size + 0x40020000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_ACL_BASE=%x\n",pdt_mem_size + -0x3ffe0000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_FLOW_BASE=%x\n",pdt_mem_size + 0x40420000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_FLOW_BASE=%x\n",pdt_mem_size + -0x3fbe0000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_BP_BUFFER_BASE=%x\n",pdt_mem_size + 0x40520000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x40520000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_TX_UP_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405e0000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_TX_DN_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405f0000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_BPPE_BASE=%x\n",pdt_mem_size + -0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_BP_BUF_BASE=%x\n",pdt_mem_size + -0x3fae0000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fae0000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_TX_UP_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fa20000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_TX_DN_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fa10000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("BPPE_POOL_SIZE=%x\n",u32_BPPE_POOL_SIZE);
  printk("NORMAL_BP_BUFFER_SIZE=%x\n",u32_BP_SIZE * u32_BPPE_POOL_SIZE);
  printk("JUMBO_BP_SIZE=%x\n",u32_JUMBO_BP_SIZE);
  printk("JUMBO_BPPE_POOL_SIZE=%x\n",u32_JUMBO_BPPE_POOL_SIZE);
  printk("BP_BUFFER_SIZE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE + u32_BP_SIZE * u32_BPPE_POOL_SIZE,
         u32_JUMBO_BPPE_POOL_SIZE,in_r3);
  return;
}

