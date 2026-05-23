// module: mt7915.ko
// function: ecc_point_dump_time @ 0x218dc8
// size: 996 bytes
//

void ecc_point_dump_time(void)

{
  undefined4 uVar1;
  undefined4 in_r3;
  
  if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
    printk("ecc_point time record:\n");
  }
  if (ec_op_ti_rec._8_4_ != 0) {
    if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
      printk("add_op time record:\n");
      if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
        printk("\tavg_time=%lu jiffies",ec_op_ti_rec._0_4_,ECC_COST_TIME_DBG_LVL,DebugLevel,in_r3);
        if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
          uVar1 = jiffies_to_msecs(ec_op_ti_rec._0_4_);
          printk(", %u msec",uVar1);
          if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
            printk("\n\texe_times=%u\n",ec_op_ti_rec._8_4_);
          }
        }
      }
    }
    ec_op_ti_rec._0_4_ = 0;
    ec_op_ti_rec._4_4_ = 0;
    ec_op_ti_rec._8_4_ = 0;
  }
  if (ec_op_ti_rec._20_4_ != 0) {
    if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
      printk("dbl_op time record:\n");
      if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
        printk("\tavg_time=%lu jiffies",ec_op_ti_rec._12_4_,ECC_COST_TIME_DBG_LVL,DebugLevel,in_r3);
        if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
          uVar1 = jiffies_to_msecs(ec_op_ti_rec._12_4_);
          printk(", %u msec",uVar1);
          if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
            printk("\n\texe_times=%u\n",ec_op_ti_rec._20_4_);
          }
        }
      }
    }
    ec_op_ti_rec._12_4_ = 0;
    ec_op_ti_rec._16_4_ = 0;
    ec_op_ti_rec._20_4_ = 0;
  }
  if (ec_op_ti_rec._32_4_ != 0) {
    if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
      printk("mul_op time record:\n");
      if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
        printk("\tavg_time=%lu jiffies",ec_op_ti_rec._24_4_,ECC_COST_TIME_DBG_LVL,DebugLevel,in_r3);
        if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
          uVar1 = jiffies_to_msecs(ec_op_ti_rec._24_4_);
          printk(", %u msec",uVar1);
          if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
            printk("\n\texe_times=%u\n",ec_op_ti_rec._32_4_);
          }
        }
      }
    }
    ec_op_ti_rec._24_4_ = 0;
    ec_op_ti_rec._28_4_ = 0;
    ec_op_ti_rec._32_4_ = 0;
  }
  if (ec_op_ti_rec._44_4_ != 0) {
    if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
      printk("find_y_op time record:\n");
      if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
        printk("\tavg_time=%lu jiffies",ec_op_ti_rec._36_4_);
        if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
          uVar1 = jiffies_to_msecs(ec_op_ti_rec._36_4_);
          printk(", %u msec",uVar1);
          if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
            printk("\n\texe_times=%u\n",ec_op_ti_rec._44_4_);
          }
        }
      }
    }
    ec_op_ti_rec._36_4_ = 0;
    ec_op_ti_rec._40_4_ = 0;
    ec_op_ti_rec._44_4_ = 0;
  }
  if (ec_op_ti_rec._56_4_ == 0) {
    return;
  }
  if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
    printk("on_curve_check_op time record:\n");
    if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
      printk("\tavg_time=%lu jiffies",ec_op_ti_rec._48_4_);
      if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
        uVar1 = jiffies_to_msecs(ec_op_ti_rec._48_4_);
        printk(", %u msec",uVar1);
        if (ECC_COST_TIME_DBG_LVL <= DebugLevel) {
          printk("\n\texe_times=%u\n",ec_op_ti_rec._56_4_);
        }
      }
    }
  }
  ec_op_ti_rec._48_4_ = 0;
  ec_op_ti_rec._52_4_ = 0;
  ec_op_ti_rec._56_4_ = 0;
  return;
}

