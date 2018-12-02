let parse = input =>
  Js.String.split("\n", input)
  ->Belt.List.fromArray
  ->Belt.List.keep(x => x !== "");

module IdComparable =
  Belt.Id.MakeComparable({
    type t = Js.String.t;
    let cmp = compare;
  });

let checksum = l => {
  let rec charCountMap = (charList, map) =>
    switch (charList) {
    | [] => map
    | [char, ...t] =>
      let map =
        switch (map->Belt.Map.get(char)) {
        | Some(count) => map->Belt.Map.set(char, count + 1)
        | None => map->Belt.Map.set(char, 1)
        };
      charCountMap(t, map);
    };

  let rec aux = (l, (twoCount, threeCount)) =>
    switch (l) {
    | [] => (twoCount, threeCount)
    | [h, ...t] =>
      let charList = h->Js.String.split("", _)->Belt.List.fromArray;
      let (twos, threes) =
        charCountMap(charList, Belt.Map.make(~id=(module IdComparable)))
        ->Belt.Map.reduce((0, 0), ((twos, threes), _key, value) =>
            switch ((twos, threes), value) {
            | ((0, _), 2) => (twos + 1, threes)
            | ((_, 0), 3) => (twos, threes + 1)
            | _ => (twos, threes)
            }
          );
      aux(t, (twoCount + twos, threeCount + threes));
    };
  let (twoCount, threeCount) = aux(l, (0, 0));
  twoCount * threeCount;
};

let letters = _l => {
  "wip"
};
