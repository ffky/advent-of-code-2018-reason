/** Looks like:
   #1 @ 1,3: 4x4
   #2 @ 3,1: 4x4
   #3 @ 5,5: 2x2 */
let parse = input =>
  Js.String.split("\n", input)
  ->Belt.List.fromArray
  ->Belt.List.keep(x => x != "")
  ->Belt.List.map(row => {
      let first =
        row
        ->Js.String.split("@ ", _)
        ->Belt.Array.getExn(1)
        ->Js.String.split(": ", _);
      let coords = first->Belt.Array.getExn(0)->Js.String.split(",", _);
      let x = coords->Belt.Array.getExn(0)->int_of_string;
      let y = coords->Belt.Array.getExn(1)->int_of_string;
      let size = first->Belt.Array.getExn(1)->Js.String.split("x", _);
      let width = size->Belt.Array.getExn(0)->int_of_string;
      let height = size->Belt.Array.getExn(1)->int_of_string;
      ((x, y), (width, height));
    });

/* Make coordinates to make square from top left coordinates to bottom
   right coordinates */
let coords = ((x1, y1), (x2, y2)) => {
  let rec aux = ((x, y), l) =>
    switch (x < x2, y < y2) {
    | (true, _) => aux((x + 1, y), [(x, y), ...l])
    | (false, true) => aux((x1, y + 1), [(x, y), ...l])
    | (false, false) => [(x2, y2), ...l]
    };
  aux((x1, y1), []);
};

module PointComparable =
  Belt.Id.MakeComparable({
    type t = (int, int);
    let cmp = compare;
  });

let mergeSet = (set1, set2) =>
  set2->Belt.Set.reduce(set1, (set, value) => set->Belt.Set.add(value));

let part1 = l => {
  let rec aux = (l, allSet, overlappingSet, count) =>
    switch (l) {
    | [] => count
    | [h, ...t] =>
      let ((x, y), (width, height)) = h;
      let coordList = coords((x, y), (x + width - 1, y + height - 1));
      let coordSet =
        coordList
        ->Belt.List.toArray
        ->Belt.Set.fromArray(~id=(module PointComparable));
      let allIntersection = coordSet->Belt.Set.intersect(allSet);
      let overlappingDiff = allIntersection->Belt.Set.diff(overlappingSet);
      let overlappingCount = overlappingDiff->Belt.Set.size;
      aux(
        t,
        mergeSet(allSet, coordSet),
        mergeSet(overlappingSet, overlappingDiff),
        count + overlappingCount,
      );
    };

  let allSet = Belt.Set.make(~id=(module PointComparable));
  let overlappingSet = Belt.Set.make(~id=(module PointComparable));
  aux(l, allSet, overlappingSet, 0);
};
