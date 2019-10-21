open Jest;
open Expect;
open App;
open Hand;

describe("sort card", () => {

  test("1H 2H 3H 4H 5H -> 1H 2H 3H 4H 5H", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Heart), 
      (Four, Heart),
      (Five, Heart),
      (Six, Heart)
    ]
    expect(sortCard(hand)) |> toEqual(hand)
  });

  test("2H 4S 4C 2D 4H -> 2_ 2_ 4_ 4_ 4_", () => {
    let givenHand: hand = [
      (Two, Heart),
      (Four, Spade), 
      (Four, Club),
      (Two, Diamond),
      (Four, Heart)
    ]
    let expectedHand: hand = [
      (Two, Heart),
      (Two, Diamond),
      (Four, Spade),
      (Four, Club),
      (Four, Heart)
    ]
    expect(sortCard(givenHand)) |> toEqual(expectedHand)
  });
});

describe("fight", () => {
  test("Black: 2H 3D 5S 9C KD and White: 2C 3H 4S 8C AH -> White win with high card Ace", () => {
    let blackHand = [
      (Two, Heart),
      (Three, Diamond),
      (Five, Spade),
      (Nine, Club),
      (King, Diamond)
    ]
    let whiteHand = [
      (Two, Club),
      (Three, Heart),
      (Four, Spade),
      (Eight, Club),
      (Ace, Heart)
    ]
    expect(fight(blackHand, whiteHand)) |> toEqual(White(HighCard(Ace)))
  })

  test("Black: 2H 4S 4C 2D 4H and White: 2S 8S AS QS 3S -> Black win with full house 4 over 2", () => {
    let blackHand = [
      (Two, Heart),
      (Four, Spade),
      (Four, Club),
      (Two, Diamond),
      (Four, Heart)
    ]
    let whiteHand = [
      (Two, Spade),
      (Eight, Spade),
      (Ace, Spade),
      (Queen, Spade),
      (Three, Spade)
    ]

    expect(fight(blackHand, whiteHand)) |> toEqual(Black(FullHouse(Four)))
  })

  test("Black: 2H 3D 5S 9C KD  White: 2C 3H 4S 8C KH -> Black win with high card 9", () => {
    let blackHand = [
      (Two, Heart),
      (Three, Diamond),
      (Five, Spade),
      (Nine, Club),
      (King, Diamond)
    ]
    let whiteHand = [
      (Two, Club),
      (Three, Heart),
      (Four, Spade),
      (Eight, Club),
      (King, Heart)
    ]

    expect(fight(blackHand, whiteHand)) |> toEqual(Black(HighCard(Nine)))
  })

  test("Black: 2H 3D 5S 9C KD  White: 2D 3H 5C 9S KH -> Tie", () => {
    let blackHand = [
      (Two, Heart),
      (Three, Diamond),
      (Five, Spade),
      (Nine, Club),
      (King, Diamond)
    ]
    let whiteHand = [
      (Two, Club),
      (Three, Heart),
      (Five, Club),
      (Nine, Spade),
      (King, Heart)
    ]

    expect(fight(blackHand, whiteHand)) |> toEqual(Tie)
  })

  test("Black: 3H 3D 4S 4C 9D  White: 2D 2H 4D 4H 9S -> black win with 3", () => {
    let blackHand = [
      (Three, Heart),
      (Three, Diamond),
      (Four, Spade),
      (Four, Club),
      (Nine, Diamond)
    ]
    let whiteHand = [
      (Two, Diamond),
      (Two, Heart),
      (Four, Diamond),
      (Four, Heart),
      (Nine, Spade)
    ]

    expect(fight(blackHand, whiteHand)) |> toEqual(Black(TwoPairs((Three, Four))))
  })

  test("Black: 2S 2C 4S 4C 9D  White: 2D 2H 4D 4H TS -> white win with 10", () => {
    let blackHand = [
      (Two, Spade),
      (Two, Club),
      (Four, Spade),
      (Four, Club),
      (Nine, Diamond)
    ]
    let whiteHand = [
      (Two, Diamond),
      (Two, Heart),
      (Four, Diamond),
      (Four, Heart),
      (Ten, Spade)
    ]

    expect(fight(blackHand, whiteHand)) |> toEqual(White(HighCard(Ten)))
  })
})
