#pragma once
/* CREDIT : bschiffthaler/BSlogger */
/* https://github.com/bschiffthaler/BSlogger/tree/master/src */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#define LOG_SILENT 0
#define LOG_ERR 1
#define LOG_ERROR 1
#define LOG_WARN 2
#define LOG_WARNING 2
#define LOG_INFO 3
#define LOG_TIME 4
#define LOG_DEBUG 5
#define LOG_DEFAULT 4

#define LOG_INIT_COUT() logger log(std::cout, __PRETTY_FUNCTION__)
#define LOG_INIT_CERR() logger log(std::cerr, __PRETTY_FUNCTION__)
#define LOG_INIT_CLOG() logger log(std::clog, __PRETTY_FUNCTION__)
#define LOG_INIT_CUSTOM(X) logger log((X), __PRETTY_FUNCTION__)

#ifdef BSLOG_NO_COLORS

#define BSLOG_TIME "[ TIME    ]"
#define BSLOG_DEBUG "[ DEBUG   ]"
#define BSLOG_ERROR "[ ERROR   ]"
#define BSLOG_WARNING "[ WARNING ]"
#define BSLOG_INFO "[ INFO    ]"

#else

#define BSLOG_TIME "\033[0;35m[ TIME    ]\033[0;0m"
#define BSLOG_DEBUG "[ DEBUG   ]"
#define BSLOG_ERROR "\033[0;31m[ ERROR   ]\033[0;0m"
#define BSLOG_WARNING "\033[0;33m[ WARNING ]\033[0;0m"
#define BSLOG_INFO "\033[0;34m[ INFO    ]\033[0;0m"

#endif

namespace TotoCompiler::Utility {


    template<typename T>
    std::string format_duration(T xms) {
        uint64_t seconds = static_cast<uint64_t>(xms);
        uint64_t days = 0;
        uint64_t hours = 0;
        uint64_t minutes = 0;

        if (seconds >= 86400) {
            days = seconds / 86400;
            seconds -= (days * 86400);
        }
        if (seconds >= 3600) {
            hours = seconds / 3600;
            seconds -= (hours * 3600);
        }
        if (seconds >= 60) {
            minutes = seconds / 60;
            seconds -= (minutes * 60);
        }

        std::stringstream ss;
        if (days > 0) {
            ss << std::setfill('0') << std::setw(2) << days << '-';
        }
        if (hours > 0) {
            ss << std::setfill('0') << std::setw(2) << hours << ':';
        }
        if (minutes > 0) {
            ss << std::setfill('0') << std::setw(2) << minutes << ':';
        }
        // Always display seconds no matter what
        ss << std::setfill('0') << std::setw(2) << seconds;
        return ss.str();
    }

    class TLogger {
    public:
        inline TLogger(std::ostream &, unsigned, std::string);

        inline TLogger(std::ostream &, std::string n);

        template<typename T>
        friend TLogger &operator<<(TLogger &l, const T &s);

        inline TLogger &operator()(unsigned ll);

        inline void add_snapshot(std::string n, bool quiet = true) {
            time_t now;
            time(&now);
            _snaps.push_back(now);
            _snap_ns.push_back(n);
            if (_loglevel() >= LOG_TIME && !quiet)
                _fac << BSLOG_TIME << prep_time(*this) << prep_name(*this)
                     << ": Added snap '" << n << "'\n";
        }

        inline void time_since_start();

        inline void time_since_last_snap();

        inline void time_since_snap(std::string);

        inline void flush() { _fac.flush(); }

        friend std::string prep_level(TLogger &l);

        friend std::string prep_time(TLogger &l);

        friend std::string prep_name(TLogger &l);

        static unsigned &_loglevel() {
            static unsigned _ll_internal = LOG_DEFAULT;
            return _ll_internal;
        };

        inline void set_log_level(unsigned ll) { _loglevel() = ll; }

    private:
        time_t _now;
        time_t _start;
        std::vector<time_t> _snaps;
        std::vector<std::string> _snap_ns;
        unsigned _message_level;
        std::ostream &_fac;
        std::string _name;
    };

    inline std::string prep_level(TLogger &l);

    inline std::string prep_time(TLogger &l);

    inline std::string prep_name(TLogger &l);

// unsigned logger::_loglevel = LOG_DEFAULT;

