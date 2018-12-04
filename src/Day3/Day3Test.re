Jest.test("parses input", () => {
  let raw = {|#1 @ 1,3: 4x4
#2 @ 3,1: 4x4
#3 @ 5,5: 2x2
|};

  Day3.parse(raw)
  ->Jest.expect
  ->Jest.Expect.toEqual([
      (1, (1, 3), (4, 4)),
      (2, (3, 1), (4, 4)),
      (3, (5, 5), (2, 2)),
    ]);

  Js.undefined;
});

Jest.test("coords", () => {
  Day3.coords((1, 4), (3, 6))
  ->Jest.expect
  ->Jest.Expect.toEqual([
      (1, 4),
      (2, 4),
      (3, 4),
      (1, 5),
      (2, 5),
      (3, 5),
      (1, 6),
      (2, 6),
      (3, 6),
    ]);
  Js.undefined;
});

let input = [
  (1, (1, 3), (4, 4)),
  (2, (3, 1), (4, 4)),
  (3, (5, 5), (2, 2)),
];

Jest.test("part 1", () => {
  Day3.part1(input)->Jest.expect->Jest.Expect.toEqual(4);
  Js.undefined;
});

Jest.test("part 2", () => {
  Day3.part2(input)->Jest.expect->Jest.Expect.toEqual(3);
  Js.undefined;
});
