open Hand;
open Rule;

let compareCard = ((cardA): card, cardB: card): int => {
  let (valueA, _) = cardA;
  let (valueB, _) = cardB;
  valueA > valueB ? 1 : -1;
}

let sortCard = (hand: hand) : hand => hand |> List.sort(compareCard)

type playerWin = Black(winningCondition) | White(winningCondition) | Tie

let compareHighCard = (black: hand, white: hand) : playerWin => {
  let (valuesBlack, _) = black |> List.split
  let (valuesWhite, _) = white |> List.split
  switch (valuesBlack, valuesWhite) {
  | ([_,_,_,_,e1], [_,_,_,_,e2]) when e1 != e2 => e1 > e2 ? Black(HighCard(e1)) : White(HighCard(e2))
  | ([_,_,_,d1,_], [_,_,_,d2,_]) when d1 != d2 => d1 > d2 ? Black(HighCard(d1)) : White(HighCard(d2))
  | ([_,_,c1,_,_], [_,_,c2,_,_]) when c1 != c2 => c1 > c2 ? Black(HighCard(c1)) : White(HighCard(c2))
  | ([_,b1,_,_,_], [_,b2,_,_,_]) when b1 != b2 => b1 > b2 ? Black(HighCard(b1)) : White(HighCard(b2))
  | ([a1,_,_,_,_], [a2,_,_,_,_]) when a1 != a2 => a1 > a2 ? Black(HighCard(a1)) : White(HighCard(a2))
  | _ => Tie
  };
}

let fight = (black: hand, white: hand) : playerWin => {
  let highestBlack: winningCondition = black |> sortCard |> getHighestCard
  let highestWhite: winningCondition = white |> sortCard |> getHighestCard
  switch (highestBlack, highestWhite) {
  | (TwoPairs((a1, b1)), TwoPairs((a2, b2))) when b1 != b2 => b1 > b2 ? Black(TwoPairs((a1, b1))) :White(TwoPairs((a2, b2))) 
  | (TwoPairs((a1, b1)), TwoPairs((a2, b2))) when a1 != a2 => a1 > a2 ? Black(TwoPairs((a1, b1))) :White(TwoPairs((a2, b2))) 
  | (a, b) when a > b => Black(a)
  | (a, b) when a < b => White(b)
  | (a, b) when a == b => compareHighCard(sortCard(black), sortCard(white))
  | _ => raise(Not_found)
  };
}