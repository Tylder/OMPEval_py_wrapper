from typing import List

import ompeval

if __name__ == "__main__":
    ranges = [
        ompeval.CardRange("65s"),
        # ompeval.CardRange("22+,A2s+,K2s+,Q2s+,J2s+,T2s+,92s+,82s+,72s+,62s+,52s+,42s+,32s,A2o+,K2o+,Q2o+,J2o+,T2o+,93o+,84o+,74o+, 63o+,53o+"),
        ompeval.CardRange("random"),
        # ompeval.CardRange("random"),
        # ompeval.CardRange("random"),
    ]
    board = ompeval.CardRange.getCardMask(text="")
    dead = ompeval.CardRange.getCardMask(text="")

    eq = ompeval.EquityCalculator()
    eq.set_hand_limit(10**6)
    # eq.set_time_limit(0.02)


    eq.start(hand_ranges=ranges, board_cards=board, dead_cards=dead, enumerate_all=False)
    eq.wait()

    res = eq.get_results()

    print(res.equity)
