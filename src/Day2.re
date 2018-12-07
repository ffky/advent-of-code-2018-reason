let parse = input =>
  Js.String.split("\n", input)
  ->Belt.List.fromArray
  ->Belt.List.keep(x => x !== "");

module IdComparable =
  Belt.Id.MakeComparable({
    type t = Js.String.t;
    let cmp = compare;
  });

let charList = l => l->Js.String.split("", _)->Belt.List.fromArray;

let part1 = l => {
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
      let (twos, threes) =
        charCountMap(charList(h), Belt.Map.make(~id=(module IdComparable)))
        ->Belt.Map.reduce((0, 0), ((twos, threes), _key, value) =>
            switch ((twos, threes), value) {
            | ((0, _), 2) => (1, threes)
            | ((_, 0), 3) => (twos, 1)
            | _ => (twos, threes)
            }
          );
      aux(t, (twoCount + twos, threeCount + threes));
    };
  let (twoCount, threeCount) = aux(l, (0, 0));
  twoCount * threeCount;
};

let rec part2 = l => {
  let commonLetters = (l1, l2) => {
    let rec aux = (innerl1, innerl2, acc, misses) =>
      switch (misses) {
      | 0
      | 1 =>
        switch (innerl1, innerl2) {
        | ([], []) => Some(acc)
        | ([], _)
        | (_, []) => Js.Exn.raiseError("not same length")
        | ([h1, ...t1], [h2, ...t2]) =>
          if (h1 != h2) {
            aux(t1, t2, acc, misses + 1);
          } else {
            aux(t1, t2, acc ++ h1, misses);
          }
        }
      | _ => None
      };
    aux(l1, l2, "", 0);
  };

  let rec compareItemToList = (item, l) =>
    switch (l) {
    | [] => None
    | [h, ...t] =>
      switch (commonLetters(charList(item), charList(h))) {
      | None => compareItemToList(item, t)
      | Some(found) => Some(found)
      }
    };

  switch (l) {
  | [] => Js.Exn.raiseError("not found")
  | [h, ...t] =>
    switch (compareItemToList(h, t)) {
    | None => part2(t)
    | Some(found) => found
    }
  };
};
