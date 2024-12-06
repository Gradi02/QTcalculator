#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cctype>
#include <cmath>
#include <QStack>
#include <limits>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::EvaluateExpression(const QString& expression)
{
    QStack<QChar> operators; // Stack to hold operators
    QStack<double> operands; // Stack to hold operands

    int expression_length = expression.length();

    if(!CheckIfCorrect(expression_length))
        return std::numeric_limits<double>::quiet_NaN();

    for(int i=0; i<expression_length; i++)
    {
        QChar d = expression[i];

        if(d.isDigit() || (d == '-' && (i == 0 || expression[i - 1] == '(' || IsOperator(expression[i - 1]))))
        {
            bool isPoint = false;
            bool isNegative = (d == '-');
            if (isNegative)
            {
                i++;
            }

            int pointIndex = 0;
            double number = 0;
            while (i < expression_length && (expression[i].isDigit() || expression[i] == '.'))
            {
                d = expression[i];

                if(d.isDigit())
                {
                    number = number * 10 + d.digitValue();

                    if(isPoint)
                        pointIndex++;
                }
                else if (d == '.')
                {
                    if(!isPoint)
                        isPoint = true;
                    else
                        return std::numeric_limits<double>::quiet_NaN();
                }

                i++;
            }

            i--;

            // dodaje kropke do otrzymanej liczby
            for(int k=0; k<pointIndex; k++)
            {
                number/=10;
            }

            if (isNegative)
                number = -number;

            operands.push(number);
        }
        else if(IsOperator(d))
        {
            while (!operators.empty() &&
                   ((GetOperatorImportance(operators.top()) > GetOperatorImportance(d)) ||
                    (GetOperatorImportance(operators.top()) == GetOperatorImportance(d) && d != '^')))
            {
                if(operands.length()>1)
                {
                    double b = operands.top();
                    operands.pop();
                    double a = operands.top();
                    operands.pop();
                    QChar op = operators.top();
                    operators.pop();

                    if(b==0 && (op =='/' || op =='%'))
                        return std::numeric_limits<double>::quiet_NaN();

                    operands.push(GetResult(a, b, op));
                }
                else
                {
                    return std::numeric_limits<double>::quiet_NaN();
                }
            }

            operators.push(d);
        }
        else if(d == "(")
        {
            if (i > 0 && expression[i - 1] == '-') {
                operands.push(-1);
                operators.push('*');
            }
            operators.push('(');
        }
        else if(d == ")")
        {
            while (!operators.empty() && operators.top() != '(')
            {
                if(operands.length()>1)
                {
                    double b = operands.top();
                    operands.pop();
                    double a = operands.top();
                    operands.pop();
                    QChar op = operators.top();
                    operators.pop();

                    if((b==0 && op =='/') || op ==')' || (b==0 && op =='%'))
                        return std::numeric_limits<double>::quiet_NaN();

                    operands.push(GetResult(a, b, op));
                }
                else
                {
                    return std::numeric_limits<double>::quiet_NaN();
                }
            }

            if (!operators.empty())
                operators.pop();
        }
    }

    while(!operators.empty())
    {
        if(operands.length()>1)
        {
            double b = operands.top();
            operands.pop();
            double a = operands.top();
            operands.pop();
            QChar op = operators.top();
            operators.pop();

            if(b==0 && (op =='/' || op =='%'))
                return std::numeric_limits<double>::quiet_NaN();

            operands.push(GetResult(a, b, op));
        }
        else
        {
            return std::numeric_limits<double>::quiet_NaN();
        }
    }

    if(operands.length() > 1)
        return std::numeric_limits<double>::quiet_NaN();

    return operands.top();
}

