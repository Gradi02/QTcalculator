#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double EvaluateExpression(const QString& expression);

private slots:
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_dot_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_sub_clicked();
    void on_pushButton_multi_clicked();
    void on_pushButton_div_clicked();
    void on_pushButton_nl_clicked();
    void on_pushButton_nr_clicked();
    void on_pushButton_exec_clicked();
    void on_pushButton_pow_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_mod_clicked();

private:
    Ui::MainWindow *ui;
    bool IsOperator(QChar c);
    int GetOperatorImportance(QChar op);
    double GetResult(double a, double b, QChar op);
    void UpdateLabel();
    void ThrowSyntaxError();
    bool CheckIfCorrect(int l);

public:
    QString expression;
};
#endif // MAINWINDOW_H
