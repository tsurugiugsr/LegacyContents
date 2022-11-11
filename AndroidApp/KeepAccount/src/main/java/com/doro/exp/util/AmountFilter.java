package com.doro.exp.util;


import android.text.InputFilter;
import android.text.Spanned;
import android.text.TextUtils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class AmountFilter implements InputFilter {

    /**
     * 整数部分的最大位数
     */
    public static final int integer_Digits = 7;

    /**
     * 小数部分的最大位数
     */
    public static final int decimal_Digits = 2;

    private static final String POINTER = ".";

    Pattern p;

    public AmountFilter() {
        // 用于匹配输入的是0-9和.这几个数字和字符
        p = Pattern.compile("([0-9]|\\.)*");
    }

    /**
     * source    新输入的字符串
     * start    新输入的字符串起始下标，一般为0
     * end    新输入的字符串终点下标，一般为source长度-1
     * dest    输入之前文本框内容
     * dstart    原内容起始坐标，一般为0
     * dend    原内容终点坐标，一般为dest长度-1
     */

    @Override
    public CharSequence filter(CharSequence source, int start, int end,
                               Spanned dest, int dstart, int dend) {

        String sourceText = source.toString();
        String destText = dest.toString();

        if (TextUtils.isEmpty(sourceText)) {
            if (dstart == 0 && destText.indexOf(POINTER) == 1) {    // 保证小数点不在第一个位置
                return "0";
            }
            return "";
        }

        Matcher matcher = p.matcher(source);
        // 已经输入小数点的情况下，只能输入数字
        // （1）不能再输入小数点
        // （2）限制小数点后只能输入2位
        if (destText.contains(POINTER)) {
            if (!matcher.matches()) {
                return "";
            } else {
                if (POINTER.contentEquals(source)) { //只能输入一个小数点
                    return "";
                }
            }
            // 验证小数点精度，保证小数点后只能输入2位
            int index = destText.indexOf(POINTER);
            int length = destText.trim().length() - index;
            if (length > decimal_Digits && dstart > index) {
                return "";
            }
        } else {
            // 没有输入小数点的情况下，能输入小数点和数字
            // （1）首位输入0，相当于没输入，还显示hintText
            // （2）首位输入小数点，自动补正为”0.“
            // （3）限制整数部分只能输入至多7位，下一位只能输入小数点
            if (!matcher.matches()) {
                return "";
            } else {
                if (dstart == 0) {    // 检验首位
                    if ((POINTER.contentEquals(source))) {  // 第一个位置输入小数点的情况
                        return "0.";
                    } else if ("0".contentEquals(source)) { // 第一个位置输入0的情况
                        return "";
                    }
                } else if (dend == integer_Digits) {    // 保证整数只能输入7位
                    if((POINTER.contentEquals(source))){
                        return POINTER;
                    }else {
                        return "";
                    }
                }
            }
        }

        return dest.subSequence(dstart, dend) + sourceText;
    }
}