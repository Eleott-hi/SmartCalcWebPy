#include "../headers/Deposit.h"

namespace s21 {

std::vector<std::string> Deposit::get_info() const {
    return std::vector<std::string>{profite_.str(), bills_.str(), profit_wb_.str(), summary_.str()};
}

bool Deposit::check_leap_year(const date::sys_days &d) { return date::year_month_day(d).year().is_leap(); }

double Deposit::simple_percent(double sum_in, double percent, int days, int leap_year) {
    return sum_in * days * percent / (leap_year ? 366. : 365.);
}

date::sys_days Deposit::calc_next_date(const date::sys_days &day, Period period) const {
    date::sys_days res;

    switch (period) {
        case DAY:
            res = day + date::days{1};
            break;
        case WEEK:
            res = day + date::weeks{7};
            break;
        case MONTH:
            res = _calc_next_date(date::year_month_day{day} + date::months{1});
            break;
        case QUARTER:
            res = _calc_next_date(date::year_month_day{day} + date::months{3});
            break;
        case HALF_YEAR:
            res = _calc_next_date(date::year_month_day{day} + date::months{6});
            break;
        case YEAR:
            res = _calc_next_date(date::year_month_day{day} + date::years{1});
            break;

        default:
            break;
    }
    return res;
}

date::sys_days Deposit::_calc_next_date(const date::year_month_day &ymd) const {
    date::year_month_day tmp = {ymd.year() / ymd.month() / date::year_month_day{m_info_.date_start}.day()};
    return ymd.ok() ? tmp : date::year_month_day{tmp.year() / tmp.month() / date::literals::last};
}

void Deposit::set_deposit_info(const Deposit_info &info) {
    m_info_ = info;
    m_date_finish_ = _calc_next_date(date::year_month_day{m_info_.date_start} + date::months{m_info_.term});
    m_info_.percent /= 100.0;
    m_info_.percent_max_without_bill /= 100.0;
    m_info_.percent_bill /= 100.0;
    m_percentage_ = m_info_.percent - m_info_.percent_max_without_bill;
}

void Deposit::calculate_deposit() {
    profite_.clear(), profite_.str("");
    bills_.clear(), bills_.str("");
    profit_wb_.clear(), profit_wb_.str("");
    summary_.clear(), summary_.str("");

    _calculate_deposit(m_info_.cop_period != NONE);

    profite_ << std::fixed << std::setprecision(2) << m_profit_res_;
    bills_ << std::fixed << std::setprecision(2) << m_bill_res_;
    profit_wb_ << std::fixed << std::setprecision(2) << m_profit_res_ - m_bill_res_;
    summary_ << std::fixed << std::setprecision(2) << m_info_.sum_in;
}

void Deposit::_calculate_deposit(bool complicated) {
    m_bill_res_ = m_profit_res_ = 0;
    double income = 0;
    double profit = 0;

    date::sys_days cur_date = m_info_.date_start;
    date::sys_days add_date = calc_next_date(cur_date, m_info_.add_period);
    date::sys_days sub_date = calc_next_date(cur_date, m_info_.sub_period);
    date::sys_days cop_date = calc_next_date(cur_date, complicated ? m_info_.cop_period : MONTH);

    while (cur_date != m_date_finish_) {
        cur_date += date::days{1};
        income += simple_percent(m_info_.sum_in, m_info_.percent, 1, check_leap_year(cur_date));
        if (cur_date == cop_date) {
            m_profit_res_ += round(income * 100.0) / 100.0;
            profit += income;
            if (complicated) m_info_.sum_in += round(income * 100.0) / 100.0;
            cop_date = calc_next_date(cur_date, complicated ? m_info_.cop_period : MONTH);
            income = 0.0;
        }
        check_adding(cur_date, add_date, sub_date);
        calc_bills(cur_date, profit);
    }
}

void Deposit::calc_bills(date::sys_days cur_date, double &profit) {
    if (((date::year_month_day{cur_date}.month() == date::December &&
          date::year_month_day{cur_date}.day() == date::day{31}) ||
         cur_date == m_date_finish_)) {
        if (date::year_month_day{cur_date}.year() > date::year{2022}) {
            double tmp = (profit - 1000000 * m_info_.percent_max_without_bill) * m_info_.percent_bill;
            if (tmp > 0.0) {
                m_bill_res_ += tmp;
            }
        }
        profit = 0.0;
    }
}

void Deposit::check_adding(const date::sys_days &cur_date, date::sys_days &add_date,
                           date::sys_days &sub_date) {
    if (m_info_.add_period != NONE && cur_date == add_date) {
        add_money(true, add_date);
    }
    if (m_info_.sub_period != NONE && cur_date == sub_date) {
        add_money(false, sub_date);
    }
}

void Deposit::add_money(bool add_operation, date::sys_days &operation_date) {
    m_info_.sum_in += add_operation ? m_info_.sum_add : -m_info_.sum_sub;
    operation_date = calc_next_date(operation_date, add_operation ? m_info_.add_period : m_info_.sub_period);
}

}  // namespace s21
