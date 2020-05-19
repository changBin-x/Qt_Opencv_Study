/*
 * @Date: 2020-05-19 10:51:56
 * @LastEditTime: 2020-05-19 10:57:07
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
 */
/**
 * power - Calculate the power of number.
 * @param base: Base value.
 * @param exponent: Exponent value.
 *
 * @return base raised to the power exponent.
 */
double power(double base, int exponent) {
  int result = base;
  int i;

  if (exponent == 0) {
    return 1;
  }

  for (i = 1; i < exponent; ++i) {
    result = result * base;
  }

  return result;
}