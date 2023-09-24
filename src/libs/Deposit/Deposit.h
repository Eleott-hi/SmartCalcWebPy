#ifndef _DEPOSIT_H_
#define _DEPOSIT_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "../dependencies/date/date.h"

namespace s21 {

class Deposit {
public:
    enum Period { NONE, DAY, WEEK, MONTH, QUARTER, HALF_YEAR, YEAR };
    struct Deposit_info {
        date::sys_days date_start;
        size_t term;
        double percent;
        double percent_max_without_bill;
        double percent_bill;
        double sum_in;
        double sum_add;
        double sum_sub;
        Period cop_period;
        Period add_period;
        Period sub_period;
    };

    Deposit() : m_date_finish_(), m_info_(), m_bill_res_(), m_profit_res_(), m_percentage_(){};
    ~Deposit(){};

    void set_deposit_info(const Deposit_info &info);
    void calculate_deposit();
    std::vector<std::string> get_info() const;

private:
    date::sys_days m_date_finish_;
    Deposit_info m_info_;
    double m_bill_res_;
    double m_profit_res_;
    double m_percentage_;
    std::ostringstream profite_, bills_, profit_wb_, summary_;

    void _calculate_deposit(bool complicated);
    void calc_bills(date::sys_days cur_date, double &profit);
    void check_adding(const date::sys_days &cur_date, date::sys_days &add_date, date::sys_days &sub_date);
    void add_money(bool add_operation, date::sys_days &operation_date);
    static bool check_leap_year(const date::sys_days &d);
    static double simple_percent(double sum_in, double percent, int days, int leap_year);
    date::sys_days calc_next_date(const date::sys_days &day, Period period) const;
    date::sys_days _calc_next_date(const date::year_month_day &ymd) const;
};

}  // namespace s21

#endif  // _DEPOSIT_H_
