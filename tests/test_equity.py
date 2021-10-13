import ompeval

if __name__ == "__main__":
    ranges = [
        ompeval.CardRange("65s"),
        ompeval.CardRange("random"),
        ompeval.CardRange("random"),
        ompeval.CardRange("random"),
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
