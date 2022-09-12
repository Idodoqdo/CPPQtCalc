#include "model.h"

void Model::GoToRPN() {
  std::stack<char> operator_stack;
  for (std::string::const_iterator i = expression.begin(); i < expression.end();
       ++i) {
    if (isdigit(*i) || *i == '.') {
      SeparateNum(i);
    } else if (*i == 'x') {
      output.push_back(*i);
    } else if ((*i == '(' || priority[*i] == 0) && *i != ')') {
      operator_stack.push(*i);
    } else if (*i != '(' && *i != ')') {
      while (!operator_stack.empty() && operator_stack.top() != '(' &&
             priority[operator_stack.top()] >= priority[*i] &&
             priority[*i] < 3) {
        char temp = operator_stack.top();
        operator_stack.pop();
        output.push_back(temp);
      }
      operator_stack.push(*i);
    } else if (*i == ')') {
      while (operator_stack.top() != '(') {
        char temp = operator_stack.top();
        operator_stack.pop();
        output.push_back(temp);
      }
      operator_stack.pop();
    }
  }
  while (!operator_stack.empty()) {
    char temp = operator_stack.top();
    operator_stack.pop();
    output.push_back(temp);
  }
}

void Model::SeparateNum(std::string::const_iterator &it) {
  bool flag_e = false;
  while (isdigit(*it) || *it == '.' || *it == 'e' || (*it == '-' && flag_e)) {
    if (*it == 'e')
      flag_e = true;
    if (*it == '-')
      flag_e = false;
    output.push_back(*it);
    ++it;
  }
  --it;
  output.push_back(' ');
}

double Model::Calculate(double x) {
  GoToRPN();
  CalculateRPN(x);
  return calculated_value;
}

void Model::CalculateGraph(std::vector<double> &x, std::vector<double> &y,
                           double const &xBegin, double const &xEnd,
                           double const &yBegin, double const &yEnd,
                           double const &step) {
  GoToRPN();
  double x_coord = xBegin;
  while (1) {
    double y_coord = Calculate(x_coord);
    if (y_coord <= yEnd && y_coord >= yBegin) {
      x.push_back(x_coord);
      y.push_back(y_coord);
    }
    x_coord += step;
    if (x_coord >= xEnd)
      break;
  }
}

bool Model::IsOperator(char oper) {
  auto iter = priority.find(oper);
  return (iter != priority.end() && iter->second < 4);
}

void Model::CalculateRPN(double x) {
  std::stack<long double> stk;
  for (auto it = output.begin(); it != output.end(); ++it) {
    if (IsOperator(*it)) {
      IsBinaryOperation(stk, *it);
    } else if (isalpha(*it) && *it != 'x') {
      IsFunckAndUnaryOperation(stk, *it);
    } else if (*it == 'x') {
      stk.push(x);
    } else {
      stk.push(ScanNum(it));
    }
  }
  if (!stk.empty())
    calculated_value = stk.top();
}

void Model::IsBinaryOperation(std::stack<long double> &resstack,
                              char operation) {
  long double a, b;
  a = resstack.top();
  resstack.pop();
  b = resstack.top();
  resstack.pop();
  resstack.push(Operation(a, b, operation));
}

void Model::IsFunckAndUnaryOperation(std::stack<long double> &resstack,
                                     char operation) {
  long double a;
  a = resstack.top();
  resstack.pop();
  resstack.push(Operation(a, operation));
}

double Model::Operation(long double const &a, long double const &b,
                        char const oper) {
  long double res = 0;
  switch (oper) {
  case '+':
    res = b + a;
    break;
  case '-':
    res = b - a;
    break;
  case '*':
    res = b * a;
    break;
  case '/':
    res = b / a;
    break;
  case '^':
    res = powf(b, a);
    break;
  case 'm':
    res = fmod(b, a);
    break;
  default:
    res = 0;
    break;
  }
  return res;
}

