#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>


#include "../extern/OMPEval/omp/CardRange.h"
#include "../extern/OMPEval/omp/CombinedRange.h"
#include "../extern/OMPEval/omp/EquityCalculator.h"
#include "../extern/OMPEval/omp/HandEvaluator.h"
#include "../extern/OMPEval/omp/Hand.h"
#include "../extern/OMPEval/omp/Constants.h"


#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;
using namespace omp;

PYBIND11_MODULE(ompeval, m) {
    m.doc() = R"pbdoc(
        OMPEval Python Wrapper
        -----------------------
        .. currentmodule:: ompeval
        .. autosummary::
           :toctree: _generate

    )pbdoc";


    py::class_<Hand>(m, "Hand")
            .def(py::init())
            .def(py::init<const Hand &>())
            .def(py::init<unsigned>())
            .def(py::init<std::array<uint8_t, 2>>())

            .def(py::self + py::self)
            .def(py::self += py::self)
            .def(py::self - py::self)
            .def(py::self -= py::self)
            .def(py::self == py::self)

            .def_static("empty", &Hand::empty)
            .def("suit_count", &Hand::suitCount, py::arg("suit"))
            .def("count", &Hand::count)
            .def("has_flush", &Hand::hasFlush)
            .def("rank_key", &Hand::rankKey)
            .def("flush_key", &Hand::flushKey);

    py::class_<HandEvaluator>(m, "HandEvaluator")
            .def(py::init())
            .def("evaluate", &HandEvaluator::evaluate<true>, py::arg("hand"));


    py::class_<CardRange>(m, "CardRange")
            .def(py::init())
            .def(py::init<const std::string &>())
            .def(py::init<const char *>())
            .def(py::init<const std::vector<std::array<uint8_t, 2>> &>())

            .def("combinations", &CardRange::combinations)
            .def_static("getCardMask", &CardRange::getCardMask, py::arg("text"));

    py::class_<EquityCalculator>(m, "EquityCalculator")
            .def(py::init())
            .def("start", &EquityCalculator::start,
                 py::arg("hand_ranges"),
                 py::arg("board_cards") = 0,
                 py::arg("dead_cards") = 0,
                 py::arg("enumerate_all") = false,
                 py::arg("stdev_target") = 5e-5,
                 py::arg("callback") = nullptr,
                 py::arg("update_interval") = 0.2,
                 py::arg("thread_count") = 0
            )
            .def("stop", &EquityCalculator::stop)
            .def("wait", &EquityCalculator::wait)
            .def("set_time_limit", &EquityCalculator::setTimeLimit,
                 py::arg("seconds")
            )
            .def("set_hand_limit", &EquityCalculator::setHandLimit,
                 py::arg("hand_limit"))
            .def("get_results", &EquityCalculator::getResults)
            .def("hand_ranges", &EquityCalculator::handRanges);


    py::class_<EquityCalculator::Results>(m, "Results")
            .def(py::init())
            .def_readwrite("players", &EquityCalculator::Results::players)

            .def_property_readonly("equity", [](py::object &obj) {
                                       auto &o = obj.cast<EquityCalculator::Results &>();
                                       return py::array_t<double>{MAX_PLAYERS, o.equity, obj};
                                   }
            )
            .def_property_readonly("wins", [](py::object &obj) {
                                       auto &o = obj.cast<EquityCalculator::Results &>();
                                       return py::array_t<uint64_t>(MAX_PLAYERS, o.wins, obj);
                                   }
            )
            .def_property_readonly("ties", [](py::object &obj) {
                                       auto &o = obj.cast<EquityCalculator::Results &>();
                                       return py::array_t<double>{MAX_PLAYERS, o.ties, obj};
                                   }
            )
            .def_property_readonly("wins_by_player_mask", [](py::object &obj) {
                                       auto &o = obj.cast<EquityCalculator::Results &>();
                                       return py::array_t<uint64_t>(uint64_t(1) << MAX_PLAYERS, o.winsByPlayerMask, obj);
                                   }
            )
            .def_readonly("hands", &EquityCalculator::Results::hands)
            .def_readonly("interval_hands", &EquityCalculator::Results::intervalHands)
            .def_readonly("speed", &EquityCalculator::Results::speed)
            .def_readonly("interval_speed", &EquityCalculator::Results::intervalSpeed)
            .def_readonly("time", &EquityCalculator::Results::time)
            .def_readonly("interval_time", &EquityCalculator::Results::intervalTime)
            .def_readonly("stdev", &EquityCalculator::Results::stdev)
            .def_readonly("stdev_per_hand", &EquityCalculator::Results::stdevPerHand)
            .def_readonly("progress", &EquityCalculator::Results::progress)
            .def_readonly("preflop_combos", &EquityCalculator::Results::preflopCombos)
            .def_readonly("skipped_preflop_combos", &EquityCalculator::Results::skippedPreflopCombos)
            .def_readonly("evaluated_preflop_combos", &EquityCalculator::Results::evaluatedPreflopCombos)
            .def_readonly("evaluations", &EquityCalculator::Results::evaluations)
            .def_readonly("enumerate_all", &EquityCalculator::Results::enumerateAll)
            .def_readonly("finished", &EquityCalculator::Results::finished);


#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}