    template<typename T>
    TLogger &operator<<(TLogger &l, const T &s) {
        if (l._message_level <= l._loglevel()) {
            l._fac << s;
            return l;
        } else {
            return l;
        }
    }

    TLogger::TLogger(std::ostream &f, std::string n)
            : _message_level(LOG_SILENT), _fac(f), _name(n) {
        time(&_now);
        time(&_start);
    }

    TLogger::TLogger(std::ostream &f, unsigned ll, std::string n)
            : _message_level(LOG_SILENT), _fac(f), _name(n) {
        time(&_now);
        time(&_start);
        _loglevel() = ll;
    }

    TLogger &TLogger::operator()(unsigned ll) {
        _message_level = ll;
        if (_message_level <= _loglevel()) {
            _fac << prep_level(*this) << prep_time(*this) << prep_name(*this) << ": ";
        }
        return *this;
    }

    std::string prep_level(TLogger &l) {
        switch (l._message_level) {
            case LOG_ERR:
                return BSLOG_ERROR;
                break;
            case LOG_WARN:
                return BSLOG_WARNING;
                break;
            case LOG_INFO:
                return BSLOG_INFO;
                break;
            case LOG_DEBUG:
                return BSLOG_DEBUG;
                break;
            case LOG_TIME:
                return BSLOG_TIME;
                break;
            default:
                return "";
        }
        return "";
    }

    std::string prep_time(TLogger &l) {
        time(&l._now);
        struct tm *t;
        t = localtime(&l._now);
        std::string s, m, h, D, M, Y;
        s = std::to_string(t->tm_sec);
        m = std::to_string(t->tm_min);
        h = std::to_string(t->tm_hour);
        D = std::to_string(t->tm_mday);
        M = std::to_string(t->tm_mon + 1);
        Y = std::to_string(t->tm_year + 1900);

        if (t->tm_sec < 10) s = "0" + s;
        if (t->tm_min < 10) m = "0" + m;
        if (t->tm_hour < 10) h = "0" + h;
        if (t->tm_mday < 10) D = "0" + D;
        if (t->tm_mon + 1 < 10) M = "0" + M;

        std::string ret =
                "[ " + Y + "-" + M + "-" + D + "T" + h + ":" + m + ":" + s + " ]";

        return ret;
    }

    std::string prep_name(TLogger &l) { return "[ " + l._name + " ]"; }

    void TLogger::time_since_start() {
        if (_loglevel() >= LOG_TIME) {
            time(&_now);
            _message_level = LOG_TIME;
            _fac << prep_level(*this) << prep_time(*this) << prep_name(*this) << ": "
                 << difftime(_now, _start) << "s since instantiation\n";
        }
    }

    void TLogger::time_since_last_snap() {
        if (_loglevel() >= LOG_TIME && _snap_ns.size() > 0) {
            time(&_now);
            _message_level = LOG_TIME;
            _fac << prep_level(*this) << prep_time(*this) << prep_name(*this) << ": "
                 << difftime(_now, _snaps.back()) << "s since snap '" << _snap_ns.back()
                 << "'\n";
        }
    }

    void TLogger::time_since_snap(std::string s) {
        if (_loglevel() >= LOG_TIME) {
            time(&_now);
            auto it = find(_snap_ns.begin(), _snap_ns.end(), s);
            if (it == _snap_ns.end()) {
                _message_level = LOG_WARN;
                _fac << prep_level(*this) << prep_time(*this) << prep_name(*this) << ": "
                     << "Could not find snapshot " << s << '\n';
                return;
            }
            unsigned long dist = std::distance(_snap_ns.begin(), it);

            _message_level = LOG_TIME;
            _fac << prep_level(*this) << prep_time(*this) << prep_name(*this) << ": "
                 << difftime(_now, _snaps[dist]) << "s since snap '" << _snap_ns[dist]
                 << "'\n";
        }
    }

    template<typename T>
    class progbar_simple {
    public:
        progbar_simple(std::ostream &f, T max, uint64_t width = 80)
                : _max(static_cast<double>(max)),
                  _sum(0),
                  _state(0),
                  _incr(0),
                  _fac(f),
                  _width(width),
                  _final(false) {
            _incr = _max / static_cast<double>(_width);
            _fac << "0%";
            for (uint64_t i = 0; i < _width - 1; i++) {
                _fac << '-';
            }
            _fac << "100%" << std::endl;
            _fac << "[";
            _state = _incr;
            _fac.flush();
        };

