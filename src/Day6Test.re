let input = {|1, 1
1, 6
8, 3
3, 4
5, 5
8, 9
|};

Jest.test("parses input", () => {
  Day6.parse(input)
  ->Jest.expect
  ->Jest.Expect.toEqual([
      (1, 1),
      (1, 6),
      (8, 3),
      (3, 4),
      (5, 5),
      (8, 9),
    ]);

  Js.undefined;
});
