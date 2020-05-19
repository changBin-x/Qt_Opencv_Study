/*
 * @Date: 2020-05-19 13:27:20
 * @LastEditTime: 2020-05-19 13:28:51
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
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