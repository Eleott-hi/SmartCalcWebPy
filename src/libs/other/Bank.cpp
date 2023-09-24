#include "../headers/mainwindow.h"
#include "../others/ui_mainwindow.h"

void MainWindow::on_b_CreditCalculate_clicked() {
    auto res = controller.calc_credit({ui->creditSum->value(), ui->creditRate->value(),
                                       ui->creditTerm->value(), ui->creditType->currentIndex() == 0});

    ui->credit_payment_label->setText(res.at(0).c_str());
    ui->credit_overpay_label->setText(res.at(1).c_str());
    ui->credit_summary_label->setText(res.at(2).c_str());
}

void MainWindow::on_b_DepositCalculate_clicked() {
    auto res = controller.calc_deposit({{date::month{(unsigned)ui->dateBox->date().month()} /
                                         ui->dateBox->date().day() / ui->dateBox->date().year()},
                                        (size_t)ui->deposit_term->value(),
                                        ui->deposit_percent->value(),
                                        ui->deposit_cb_percent->value(),
                                        ui->deposit_bill_percent->value(),
                                        ui->deposit_sum_in->value(),
                                        ui->deposit_add->value(),
                                        ui->deposit_sub->value(),
                                        (s21::Deposit::Period)ui->deposit_cap_period->currentIndex(),
                                        (s21::Deposit::Period)ui->deposit_add_period->currentIndex(),
                                        (s21::Deposit::Period)ui->deposit_sub_period->currentIndex()});

    ui->deposit_profit_label->setText(res.at(0).c_str());
    ui->deposit_bills_label->setText(res.at(1).c_str());
    ui->deposit_pwb_label->setText(res.at(2).c_str());
    ui->deposit_summary_label->setText(res.at(3).c_str());
}
