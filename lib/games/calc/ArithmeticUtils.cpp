#include "ArithmeticUtils.hpp"
#include <stdexcept>

namespace arithmetic_utils {

    int performOperation(int leftOperand, char operation, int rightOperand) {
        switch (operation) {
            case '+': return leftOperand + rightOperand;
            case '-': return leftOperand - rightOperand;
            case '*': return leftOperand * rightOperand;
            case '/':
                if (rightOperand == 0) {
                    throw std::runtime_error("Division durch Null");
                }
                return leftOperand / rightOperand;
            case '%':
                if (rightOperand == 0) {
                    throw std::runtime_error("Modulo durch Null");
                }
                return leftOperand % rightOperand;
            default: throw std::invalid_argument("Ungültiger Operator");
        }
    }

}
