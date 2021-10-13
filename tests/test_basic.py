# -*- coding: utf-8 -*-
import ompeval

def test_main():
    assert ompeval.__version__ == "0.0.11"

    ranges = [
        ompeval.CardRange("65s"),
        ompeval.CardRange("random"),
        ompeval.CardRange("random"),
        ompeval.CardRange("random"),
    ]

    eq = ompeval.EquityCalculator()
    eq.set_hand_limit(10**6)

    eq.start(hand_ranges=ranges)
    eq.wait()

    res = eq.get_results()

    assert res.finished == True

