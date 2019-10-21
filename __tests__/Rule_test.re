open Jest;
open Expect;
open Rule;
open Hand;

describe("check pair", () => {
  
  test("2H 2D 4C 4S 4H -> 2", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Diamond), 
      (Four, Club),
      (Four, Spade),
      (Four, Heart)
    ]
   expect(checkPair(hand)) |> toEqual(Pair(Two))
  });

  test("2S 3S 4S 5S 6S -> None", () => {
    let hand: hand = [
      (Two, Spade),
      (Three, Spade), 
      (Four, Spade),
      (Five, Spade),
      (Six, Spade)
    ]
    expect(checkPair(hand)) |> toEqual(NotFound)
  })
})

describe("check two pair", () => {

  test("2H 3S 5H 8S 9C -> None", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Spade),
      (Five, Heart),
      (Eight, Spade),
      (Nine, Club)
    ]
    expect(checkTwoPair(hand)) |> toEqual(NotFound)
  })

  test("2H 2S 5H 5S 9C -> TwoPairs(2,5)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Spade),
      (Five, Heart),
      (Five, Spade),
      (Nine, Club)
    ]
    expect(checkTwoPair(hand)) |> toEqual(TwoPairs((Two, Five)))
  })

  test("2H 2S 3H 4S 4C -> TwoPairs(2,4)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Spade),
      (Three, Heart),
      (Four, Spade),
      (Four, Club)
    ]
    expect(checkTwoPair(hand)) |> toEqual(TwoPairs((Two, Four)))
  })
    
})

describe("check three of a kind", () => {
  test("2H 3H 4H 5D 6S -> None", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Heart),
      (Four, Heart),
      (Five, Diamond),
      (Six, Spade)
    ]
    expect(checkThreeOfAKind(hand)) |> toEqual(NotFound)
  })

  test("2H 2D 2S 5D 6S -> ThreeOfAKind(2)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Diamond),
      (Two, Spade),
      (Five, Diamond),
      (Six, Spade)
    ]
    expect(checkThreeOfAKind(hand)) |> toEqual(ThreeOfAKind(Two))
  })

  test("2H 3D 4S 4D 4H -> ThreeOfAKind(4)", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Diamond),
      (Four, Spade),
      (Four, Diamond),
      (Four, Heart)
    ]
    expect(checkThreeOfAKind(hand)) |> toEqual(ThreeOfAKind(Four))
  })
})

describe("check Straight", () => {
  test("2H 4H 7S 8H JS -> None", () => {
    let hand: hand = [
      (Two, Heart),
      (Four, Heart),
      (Seven, Spade),
      (Eight, Heart),
      (Jack, Spade)
    ]
    expect(checkStraight(hand)) |> toEqual(NotFound)
  })

  test("2H 3S 4S 5C 6S -> Straight(6)", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Spade),
      (Four, Spade),
      (Five, Club),
      (Six, Spade)
    ]
    expect(checkStraight(hand)) |> toEqual(Straight(Six))
  })

  test("7H 8S 9S TC JS -> Straight(Jack)", () => {
    let hand: hand = [
      (Seven, Heart),
      (Eight, Spade),
      (Nine, Spade),
      (Ten, Club),
      (Jack, Spade)
    ]
    expect(checkStraight(hand)) |> toEqual(Straight(Jack))
  })

  test("TS JH QC KC AC -> Straight(Ace)", () => {
    let hand: hand = [
      (Ten, Spade),
      (Jack, Heart),
      (Queen, Club),
      (King, Club),
      (Ace, Club)
    ]
    expect(checkStraight(hand)) |> toEqual(Straight(Ace))
  })
})

describe("check Flush", () => {
  test("2H 3C 4S 4C 5S -> None", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Club),
      (Four, Spade),
      (Four, Club),
      (Five, Spade)
    ]
    expect(checkFlush(hand)) |> toEqual(NotFound)
  })

  test("2H 3H 4H 5H 8H -> Flush(8)", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Heart),
      (Four, Heart),
      (Five, Heart),
      (Eight, Heart)
    ]
    expect(checkFlush(hand)) |> toEqual(Flush(Eight))
  })
})

describe("check Full House", () => {
  test("2H 3H 4S 7C 9C -> None", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Heart),
      (Four, Spade),
      (Seven, Club),
      (Nine, Club)
    ]
    expect(checkFullHouse(hand)) |> toEqual(NotFound)
  })

  test("2H 3C 4S 4C 4H -> None", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Club),
      (Four, Spade),
      (Four, Club),
      (Four, Heart)
    ]
    expect(checkFullHouse(hand)) |> toEqual(NotFound)
  })

  test("2H 2C 6S 6C 6H -> FullHouse(6)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Club),
      (Six, Spade),
      (Six, Club),
      (Six, Heart)
    ]
    expect(checkFullHouse(hand)) |> toEqual(FullHouse(Six))
  })

  test("2H 2C 2S 6C 6H -> FullHouse(2)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Club),
      (Two, Spade),
      (Six, Club),
      (Six, Heart)
    ]
    expect(checkFullHouse(hand)) |> toEqual(FullHouse(Two))
  })
})

describe("check Four of a Kind", () => {
  test("2H 4C 7S 8D 9D -> Some(2)", () => {
    let hand: hand = [
      (Two, Heart),
      (Four, Club),
      (Seven, Spade),
      (Eight, Diamond),
      (Nine, Diamond)
    ]
    expect(checkFourOfAKind(hand)) |> toEqual(NotFound)
  })

  test("2H 2C 2S 2D 9D -> FourOfAKind(2)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Club),
      (Two, Spade),
      (Two, Diamond),
      (Nine, Diamond)
    ]
    expect(checkFourOfAKind(hand)) |> toEqual(FourOfAKind(Two))
  })

  test("3H 4C 4S 4D 4H -> FourOfAKind(4)", () => {
    let hand: hand = [
      (Three, Heart),
      (Four, Club),
      (Four, Spade),
      (Four, Diamond),
      (Four, Heart)
    ]
    expect(checkFourOfAKind(hand)) |> toEqual(FourOfAKind(Four))
  })
})

describe("check Straight flush", () => {
  test("2H 3C 4D 7C 8S -> None", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Club),
      (Four, Diamond),
      (Seven, Club),
      (Eight, Spade)
    ]
    expect(checkStraightFlush(hand)) |> toEqual(NotFound)
  })

  test("2H 3H 4H 5H 6H -> StraightFlush(6)", () => {
    let hand: hand = [
      (Two, Heart),
      (Three, Heart),
      (Four, Heart),
      (Five, Heart),
      (Six, Heart)
    ]
    expect(checkStraightFlush(hand)) |> toEqual(StraightFlush(Six))
  })
})

describe("get highest card", () => {
  test("2H 2D 4C 5S 6H -> Pair(2)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Diamond),
      (Four, Club),
      (Five, Spade),
      (Six, Heart)
    ]
    expect(getHighestCard(hand)) |> toEqual(Pair(Two))
  })

  test("2H 2S 5H 5S 9C -> TwoPairs(2,5)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Spade),
      (Five, Heart),
      (Five, Spade),
      (Nine, Club)
    ]
    expect(getHighestCard(hand)) |> toEqual(TwoPairs((Two, Five)))
  })

  test("2H 2C 6S 6C 6H -> FullHouse(6)", () => {
    let hand: hand = [
      (Two, Heart),
      (Two, Club),
      (Six, Spade),
      (Six, Club),
      (Six, Heart)
    ]
    expect(getHighestCard(hand)) |> toEqual(FullHouse(Six))
  })
})