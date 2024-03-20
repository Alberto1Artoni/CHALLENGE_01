#ifndef MUPARSER_FUN_HPP
#define MUPARSER_FUN_HPP

#include <iostream>
#include <muParser.h>
#include <vector>

class MuparserFun {
    
public:
    MuparserFun(const std::string &expression, const std::vector<std::string> &variableNames) {
        try {
            m_expression=expression;
            m_parser.SetExpr(expression);
            m_vars.resize(variableNames.size());
            for (size_t i = 0; i < variableNames.size(); ++i) {
                m_parser.DefineVar(variableNames[i], &m_vars[i]);
            }
        } catch (mu::Parser::exception_type &e) {
            std::cerr << e.GetMsg() << std::endl;
        }
    }

    double operator()(const std::vector<double> &values) {
        if (values.size() != m_vars.size()) {
            std::cerr << "Number of variables doesn't match the number of requested variables" << std::endl;
            return std::numeric_limits<double>::quiet_NaN();
        }

        for (size_t i = 0; i < values.size(); ++i) {
            m_vars[i] = values[i];
        }

        return m_parser.Eval();
    }

  std::string getExpression() const {
        return m_expression;
    }
private:
    std::vector<double> m_vars;
    mu::Parser m_parser;
    std::string m_expression;
};

#endif