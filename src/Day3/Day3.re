/* Looks like:
   #1 @ 1,3: 4x4
   #2 @ 3,1: 4x4
   #3 @ 5,5: 2x2 */
let parse = input =>
  Js.String.split("\n", input)
  ->Belt.List.fromArray
  ->Belt.List.keep(x => x != "")
  ->Belt.List.map(row => {
      let matches =
        row |> Js.String.match([%re "/#(\\d) @ (\\d),(\\d): (\\d)x(\\d)/"]);
      switch (matches) {
      | None => Js.Exn.raiseError("no matches")
      | Some(matches) =>
        let get = index => matches->Belt.Array.getExn(index)->int_of_string;
        let num = get(1);
        let x = get(2);
        let y = get(3);
        let width = get(4);
        let height = get(5);
        (num, (x, y), (width, height));
      };
    });

/* Make coordinates to make square from top left coordinates to bottom
   right coordinates */
let coords = ((x1, y1), (x2, y2)) => {
  let rec aux = (x, y) =>
    switch (x < x2, y < y2) {
    | (true, _) => [(x, y), ...aux(x + 1, y)]
    | (false, true) => [(x, y), ...aux(x1, y + 1)]
    | (false, false) => [(x2, y2)]
    };
  aux(x1, y1);
};

module PointComparable =
  Belt.Id.MakeComparable({
    type t = (int, int);
    let cmp = compare;
  });

let makeCoordSet = ((x, y), (width, height)) => {
  let coordList = coords((x, y), (x + width - 1, y + height - 1));
  coordList
  ->Belt.List.toArray
  ->Belt.Set.fromArray(~id=(module PointComparable));
};

let mergeSet = (set1, set2) =>
  set2->Belt.Set.reduce(set1, (set, value) => set->Belt.Set.add(value));

let overlappingCoordSet = l => {
  let rec aux = (l, allSet, overlappingSet) =>
    switch (l) {
    | [] => overlappingSet
    | [h, ...t] =>
      let (_num, start, size) = h;
      let coordSet = makeCoordSet(start, size);
      let allIntersection = coordSet->Belt.Set.intersect(allSet);
      let overlappingDiff = allIntersection->Belt.Set.diff(overlappingSet);
      aux(
        t,
        mergeSet(allSet, coordSet),
        mergeSet(overlappingSet, overlappingDiff),
      );
    };

  let allSet = Belt.Set.make(~id=(module PointComparable));
  let overlappingSet = Belt.Set.make(~id=(module PointComparable));
  aux(l, allSet, overlappingSet);
};

let part1 = l => overlappingCoordSet(l)->Belt.Set.size;

let rec outside = (set, l) =>
  switch (l) {
  | [] => Js.Exn.raiseError("not found")
  | [h, ...t] =>
    let (_num, start, size) = h;
    makeCoordSet(start, size)
    ->Belt.Set.intersect(set)
    ->Belt.Set.size
    ->(
        fun
        | 0 => h
        | _ => outside(set, t)
      );
  };

let part2 = l => {
  let (num, _, _) = outside(overlappingCoordSet(l), l);
  num;
};
