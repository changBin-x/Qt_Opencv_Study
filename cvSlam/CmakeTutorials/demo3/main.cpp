/*
 * @Date: 2020-05-19 10:51:40
 * @LastEditTime: 2020-05-19 13:20:30
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
 */
#include <stdio.h>
#include <stdlib.h>

#include "math/mathFunctions.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s base exponent \n", argv[0]);
    return 1;
  }
  double base = atof(argv[1]);
  int exponent = atoi(argv[2]);
  double result = power(base, exponent);
  printf("%g ^ %d is %g\n", base, exponent, result);
  return 0;
}
