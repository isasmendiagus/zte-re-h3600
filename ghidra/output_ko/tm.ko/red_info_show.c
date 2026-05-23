// module: tm.ko
// function: red_info_show @ 0x76dec
// size: 1508 bytes
//

undefined4 red_info_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 uVar7;
  
  pcVar6 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    uVar7 = 0xffffffff;
  }
  else {
    iVar1 = strcmp(pcVar6,"helpRed");
    if (iVar1 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands[HEX]\n");
      printk("============================================================================\n");
      printk(
            " echo [direction] [port/tcont_llid] > bufUsed  - List buffer space used by port or tcont_llid\n"
            );
      printk(
            " echo [direction] [port/tcont_llid] > bufCfg   - List buffer space cfg  by port or tcont_llid \n"
            );
      printk(" echo [queid] [guartsize][maxsize] > sredoutquecfg  - Set outside buffer space cfg\n")
      ;
      printk(" echo [queid] [guartsize][maxsize] > sredinquecfg   - Set inside buffer space cfg \n")
      ;
      printk("============================================================================\n");
      printk("Display Commands: cat <file>\n");
      printk("============================================================================\n");
      printk(" cat dbgInfo            - dump printing options\n");
      printk(" cat desOut             - show descrip out info\n");
      printk(" cat desDrop            - show descrip drop info\n");
      return 0;
    }
    iVar1 = strcmp(pcVar6,"dbgInfo");
    if (iVar1 == 0) {
      printk("---------------------------------------------\n");
      printk(" red debug info:\n");
      printk("---------------------------------------------\n");
      uVar2 = fpga_read_reg(0xd1033);
      printk("qmg2red watermark up high fwd drop cnt :%-10d\n",uVar2 & 0xff);
      printk("qmg2red watermark dn high fwd drop cnt :%-10d\n",(uVar2 << 0x10) >> 0x18);
      uVar2 = fpga_read_reg(0xd1034);
      printk("out all share space:%-10d\n",uVar2 & 0x7fff);
      uVar2 = fpga_read_reg(0xd1036);
      printk("in all share space:%-10d\n",uVar2 & 0x3fff);
      uVar2 = fpga_read_reg(0xd1037);
      printk("in act que num:%-10d\n",(uVar2 << 7) >> 0x17);
      printk("out act que num:%-10d\n",uVar2 & 0x1ff);
      uVar2 = fpga_read_reg(0xd1051);
      printk("cpu tx omci cnt:%-10d\n",uVar2 >> 0x10);
      uVar2 = fpga_read_reg(0xd1052);
      printk("cpu rx omci cnt:%-10d\n",uVar2 >> 0x10);
      return 0;
    }
    iVar1 = strcmp(pcVar6,"desOut");
    if (iVar1 == 0) {
      uVar2 = fpga_read_reg(0xd1040);
      uVar3 = fpga_read_reg(0xd1041);
      uVar4 = fpga_read_reg(0xd1042);
      uVar5 = fpga_read_reg(0xd1043);
      printk("---------------------------------------------\n");
      printk("(red2qmg) des info:\n");
      printk("---------------------------------------------\n");
      printk("Rele offset(119-126)             :0x%x\n",(uVar5 << 1) >> 0x18);
      printk("Rele Pmau(106-118)               :0x%x\n",(uVar5 << 9) >> 0x13);
      printk("action(104-105)                  :0x%x\n",(uVar5 << 0x16) >> 0x1e);
      printk("move flag(103)                   :0x%x\n",(uVar5 << 0x18) >> 0x1f);
      printk("Offset(96-102)                   :%d\n",uVar5 & 0x7f);
      printk("pri(93-95)                       :%d\n",uVar4 >> 0x1d);
      printk("sec_flag(92)                     :0x%x\n",(uVar4 << 3) >> 0x1f);
      printk("CPU_flag(91)                     :0x%x\n",(uVar4 << 4) >> 0x1f);
      printk("pack in ddr(90)                  :0x%x\n",(uVar4 << 5) >> 0x1f);
      printk("Pkt Len(76-89)                   :%d\n",(uVar4 << 6) >> 0x12);
      printk("Hpmau/BP(60-75)                  :%d\n",(uVar4 & 0xfff) << 4 | uVar3 >> 0x1c);
      printk("Desc Flag(59)                    :0x%x\n",(uVar3 << 4) >> 0x1f);
      printk("inport(54-58)                    :%d\n",(uVar3 << 5) >> 0x1b);
      printk("OMCI Flag(53)                    :0x%x\n",(uVar3 << 10) >> 0x1f);
      printk("bp_type(52)                      :0x%x\n",(uVar3 << 0xb) >> 0x1f);
      printk("Buffer Type(51)                  :0x%x\n",(uVar3 << 0xc) >> 0x1f);
      printk("gemport id(35-50)                :%d\n",(uVar3 << 0xd) >> 0x10);
      printk("Cast Type(33-34)                 :0x%x\n",(uVar3 << 0x1d) >> 0x1e);
      uVar3 = uVar2 >> 0x1e | (uVar3 & 1) << 2;
      pcVar6 = "Queue ID(30-32)                  :%d\n";
    }
    else {
      iVar1 = strcmp(pcVar6,"desDrop");
      if (iVar1 != 0) {
        printk("%s: illegal operation <%s>\n","red_info_show",*param_2);
        return 0;
      }
      uVar2 = fpga_read_reg(0xd1044);
      uVar3 = fpga_read_reg(0xd1045);
      uVar4 = fpga_read_reg(0xd1046);
      uVar5 = fpga_read_reg(0xd1047);
      printk("---------------------------------------------\n");
      printk("(red2opc) des info:\n");
      printk("---------------------------------------------\n");
      printk("Pkt Len old(106-119)             :%d\n",(uVar5 << 8) >> 0x12);
      printk("action(104-105)                  :0x%x\n",(uVar5 << 0x16) >> 0x1e);
      printk("move flag(103)                   :0x%x\n",(uVar5 << 0x18) >> 0x1f);
      printk("Offset(96-102)                   :%d\n",uVar5 & 0x7f);
      printk("pri(93-95)                       :%d\n",uVar4 >> 0x1d);
      printk("sec_flag(92)                     :0x%x\n",(uVar4 << 3) >> 0x1f);
      printk("CPU_flag(91)                     :0x%x\n",(uVar4 << 4) >> 0x1f);
      printk("Pkt Len(76-89)                   :%d\n",(uVar4 << 6) >> 0x12);
      printk("Hpmau/BP(60-75)                  :%d\n",(uVar4 & 0xfff) << 4 | uVar3 >> 0x1c);
      printk("Desc Flag(59)                    :0x%x\n",(uVar3 << 4) >> 0x1f);
      printk("inport(54-58)                    :%d\n",(uVar3 << 5) >> 0x1b);
      printk("OMCI Flag(53)                    :0x%x\n",(uVar3 << 10) >> 0x1f);
      printk("bp_type(52)                      :0x%x\n",(uVar3 << 0xb) >> 0x1f);
      printk("Buffer Type(51)                  :0x%x\n",(uVar3 << 0xc) >> 0x1f);
      printk("gemport id(35-50)                :%d\n",(uVar3 << 0xd) >> 0x10);
      printk("Cast Type(33-34)                 :0x%x\n",(uVar3 << 0x1d) >> 0x1e);
      uVar3 = uVar2 >> 0x1e | (uVar3 & 1) << 2;
      pcVar6 = "Drop Reason(30-32)               :%d\n";
    }
    uVar7 = 1;
    printk(pcVar6,uVar3);
    printk("Outport/Tcont(24-29)             :%d\n",(uVar2 << 2) >> 0x1a);
    printk("CPU Queue ID/E8 Queue ID(21-23)  :%d\n",(uVar2 << 8) >> 0x1d);
    printk("SVID(9-20)                       :%d\n",(uVar2 << 0xb) >> 0x14);
    printk("color(8)(1:g 0:y)                :0x%x\n",(uVar2 << 0x17) >> 0x1f);
    uVar3 = (uVar2 << 0x18) >> 0x19;
    printk("Action Reason(1-7)               :0x%02x:%s\n",uVar3,(&trapPktType)[uVar3]);
    printk("E8_en(0)                         :0x%x\n",uVar2 & 1);
  }
  return uVar7;
}

