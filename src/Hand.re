type suit = Club
  | Diamond
  | Heart
  | Spade

type value = Two
  | Three
  | Four
  | Five
  | Six
  | Seven
  | Eight
  | Nine
  | Ten
  | Jack
  | Queen
  | King
  | Ace

type card = (value, suit)
type hand = list(card)

let valueToNumber = (value: value) : int =>
  switch value {
  | Two => 2
  | Three => 3
  | Four => 4
  | Five => 5
  | Six => 6
  | Seven => 7
  | Eight => 8
  | Nine => 9
  | Ten => 10
  | Jack => 11
  | Queen => 12
  | King => 13
  | Ace => 14
  };

let numberToValue = (number: int) : value =>
  switch number {
  | 2 => Two
  | 3 => Three
  | 4 => Four
  | 5 => Five
  | 6 => Six
  | 7 => Seven
  | 8 => Eight
  | 9 => Nine
  | 10 => Ten
  | 11 => Jack
  | 12 => Queen
  | 13 => King
  | 14 => Ace
  | _ => raise(Not_found)
  };