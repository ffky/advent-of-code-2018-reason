/* Input is something like +1 or -2 separated by new lines. We need to
   strip out the +'s */
let parse = input =>
  Js.String.split("\n", input)
  ->Belt.List.fromArray
  ->Belt.List.keep(x => x !== "")
  ->Belt.List.map(x => x |> Js.String.replace("+", "") |> int_of_string);

let rec part1 = l =>
  switch (l) {
  | [] => 0
  | [h, ...t] => h + part1(t)
  };

let part2 = l => {
  let rec aux = (l2, acc, set) =>
    switch (l2) {
    | [] => aux(l, acc, set)
    | [h, ...t] =>
      let sum = h + acc;
      if (set->Belt.Set.Int.has(sum)) {
        sum;
      } else {
        aux(t, sum, set->Belt.Set.Int.add(sum));
      };
    };
  aux(l, 0, Belt.Set.Int.empty->Belt.Set.Int.add(0));
};
