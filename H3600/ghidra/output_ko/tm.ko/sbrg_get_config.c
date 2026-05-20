// module: tm.ko
// function: sbrg_get_config @ 0x22950
// size: 440 bytes
//

undefined4 sbrg_get_config(void)

{
  undefined **ppuVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  undefined *local_20 [3];
  
  local_20[0] = &_LC0;
  local_20[1] = &_LC1;
  iVar4 = 0;
  uVar3 = fpga_read_reg(0xe2070);
  uVar2 = fpga_read_reg(0xe20b0);
  printk("source address look enable<0:dis,1:en> :0x%x\n",uVar3 & 0xff);
  printk("source address look fail<0:pass,1:drop>:0x%x\n",(uVar3 << 0x10) >> 0x18);
  printk("destin address look enable<0:dis,1:en> :0x%x\n",uVar2);
  uVar3 = fpga_read_reg(0xe20d0);
  uVar2 = fpga_read_reg(0xe20d1);
  printk(&_LC669);
  printk("unicast look    table enable<0:dis,1:en>          :0x%x\n",uVar3 & 0xff);
  printk("unknown unicast ctrl<0:dorp,1:flood,2:copy,3:trap>:0x%x\n",(uVar3 << 9) >> 0x11);
  printk("unknown unicast fwd<0:drop,1:fwd>                 :0x%x\n",uVar3 >> 0x18);
  printk("unknown unicast from pon flood port<0:drop,1:fwd> :0x%x\n",uVar2);
  uVar3 = fpga_read_reg(0xe20c0);
  uVar2 = fpga_read_reg(0xe20c1);
  printk(&_LC669);
  printk("unknown broadcast ctrl<0:drop,1:fwd>       :0x%x\n",uVar3 & 0xff);
  printk("unknown broadcast fwd<0:drop,1:fwd>        :0x%x\n",(uVar3 << 0x10) >> 0x18);
  printk("broadcast from pon flood port<0:drop,1:fwd>:0x%x\n",uVar2);
  uVar3 = fpga_read_reg(0xe20b5);
  printk(&_LC669);
  printk("multicast look table enable<0:dis,1:en>:0x%x\n",uVar3 & 0xff);
  printk("unknown multicast ctrl<0:drop,1:fwd>   :0x%x\n",(uVar3 << 0x10) >> 0x18);
  printk("unknown multicast fwd<0:drop,1:fwd>    :0x%x\n",(uVar3 << 8) >> 0x18);
  do {
    uVar2 = fpga_read_reg(&DAT_000c40b6 + iVar4);
    ppuVar1 = local_20 + iVar4;
    iVar4 = iVar4 + 1;
    printk("unknown multicast from %s flood port<0:drop,1:fwd>:0x%x\n",*ppuVar1,uVar2);
  } while (iVar4 != 7);
  return 0;
}