        void check() {
            if (_sum >= _state) {
                _state += _incr;
                _width--;
                _fac << "=";
                _fac.flush();
                if (_width == 0 && !_final) {
                    _fac << "]\n";
                    _fac.flush();
                    _final = true;
                }
            }
        }

        void finalize() {
            if (!_final) {
                _final = true;
                _fac << "]\n";
                _fac.flush();
            }
        }

        void operator()(const T &x) {
            double dx = static_cast<double>(x);
            _sum = dx;
            check();
        }

        progbar_simple &operator++() {
            _sum += 1;
            check();
            return *this;
        }

        progbar_simple operator++(int) {
            progbar_simple copy(*this);
            _sum += 1;
            check();
            return copy;
        }

        progbar_simple &operator+=(const T &x) {
            _sum += static_cast<double>(x);
            check();
            return *this;
        }

    private:
        double _max;
        double _sum;
        double _state;
        double _incr;
        std::ostream &_fac;
        uint64_t _width;
        bool _final;
    };

    template<typename T>
    class progbar_fancy {
    public:
        progbar_fancy(std::ostream &f, T max, uint64_t poll_interval = 1000,
                      uint64_t width = 30, std::string unit = "")
                : m_max(static_cast<double>(max)),
                  m_sum(0),
                  m_state(0),
                  m_incr(0),
                  m_fac(f),
                  m_width(width),
                  m_unit(unit),
                  m_final(false) {
            m_incr = m_max / static_cast<double>(m_width);
            m_start = std::chrono::system_clock::now();
            m_before = m_start;
            m_state = m_incr;
            m_poll_interval = std::chrono::milliseconds(poll_interval);
            m_fac << std::setprecision(2) << std::fixed;
            m_fac.flush();
        };

        void check() {
            std::chrono::system_clock::time_point now =
                    std::chrono::system_clock::now();
            std::chrono::milliseconds diff =
                    std::chrono::duration_cast<std::chrono::milliseconds>(now - m_before);
            if (diff > m_poll_interval) {
                std::chrono::seconds diff_start =
                        std::chrono::duration_cast<std::chrono::seconds>(now - m_start);
                double ds = std::chrono::duration<double>(diff_start).count();
                double dss = m_sum / ds;

                int64_t dss_i = std::ceil((m_max - m_sum) / dss);

                auto eta = std::chrono::duration<uint64_t>(dss_i);

                std::string prefix = "";
                if (dss > 1e15) {
                    prefix = "P";
                    dss /= 1e15;
                } else if (dss > 1e12) {
                    prefix = "T";
                    dss /= 1e12;
                } else if (dss > 1e9) {
                    prefix = "G";
                    dss /= 1e9;
                } else if (dss > 1e6) {
                    prefix = "M";
                    dss /= 1e6;
                } else if (dss > 1e3) {
                    prefix = "K";
                    dss /= 1e3;
                }
                m_before = now;
                m_fac << "\r" << std::flush;
                m_fac << "|";
                for (double i = 0; i < m_max; i += m_incr) {
                    m_fac << (i < m_sum ? "=" : " ");
                }
                m_fac << "| " << (m_sum / m_max) * 100 << "% | " << dss << " " << prefix
                      << m_unit << "/s | " << format_duration<uint64_t>(diff_start.count())
                      << " | " << format_duration<uint64_t>(eta.count()) << std::flush;
                if (m_sum >= m_max) {
                    finalize();
                }
            }
        }

        void finalize() {
            if (!m_final) {
                m_fac << std::endl;
                m_final = true;
                m_fac.flush();
            }
        }

        void operator()(const T &x) {
            double dx = static_cast<double>(x);
            m_sum = dx;
            check();
        }

        progbar_fancy &operator++() {
            m_sum += 1;
            check();
            return *this;
        }

        progbar_fancy operator++(int) {
            progbar_fancy copy(*this);
            m_sum += 1;
            check();
            return copy;
        }

        progbar_fancy &operator+=(const T &x) {
            m_sum += static_cast<double>(x);
            check();
            return *this;
        }

    private:
        double m_max;
        double m_sum;
        double m_state;
        double m_incr;
        std::ostream &m_fac;
        uint64_t m_width;
        std::chrono::milliseconds m_poll_interval;
        std::chrono::system_clock::time_point m_before;
        std::chrono::system_clock::time_point m_start;
        std::string m_unit;
        bool m_final;
    };

}