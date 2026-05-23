// module: mt7915.ko
// function: BigInteger_dump_time @ 0x1ff9f0
// size: 1896 bytes
//

void BigInteger_dump_time(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  if (DebugLevel < 3) {
    return;
  }
  printk("BigInteger time record: (allocated cnt = %lu)\n",alloc_cnt);
  printk("add allocated cnt = %lu\n",alloc_cnt_add);
  printk("sub allocated cnt = %lu\n",alloc_cnt_sub);
  printk("mul allocated cnt = %lu\n",alloc_cnt_mul);
  printk("div allocated cnt = %lu\n",alloc_cnt_div);
  printk("mod allocated cnt = %lu\n",alloc_cnt_mod);
  if (bi_op_ti_rec._20_4_ != 0) {
    printk("sub_op time record:\n");
    uVar1 = bi_op_ti_rec._20_4_;
    uVar2 = bi_op_ti_rec._16_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._16_4_,bi_op_ti_rec._20_4_);
    iVar4 = __aeabi_uidiv(uVar2 * 1000,uVar1);
    printk("\tavg_time=%lu.%03lu nsec",iVar3,iVar4 + iVar3 * -1000);
    printk(", %lu nsec",bi_op_ti_rec._16_4_);
    uVar1 = bi_op_ti_rec._16_4_;
    uVar2 = bi_op_ti_rec._4_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._16_4_,bi_op_ti_rec._4_4_);
    iVar4 = __aeabi_uidiv(uVar1 * 100,uVar2);
    printk(", add:sub = 1:%lu.%02lu",iVar3,iVar4 + iVar3 * -100);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._20_4_);
    bi_op_ti_rec._16_4_ = 0;
    bi_op_ti_rec._20_4_ = 0;
    bi_op_ti_rec._12_4_ = 0;
  }
  if (bi_op_ti_rec._32_4_ != 0) {
    printk("mul_op time record:\n");
    uVar1 = bi_op_ti_rec._32_4_;
    uVar2 = bi_op_ti_rec._28_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._28_4_,bi_op_ti_rec._32_4_);
    iVar4 = __aeabi_uidiv(uVar2 * 1000,uVar1);
    printk("\tavg_time=%lu.%03lu nsec",iVar3,iVar4 + iVar3 * -1000);
    printk(", %lu nsec",bi_op_ti_rec._28_4_);
    uVar1 = bi_op_ti_rec._28_4_;
    uVar2 = bi_op_ti_rec._4_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._28_4_,bi_op_ti_rec._4_4_);
    iVar4 = __aeabi_uidiv(uVar1 * 100,uVar2);
    printk(", add:mul = 1:%lu.%02lu",iVar3,iVar4 + iVar3 * -100);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._32_4_);
    bi_op_ti_rec._28_4_ = 0;
    bi_op_ti_rec._32_4_ = 0;
    bi_op_ti_rec._24_4_ = 0;
  }
  if (bi_op_ti_rec._44_4_ != 0) {
    printk("div_op time record:\n");
    uVar1 = bi_op_ti_rec._44_4_;
    uVar2 = bi_op_ti_rec._40_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._40_4_,bi_op_ti_rec._44_4_);
    iVar4 = __aeabi_uidiv(uVar2 * 1000,uVar1);
    printk("\tavg_time=%lu.%03lu nsec",iVar3,iVar4 + iVar3 * -1000);
    printk(", %lu nsec",bi_op_ti_rec._40_4_);
    uVar1 = bi_op_ti_rec._40_4_;
    uVar2 = bi_op_ti_rec._4_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._40_4_,bi_op_ti_rec._4_4_);
    iVar4 = __aeabi_uidiv(uVar1 * 100,uVar2);
    printk(", add:div = 1:%lu.%02lu",iVar3,iVar4 + iVar3 * -100);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._44_4_);
    bi_op_ti_rec._36_4_ = 0;
    bi_op_ti_rec._40_4_ = 0;
    bi_op_ti_rec._44_4_ = 0;
  }
  if (bi_op_ti_rec._56_4_ != 0) {
    printk("mod_op time record:\n");
    uVar1 = bi_op_ti_rec._56_4_;
    uVar2 = bi_op_ti_rec._52_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._52_4_,bi_op_ti_rec._56_4_);
    iVar4 = __aeabi_uidiv(uVar2 * 1000,uVar1);
    printk("\tavg_time=%lu.%03lu nsec",iVar3,iVar4 + iVar3 * -1000);
    printk(", %lu nsec",bi_op_ti_rec._52_4_);
    uVar1 = bi_op_ti_rec._52_4_;
    uVar2 = bi_op_ti_rec._4_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._52_4_,bi_op_ti_rec._4_4_);
    iVar4 = __aeabi_uidiv(uVar1 * 100,uVar2);
    printk(", add:mod = 1:%lu.%02lu",iVar3,iVar4 + iVar3 * -100);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._56_4_);
    bi_op_ti_rec._48_4_ = 0;
    bi_op_ti_rec._52_4_ = 0;
    bi_op_ti_rec._56_4_ = 0;
  }
  if (bi_op_ti_rec._8_4_ != 0) {
    printk("add_op time record:\n");
    uVar1 = bi_op_ti_rec._8_4_;
    uVar2 = bi_op_ti_rec._4_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._4_4_,bi_op_ti_rec._8_4_);
    iVar4 = __aeabi_uidiv(uVar2 * 1000,uVar1);
    printk("\tavg_time=%lu.%03lu nsec",iVar3,iVar4 + iVar3 * -1000);
    printk(", %lu nsec",bi_op_ti_rec._4_4_);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._8_4_);
    bi_op_ti_rec._4_4_ = 0;
    bi_op_ti_rec._8_4_ = 0;
    bi_op_ti_rec._0_4_ = 0;
  }
  if (bi_op_ti_rec._68_4_ != 0) {
    printk("square_op time record:\n");
    uVar1 = bi_op_ti_rec._68_4_;
    uVar2 = bi_op_ti_rec._64_4_;
    iVar3 = __aeabi_uidiv(bi_op_ti_rec._64_4_,bi_op_ti_rec._68_4_);
    iVar4 = __aeabi_uidiv(uVar2 * 1000,uVar1);
    printk("\tavg_time=%lu.%03lu nsec",iVar3,iVar4 + iVar3 * -1000);
    printk(", %lu nsec",bi_op_ti_rec._64_4_);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._68_4_);
    bi_op_ti_rec._60_4_ = 0;
    bi_op_ti_rec._64_4_ = 0;
    bi_op_ti_rec._68_4_ = 0;
  }
  alloc_cnt = 0;
  alloc_cnt_add = 0;
  alloc_cnt_sub = 0;
  alloc_cnt_mul = 0;
  alloc_cnt_div = 0;
  alloc_cnt_mod = 0;
  if (bi_op_ti_rec._80_4_ != 0) {
    printk("sqrt_op time record:\n");
    printk("\tavg_time=%lu jiffies",bi_op_ti_rec._72_4_);
    uVar2 = jiffies_to_msecs(bi_op_ti_rec._72_4_);
    printk(", %u msec",uVar2);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._80_4_);
    bi_op_ti_rec._72_4_ = 0;
    bi_op_ti_rec._76_4_ = 0;
    bi_op_ti_rec._80_4_ = 0;
  }
  if (bi_op_ti_rec._92_4_ != 0) {
    printk("exp_mod_op time record:\n");
    printk("\tavg_time=%lu jiffies",bi_op_ti_rec._84_4_);
    uVar2 = jiffies_to_msecs(bi_op_ti_rec._84_4_);
    printk(", %u msec",uVar2);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._92_4_);
    bi_op_ti_rec._84_4_ = 0;
    bi_op_ti_rec._88_4_ = 0;
    bi_op_ti_rec._92_4_ = 0;
  }
  if (bi_op_ti_rec._104_4_ != 0) {
    printk("div_mod_op time record:\n");
    printk("\tavg_time=%lu jiffies",bi_op_ti_rec._96_4_);
    uVar2 = jiffies_to_msecs(bi_op_ti_rec._96_4_);
    printk(", %u msec",uVar2);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._104_4_);
    bi_op_ti_rec._96_4_ = 0;
    bi_op_ti_rec._100_4_ = 0;
    bi_op_ti_rec._104_4_ = 0;
  }
  if (bi_op_ti_rec._116_4_ != 0) {
    printk("sqrt_mod_op time record:\n");
    printk("\tavg_time=%lu jiffies",bi_op_ti_rec._108_4_);
    uVar2 = jiffies_to_msecs(bi_op_ti_rec._108_4_);
    printk(", %u msec",uVar2);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._116_4_);
    bi_op_ti_rec._108_4_ = 0;
    bi_op_ti_rec._112_4_ = 0;
    bi_op_ti_rec._116_4_ = 0;
  }
  if (bi_op_ti_rec._128_4_ != 0) {
    printk("mod_mul_inv_op time record:\n");
    printk("\tavg_time=%lu jiffies",bi_op_ti_rec._120_4_);
    uVar2 = jiffies_to_msecs(bi_op_ti_rec._120_4_);
    printk(", %u msec",uVar2);
    printk("\n\texe_times=%u\n",bi_op_ti_rec._128_4_);
    bi_op_ti_rec._120_4_ = 0;
    bi_op_ti_rec._124_4_ = 0;
    bi_op_ti_rec._128_4_ = 0;
  }
  if (bi_op_ti_rec._140_4_ == 0) {
    return;
  }
  printk("simple_exp_mod_op time record:\n");
  printk("\tavg_time=%lu jiffies",bi_op_ti_rec._132_4_);
  uVar2 = jiffies_to_msecs(bi_op_ti_rec._132_4_);
  printk(", %u msec",uVar2);
  printk("\n\texe_times=%u\n",bi_op_ti_rec._140_4_);
  bi_op_ti_rec._132_4_ = 0;
  bi_op_ti_rec._136_4_ = 0;
  bi_op_ti_rec._140_4_ = 0;
  return;
}