double Model::Operation(long double const &a, char const oper) {
  long double res = 0;
  switch (oper) {
  case 's':
    res = sin(a);
    break;
  case 'c':
    res = cos(a);
    break;
  case 't':
    res = tan(a);
    break;
  case 'z':
    res = acos(a);
    break;
  case 'w':
    res = asin(a);
    break;
  case 'v':
    res = sqrt(a);
    break;
  case 'd':
    res = log(a);
    break;
  case 'l':
    res = log10(a);
    break;
  case 'e':
    res = atan(a);
    break;
  case 'u':
    res = -a;
    break;
  case 'p':
    res = a;
    break;
  }
  return res;
}

double Model::ScanNum(std::list<char>::iterator &it) {
  std::string res = "";
  while (*it != ' ') {
    res += *it;
    ++it;
  }
  return std::stod(res);
}

bool Model::Valid() {
  std::set<char> check_kit = {'^', '+', '-', '*', '/'};
  may_unary = true;
  bool flag_valid = true;
  bool flag_point = false;
  int bal = 0;
  if (!ValidFirstAndLastSim())
    return false;
  for (auto i = expression.begin(); i != expression.end() - 1; ++i) {
    if (may_unary && *i == '+') {
      *i = 'p';
    } else if (may_unary && *i == '-') {
      *i = 'u';
    }
    may_unary = false;
    if (check_kit.find(*i) != check_kit.end() || *i == '(' || *i == 'p' ||
        *i == 'u')
      may_unary = true;
    if (*i == '(' && *std::next(i) == ')') {
      flag_valid = false;
      break;
    }
    if (*i == '(')
      bal++;
    else if (*i == ')')
      bal--;
    if (bal < 0) {
      flag_valid = false;
      break;
    }
    if (!ValidAfterDigit(i)) {
      flag_valid = false;
      break;
    }
    if (*i == 'm' && !(isdigit(*std::next(i))) && *std::next(i) != '(') {
      flag_valid = false;
      break;
    }
    if ((flag_point &&
         ((!isdigit(*i) && *i != 'x' && *i != 'e') || *i == '.') &&
         check_kit.find(*i) == check_kit.end() && *i != ')')) {
      flag_valid = false;
      break;
    }
    if (*i == '.') {
      flag_point = true;
      if ((!isdigit(*std::next(i)) && *std::next(i) != 'x' &&
           *std::next(i) != 'e') ||
          (!isdigit(*std::prev(i)) && *std::prev(i) != 'x')) {
        flag_valid = false;
        break;
      }
    }
    if ((check_kit.find(*i) != check_kit.end() || *i == ')') && *i != '-') {
      flag_point = false;
    }
  }
  return flag_valid;
}

bool Model::ValidFirstAndLastSim() {
  bool flag = true;
  char last_symb = expression[expression.length() - 1];
  std::set<char> first_symbol = {'x', 'a', 'c', 's', '(', 'l', 't', '+',
                                 '-', 'z', 'w', 'v', 'd', 'e', 'm'};
  if ((!isdigit(expression[0]) &&
       first_symbol.find(expression[0]) == first_symbol.end()) ||
      (!isdigit(last_symb) && last_symb != 'x' && last_symb != ')'))
    flag = false;
  return flag;
}

bool Model::ValidAfterDigit(std::string::iterator it) {
  bool flag = true;
  std::set<char> check_elem = {'+', '-', '*', '/', '^', 'm', ')', '.'};
  if ((isdigit(*it) || (*it) == 'x') &&
      (check_elem.find(*std::next(it)) == check_elem.end()) &&
      !isdigit(*std::next(it)))
    flag = false;
  return flag;
}

void Model::AppendToLine(std::string added_string) {
  if (converter.find(added_string) == converter.end())
    expression.append(added_string);
  else
    expression += converter[added_string];
}

void Model::AC() {
  expression.clear();
  output.clear();
}

typename std::pair<bool, double> Model::Test(std::string const &input,
                                             double x) {
  expression = input;
  std::pair<bool, double> res;
  res.first = Valid();
  if (res.first)
    res.second = Calculate(x);
  return res;
}
