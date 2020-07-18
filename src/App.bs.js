// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Rule$PokerHandReason = require("./Rule.bs.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function compareCard(cardA, cardB) {
  var match = cardA[0] > cardB[0];
  if (match) {
    return 1;
  } else {
    return -1;
  }
}

function sortCard(hand) {
  return List.sort(compareCard, hand);
}

function compareHighCard(black, white) {
  var match = List.split(black);
  var valuesBlack = match[0];
  var match$1 = List.split(white);
  var valuesWhite = match$1[0];
  if (valuesBlack) {
    var match$2 = valuesBlack[1];
    if (match$2) {
      var match$3 = match$2[1];
      if (match$3) {
        var match$4 = match$3[1];
        if (match$4) {
          var match$5 = match$4[1];
          if (match$5 && !(match$5[1] || !valuesWhite)) {
            var match$6 = valuesWhite[1];
            if (match$6) {
              var match$7 = match$6[1];
              if (match$7) {
                var match$8 = match$7[1];
                if (match$8) {
                  var match$9 = match$8[1];
                  if (match$9 && !match$9[1]) {
                    var e2 = match$9[0];
                    var d2 = match$8[0];
                    var c2 = match$7[0];
                    var b2 = match$6[0];
                    var a2 = valuesWhite[0];
                    var e1 = match$5[0];
                    var d1 = match$4[0];
                    var c1 = match$3[0];
                    var b1 = match$2[0];
                    var a1 = valuesBlack[0];
                    if (e1 !== e2) {
                      var match$10 = e1 > e2;
                      if (match$10) {
                        return /* Black */Block.__(0, [/* HighCard */Block.__(0, [e1])]);
                      } else {
                        return /* White */Block.__(1, [/* HighCard */Block.__(0, [e2])]);
                      }
                    } else if (d1 !== d2) {
                      var match$11 = d1 > d2;
                      if (match$11) {
                        return /* Black */Block.__(0, [/* HighCard */Block.__(0, [d1])]);
                      } else {
                        return /* White */Block.__(1, [/* HighCard */Block.__(0, [d2])]);
                      }
                    } else if (c1 !== c2) {
                      var match$12 = c1 > c2;
                      if (match$12) {
                        return /* Black */Block.__(0, [/* HighCard */Block.__(0, [c1])]);
                      } else {
                        return /* White */Block.__(1, [/* HighCard */Block.__(0, [c2])]);
                      }
                    } else if (b1 !== b2) {
                      var match$13 = b1 > b2;
                      if (match$13) {
                        return /* Black */Block.__(0, [/* HighCard */Block.__(0, [b1])]);
                      } else {
                        return /* White */Block.__(1, [/* HighCard */Block.__(0, [b2])]);
                      }
                    } else if (a1 !== a2) {
                      var match$14 = a1 > a2;
                      if (match$14) {
                        return /* Black */Block.__(0, [/* HighCard */Block.__(0, [a1])]);
                      } else {
                        return /* White */Block.__(1, [/* HighCard */Block.__(0, [a2])]);
                      }
                    } else {
                      return /* Tie */0;
                    }
                  } else {
                    return /* Tie */0;
                  }
                } else {
                  return /* Tie */0;
                }
              } else {
                return /* Tie */0;
              }
            } else {
              return /* Tie */0;
            }
          } else {
            return /* Tie */0;
          }
        } else {
          return /* Tie */0;
        }
      } else {
        return /* Tie */0;
      }
    } else {
      return /* Tie */0;
    }
  } else {
    return /* Tie */0;
  }
}

function fight(black, white) {
  var highestBlack = Rule$PokerHandReason.getHighestCard(List.sort(compareCard, black));
  var highestWhite = Rule$PokerHandReason.getHighestCard(List.sort(compareCard, white));
  var exit = 0;
  if (typeof highestBlack === "number" || !(highestBlack.tag === 2 && !(typeof highestWhite === "number" || highestWhite.tag !== 2))) {
    exit = 1;
  } else {
    var match = highestWhite[0];
    var b2 = match[1];
    var a2 = match[0];
    var match$1 = highestBlack[0];
    var b1 = match$1[1];
    var a1 = match$1[0];
    if (b1 !== b2) {
      var match$2 = b1 > b2;
      if (match$2) {
        return /* Black */Block.__(0, [/* TwoPairs */Block.__(2, [/* tuple */[
                        a1,
                        b1
                      ]])]);
      } else {
        return /* White */Block.__(1, [/* TwoPairs */Block.__(2, [/* tuple */[
                        a2,
                        b2
                      ]])]);
      }
    } else if (a1 !== a2) {
      var match$3 = a1 > a2;
      if (match$3) {
        return /* Black */Block.__(0, [/* TwoPairs */Block.__(2, [/* tuple */[
                        a1,
                        b1
                      ]])]);
      } else {
        return /* White */Block.__(1, [/* TwoPairs */Block.__(2, [/* tuple */[
                        a2,
                        b2
                      ]])]);
      }
    } else {
      exit = 1;
    }
  }
  if (exit === 1) {
    if (Caml_obj.caml_greaterthan(highestBlack, highestWhite)) {
      return /* Black */Block.__(0, [highestBlack]);
    } else if (Caml_obj.caml_lessthan(highestBlack, highestWhite)) {
      return /* White */Block.__(1, [highestWhite]);
    } else if (Caml_obj.caml_equal(highestBlack, highestWhite)) {
      return compareHighCard(List.sort(compareCard, black), List.sort(compareCard, white));
    } else {
      throw Caml_builtin_exceptions.not_found;
    }
  }
  
}

exports.compareCard = compareCard;
exports.sortCard = sortCard;
exports.compareHighCard = compareHighCard;
exports.fight = fight;
/* No side effect */