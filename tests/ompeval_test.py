# -*- coding: utf-8 -*-
import ompeval


def test_version():
    assert ompeval.__version__ == "0.0.11"


def test_equity():
    ranges = [
        ompeval.CardRange("65s"),
        ompeval.CardRange("random"),
        ompeval.CardRange("random"),
        ompeval.CardRange("random"),
    ]

    eq = ompeval.EquityCalculator()
    eq.set_hand_limit(1000) # super low since its just a test

    eq.start(hand_ranges=ranges)
    eq.wait()

    res = eq.get_results()

    assert res.finished is True


def test_evaluator():
    # Create a Hand from a card. CardIdx is an integer between 0 and 51, so that CARD = 4 * RANK + SUIT, where
    # rank ranges from 0 (deuce) to 12 (ace) and suit is from 0 (spade) to 3 (diamond).
    # in order = spade, heart, clubs, diamond

    # AdAs2s2h2c
    hand = ompeval.Hand.empty() + \
           ompeval.Hand(51) + \
           ompeval.Hand(48) + \
           ompeval.Hand(0) + \
           ompeval.Hand(1) + \
           ompeval.Hand(2)

    evaluator = ompeval.HandEvaluator()
    value = evaluator.evaluate(hand)  # 28684 = 7 * 4096 + 12

    assert value == 28684