bool MainWindow::IsOperator(QChar c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int MainWindow::GetOperatorImportance(QChar op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

double MainWindow::GetResult(double a, double b, QChar op)
{
    if(op == '+')
        return a+b;
    else if(op == '-')
        return a-b;
    else if(op == '*')
        return a*b;
    else if(op == '/')
        return a/b;
    else if(op == '%')
        return std::fmod(a, b);
    else if(op == '^')
        return pow(a,b);

    return std::numeric_limits<double>::quiet_NaN();;
}

void MainWindow::UpdateLabel()
{
    ui->label->setText(expression);
}

void MainWindow::ThrowSyntaxError()
{
    ui->label_2->setText("Syntax Error");
}

bool MainWindow::CheckIfCorrect(int l)
{
    int br = 0;

    for(int i=0; i<l; i++)
    {
        if(expression[i] == '(')
        {
            br++;
        }
        else if(expression[i] == ')')
        {
            br--;
        }

        if(br<0)
            return false;
    }

    if(br != 0)
        return false;

    return true;
}





// Buttons Handlers

void MainWindow::on_pushButton_0_clicked()
{
    if(!expression.isEmpty())
    {
        expression += "0";
        UpdateLabel();
    }
}
void MainWindow::on_pushButton_1_clicked()
{
    expression += "1";
    UpdateLabel();
}
void MainWindow::on_pushButton_2_clicked()
{
    expression += "2";
    UpdateLabel();
}
void MainWindow::on_pushButton_3_clicked()
{
    expression += "3";
    UpdateLabel();
}
void MainWindow::on_pushButton_4_clicked()
{
    expression += "4";
    UpdateLabel();
}
void MainWindow::on_pushButton_5_clicked()
{
    expression += "5";
    UpdateLabel();
}
void MainWindow::on_pushButton_6_clicked()
{
    expression += "6";
    UpdateLabel();
}
void MainWindow::on_pushButton_7_clicked()
{
    expression += "7";
    UpdateLabel();
}
void MainWindow::on_pushButton_8_clicked()
{
    expression += "8";
    UpdateLabel();
}
void MainWindow::on_pushButton_9_clicked()
{
    expression += "9";
    UpdateLabel();
}
void MainWindow::on_pushButton_dot_clicked()
{
    if(!expression.isEmpty())
    {
        QChar c = expression[expression.length()-1];
        if(c.isDigit())
        {
            expression += ".";
            UpdateLabel();
        }
    }
    else
    {
        expression += "0.";
        UpdateLabel();
    }
}
void MainWindow::on_pushButton_add_clicked()
{
    if(!expression.isEmpty() && !IsOperator(expression[expression.length()-1]))
    {
        expression += "+";
        UpdateLabel();
    }
}
void MainWindow::on_pushButton_sub_clicked()
{
    if(!expression.isEmpty())
    {
        QChar c = expression[expression.length()-1];

        if(c != '-')
        {
            expression += "-";
            UpdateLabel();
        }
    }
    else
    {
        expression += "-";
        UpdateLabel();
    }
}
void MainWindow::on_pushButton_multi_clicked()
{
    if(!expression.isEmpty() && !IsOperator(expression[expression.length()-1]))
    {
        expression += "*";
        UpdateLabel();
    }
}
void MainWindow::on_pushButton_div_clicked()
{
    if(!expression.isEmpty() && !IsOperator(expression[expression.length()-1]))
    {
        expression += "/";
        UpdateLabel();
    }
}
void MainWindow::on_pushButton_nl_clicked()
{
    expression += "(";
    UpdateLabel();
}
void MainWindow::on_pushButton_nr_clicked()
{
    expression += ")";
    UpdateLabel();
}
void MainWindow::on_pushButton_exec_clicked()
{
    if(!expression.isEmpty())
    {
        double result = EvaluateExpression(expression);

        if(!std::isnan(result) && !std::isinf(result))
        {
            ui->label_2->setText(QString::number(result));
            return;
        }

        ThrowSyntaxError();
    }
}
void MainWindow::on_pushButton_pow_clicked()
{
    if(!expression.isEmpty() && !IsOperator(expression[expression.length()-1]))
    {
        expression += "^";
        UpdateLabel();
    }
}
void MainWindow::on_pushButton_clear_clicked()
{
    expression = "0";
    UpdateLabel();
    expression = "";
}
void MainWindow::on_pushButton_back_clicked()
{
    if(!expression.isEmpty())
    {
        expression.chop(1);
        UpdateLabel();

        if(expression.isEmpty())
        {
            expression = "0";
            UpdateLabel();
            expression = "";
        }
    }
}
void MainWindow::on_pushButton_mod_clicked()
{
    if(!expression.isEmpty() && !IsOperator(expression[expression.length()-1]))
    {
        expression += "%";
        UpdateLabel();
    }
}
