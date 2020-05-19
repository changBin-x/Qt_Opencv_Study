/*
 * @Date: 2020-05-19 13:26:23
 * @LastEditTime: 2020-05-19 13:57:13
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
 */
#include <stdio.h>
#include <stdlib.h>

#include "build/config.h"

// 让其根据 USE_MYMATH 的预定义值来决定是否调用标准库还是 MathFunctions 库
#ifdef USE_MYMATH
#include "math/matFunctions.h"
#else
#include <math.h>
#endif

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s base exponent \n", argv[0]);
    return 1;
  }

  double base = atof(argv[1]);
  int exponent = atoi(argv[2]);

#ifdef USE_MYMATH
  printf("Now we use our own Math library. \n");
  double result = power(base, exponent);
#else
  printf("Now we use the standard library. \n");
  double result = pow(base, exponent);
#endif

  printf("%g ^ %d is %g\n", base, exponent, result);
  return 0;
}