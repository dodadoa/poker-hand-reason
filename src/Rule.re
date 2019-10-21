open Hand;

// Assuming that hand are already sorted

type winningCondition = NotFound
  | HighCard (value)
  | Pair (value)
  | TwoPairs ((value, value))
  | ThreeOfAKind (value)
  | Straight (value)
  | Flush (value)
  | FullHouse (value)
  | FourOfAKind (value)
  | StraightFlush (value)

let checkPair = (hand: hand) : winningCondition => {
  let (values, _) = hand |> List.split
  switch values {
  | [a,b,_,_,_] when a == b => Pair(a)
  | [_,b,c,_,_] when b == c => Pair(b)
  | [_,_,c,d,_] when c == d => Pair(c)
  | [_,_,_,d,e] when d == e => Pair(d)
  | _ => NotFound
  };
}

let checkTwoPair = (hand: hand) : winningCondition => {
  let (values, _) = hand |> List.split
  switch values {
  | [a,b,c,d,_] when (a == b) && (c == d) => TwoPairs((a,c))
  | [_,b,c,d,e] when (b == c) && (d == e) => TwoPairs((b,d))
  | [a,b,_,d,e] when (a == b) && (d == e) => TwoPairs((a,d))
  | _ => NotFound
  };
}

let checkThreeOfAKind = (hand: hand) : winningCondition => {
  let (values, _) = hand |> List.split
  switch values {
  | [a,b,c,_,_] when (a == b) && (b == c) => ThreeOfAKind(a)
  | [_,b,c,d,_] when (b == c) && (c == d) => ThreeOfAKind(b)
  | [_,_,c,d,e] when (c == d) && (d == e) => ThreeOfAKind(c)
  | _ => NotFound
  };
}

let checkStraight = (hand: hand) : winningCondition => {
  let (values, _) = hand |> List.split
  let valueNumber = values |> List.map(valueToNumber)
  switch valueNumber {
  | [a,b,c,d,e] 
    when (b == a + 1) && (c == b + 1) && (d == c + 1) && (e == d + 1) => Straight(numberToValue(e))
  | _ => NotFound
  };
}

let checkFlush = (hand: hand) : winningCondition => {
  let cards = hand |> List.split
  switch cards {
  | ([_,_,_,_,highestValue], [a,b,c,d,e]) 
    when a == b && b == c && c == d && d == e => Flush(highestValue)
  | _ => NotFound
  };
}

let checkFullHouse = (hand: hand) : winningCondition => {
  let (values, _) = hand |> List.split
  switch values {
  | [a,b,c,d,e] when (a == b && b == c) && (d == e) => FullHouse(a)
  | [a,b,c,d,e] when (a == b) && (c == d && d == e) => FullHouse(c)
  | _ => NotFound
  };
}

let checkFourOfAKind = (hand: hand) : winningCondition => {
  let (values, _) = hand |> List.split
  switch values {
  | [a,b,c,d,_] when a == b && b == c && c == d => FourOfAKind(a)
  | [_,b,c,d,e] when b == c && c == d && d == e => FourOfAKind(e)
  | _ => NotFound
  };
}

let checkStraightFlush = (hand: hand) : winningCondition => {
  let (values, suits) = hand |> List.split
  let cards = (List.map(valueToNumber, values), suits)
  switch cards {
  | ([va, vb, vc, vd, ve], [sa, sb, sc, sd, se])
    when (sa == sb && sb == sc && sc == sd && sd == se) &&
      ((vb == va +1) && (vc == vb + 1) && (vd == vc + 1) && (ve == vd + 1)) => StraightFlush(numberToValue(ve))
  | _ => NotFound
  };
}

type result = Done(winningCondition) 
  | NotDone(hand)

let checkAndPass = (checkFunction: hand => winningCondition, wrapHand: result) : result => {
  switch wrapHand {
  | Done(winning) => Done(winning)
  | NotDone(hand) => {
    let result = checkFunction(hand)
    switch result {
    | NotFound => NotDone(hand)
    | winning => Done(winning)
    }
  }
  };
}

let getHighestCard = (hand: hand) : winningCondition => {
  let highestCard = NotDone(hand)
  |> checkAndPass(checkStraightFlush)
  |> checkAndPass(checkFourOfAKind)
  |> checkAndPass(checkFullHouse)
  |> checkAndPass(checkFlush)
  |> checkAndPass(checkStraight)
  |> checkAndPass(checkThreeOfAKind)
  |> checkAndPass(checkTwoPair)
  |> checkAndPass(checkPair)

  switch highestCard {
  | Done(highest) => highest
  | NotDone(_) => NotFound
  };
}


