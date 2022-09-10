#include <gtest/gtest.h>

#include "model.h"

TEST(RPN_OUTPUT, ORIGIN) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("3+4*2/(1-5)^2^3");
  equal = 3 + 4 * 2 / pow((1 - 5), pow(2, 3));
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_1, ORIGIN_1) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("(4+5)*9-(3/2+1)");
  equal = (4 + 5) * 9 - ((3.0 / 2.0) + 1);
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_2, ORIGIN_2) {
  std::pair<bool, double> res;
  double equal = 3 - 7 + 3;
  Model model;
  res = model.Test("3-7+3");
  EXPECT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_3, ORIGIN_3) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("28.5+3*(1-5)*(3+4)");
  equal = 28.5 + 3 * (1 - 5) * (3 + 4);
  EXPECT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_4, ORIGIN_4) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("3^s(1)");
  equal = pow(3, sin(1));
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_5, ORIGIN_5) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("s(c(2^1)*3)+3");
  equal = sin(cos(pow(2, 1)) * 3) + 3;
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_6, ORIGIN_6) {
  std::pair<bool, double> res;
  Model model;
  double equal;
  res = model.Test("4m3+z(0.1)*2-(12.158*9)");
  equal = fmod(4.0, 3.0) + acos(0.1) * 2.0 - (12.158 * (9.0));
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_7, ORIGIN_7) {
  std::pair<bool, double> res;
  Model model;
  double equal;
  res = model.Test("-3+5");
  equal = -3 + 5;
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_8, ORIGIN_8) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("-8--13-9++9-v(81)");
  equal = -8 - (-13) - 9 + (+9) - sqrt(81);
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_9, ORIGIN_9) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("3+x-4", 10);
  equal = 3 + 10 - 4;
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_10, ORIGIN_10) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("3+3.e2");
  equal = 3 + 3.e2;
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_11, ORIGIN_11) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("-10+5-3.e-3-23");
  equal = -10 + 5 - 3.e-3 - 23;
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_12, ORIGIN_12) {
  std::pair<bool, double> res;
  bool equal = false;
  Model model;
  res = model.Test("-3.14c+3");
  EXPECT_EQ(res.first, equal);
}

TEST(RPN_OUTPUT_13, ORIGIN_13) {
  std::pair<bool, double> res;
  bool equal = false;
  Model model;
  res = model.Test("-3+5((3)");
  EXPECT_EQ(res.first, equal);
}

TEST(RPN_OUTPUT_14, ORIGIN_14) {
  std::pair<bool, double> res;
  Model model;
  double equal;
  res = model.Test("-3+-5");
  equal = -3 + -5;
  EXPECT_FLOAT_EQ(res.second, equal);
}

TEST(RPN_OUTPUT_15, ORIGIN_15) {
  std::pair<bool, double> res;
  bool equal = false;
  Model model;
  res = model.Test("6.e-1.23-5");
  EXPECT_EQ(res.first, equal);
}

TEST(RPN_OUTPUT_16, ORIGIN_16) {
  std::pair<bool, double> res;
  bool equal = false;
  Model model;
  res = model.Test("6.em34+1");
  EXPECT_EQ(res.first, equal);
}

TEST(RPN_OUTPUT_17, ORIGIN_17) {
  std::pair<bool, double> res;
  bool equal = true;
  Model model;
  res = model.Test("6.e-3");
  EXPECT_EQ(res.first, equal);
}

TEST(RPN_OUTPUT_18, ORIGIN_18) {
  std::pair<bool, double> res;
  bool equal = true;
  Model model;
  res = model.Test("6.e-3+5.e6");
  EXPECT_EQ(res.first, equal);
}

TEST(RPN_OUTPUT_19, ORIGIN_19) {
  std::pair<bool, double> res;
  double equal;
  Model model;
  res = model.Test("t(3)+w(0.5)-d(4)+l(20)*e(5)");
  equal = tan(3) + asin(0.5) - log(4) + log10(20) * atan(5);
  EXPECT_FLOAT_EQ(res.second, equal);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
