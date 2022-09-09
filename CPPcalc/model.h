#ifndef MODEL_H
#define MODEL_H
#include <math.h>

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <vector>

class Model {
  std::list<char> output;
  std::map<char, int> priority = {
      {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'m', 2}, {'^', 3},
      {'s', 4}, {'c', 4}, {'t', 4}, {'z', 4}, {'w', 4}, {'v', 4},
      {'d', 4}, {'l', 4}, {'e', 4}, {'u', 5}, {'p', 5}};
  std::map<std::string, char> converter = {
      {"sin", 's'},  {"cos", 'c'}, {"tan", 't'}, {"acos", 'z'}, {"asin", 'w'},
      {"sqrt", 'v'}, {"ln", 'v'},  {"log", 'd'}, {"atan", 'e'}, {"mod", 'm'}};
  std::string expression;
  void GoToRPN();
  void CalculateRPN(double x);
  bool IsOperator(char oper);
  double Operation(long double &a, long double &b, char oper);
  double Operation(long double &a, char oper);
  double ScanNum(std::list<char>::iterator &it);
  void SeparateNum(std::string::const_iterator &it);
  bool ValidFirstAndLastSim();
  bool ValidAfterDigit(std::string::iterator it);
  void IsBinaryOperation(std::stack<long double> &resstack, char operation);
  void IsFunckAndUnaryOperation(std::stack<long double> &resstack,
                                char operation);
  double calculated_value;
  bool may_unary;

 public:
  Model() : expression(""), calculated_value(4), may_unary(true){};
  double Calculate(double x);
  void CalculateGraph(std::vector<double> &x, std::vector<double> &y,
                      double &xBegin, double &xEnd, double &yBegin,
                      double &yEnd, double &step);
  void AppendToLine(std::string added_string);
  std::pair<bool, double> Test(std::string input, double x = 0);
  void AC();
  bool Valid();
};

#endif  // MODEL_H